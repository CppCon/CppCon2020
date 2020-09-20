#pragma once

#include <cassert>
#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>
#include <asio/execution_context.hpp>

namespace cppcon20 {

template<typename T>
class service : public ::asio::execution_context::service {
private:
  struct node : public T {
    template<typename... Args>
    explicit node(Args&&... args) noexcept(std::is_nothrow_constructible_v<T,
      Args&&...>) : T(std::forward<Args>(args)...) {}
    node* next;
    node* prev{nullptr};
  };
public:
  using key_type = service;
  static_assert(std::is_base_of_v<key_type, service>);
  static inline ::asio::execution_context::id id;
  explicit service(::asio::execution_context& ctx) : ::asio::execution_context::
    service(ctx) {}
  service() = delete;
  service(const service&) = delete;
  service& operator=(const service&) = delete;
  virtual void shutdown() override {
    while (begin_) {
      auto&& tmp = *begin_;
      begin_ = tmp.next;
      delete &tmp;
    }
  }
  template<typename... Args>
  T* create(Args&&... args) {
    auto ptr = new node(std::forward<Args>(args)...);
    ptr->next = begin_;
    if (begin_) {
      begin_->prev = ptr;
    }
    begin_ = ptr;
    return ptr;
  }
  void destroy(T* obj) noexcept {
    if (!begin_) {
      return;
    }
    assert(obj);
    auto ptr = static_cast<node*>(obj);
    if (ptr->next) {
      ptr->next->prev = ptr->prev;
    }
    if (ptr->prev) {
      ptr->prev->next = ptr->next;
    } else {
      begin_ = ptr->next;
    }
    delete ptr;
  }
private:
  node* begin_{nullptr};
};

}
