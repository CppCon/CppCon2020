#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <asio/associated_allocator.hpp>

namespace cppcon20 {

template<typename T>
class pending;

template<typename R, typename... Args>
class pending<R(Args...)> {
private:
  struct base {
    base() = default;
    base(const base&) = default;
    base(base&&) = default;
    base& operator=(const base&) = default;
    base& operator=(base&&) = default;
    virtual ~base() noexcept {}
    virtual R invoke(Args&&...) = 0;
    virtual void destroy() noexcept = 0;
  };
  struct deleter {
    void operator()(base* ptr) const noexcept {
      assert(ptr);
      ptr->destroy();
    }
  };
  template<typename T>
  struct derived final : base {
    template<typename U>
    explicit derived(U&& u) noexcept(std::is_nothrow_constructible_v<T, U&&>) :
      t_(std::forward<U>(u)) {}
    virtual R invoke(Args&&... args) override {
      struct guard {
        ~guard() noexcept {
          if (self) {
            self->destroy();
          }
        }
        derived* self;
      };
      guard g{this};
      auto t = std::move(t_);
      g.self = nullptr;
      destroy(::asio::get_associated_allocator(t));
      return std::invoke(std::move(t), std::forward<Args>(args)...);
    }
    virtual void destroy() noexcept override {
      destroy(::asio::get_associated_allocator(t_));
    }
  private:
    template<typename Allocator>
    void destroy(const Allocator& a) {
      using allocator_type = typename std::allocator_traits<Allocator>::template
        rebind_alloc<derived>;
      allocator_type alloc(a);
      using traits_type = std::allocator_traits<allocator_type>;
      traits_type::destroy(alloc, this);
      traits_type::deallocate(alloc, this, 1);
    }
    T t_;
  };
  using impl_type = std::unique_ptr<base, deleter>;
  template<typename T>
  static impl_type make_impl(T&& t) {
    auto alloc = ::asio::get_associated_allocator(t);
    using allocator_type = typename std::allocator_traits<decltype(alloc)>::
      template rebind_alloc<derived<std::decay_t<T>>>;
    allocator_type a(alloc);
    using traits_type = std::allocator_traits<allocator_type>;
    auto ptr = traits_type::allocate(a, 1);
    struct guard {
      ~guard() noexcept {
        if (p) {
          traits_type::deallocate(alloc, p, 1);
        }
      }
      decltype(ptr) p;
      allocator_type& alloc;
    };
    guard g{ptr, a};
    traits_type::construct(a, ptr, std::forward<T>(t));
    g.p = nullptr;
    static_assert(std::is_nothrow_constructible_v<impl_type, decltype(ptr)>);
    return impl_type(ptr);
  };
public:
  pending() = default;
  template<typename T> requires(!std::is_same_v<std::decay_t<T>, pending>)
  explicit pending(T&& t) : impl_(make_impl(std::forward<T>(t))) {}
  explicit operator bool() const noexcept { return !!impl_; }
  template<typename T> requires(!std::is_same_v<std::decay_t<T>, pending>)
  pending& operator=(T&& t) {
    impl_ = make_impl(std::forward<T>(t));
    return *this;
  }
  R operator()(Args... args) {
    assert(impl_);
    return impl_.release()->invoke(std::forward<Args>(args)...);
  }
private:
  impl_type impl_;
};

}
