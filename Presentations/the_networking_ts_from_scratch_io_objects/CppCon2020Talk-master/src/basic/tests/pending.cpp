#include <cppcon20/pending.hpp>

#include <cassert>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>
#include <asio/associated_allocator.hpp>

#include <catch2/catch.hpp>

namespace cppcon20::tests {
namespace {

static_assert(std::is_nothrow_default_constructible_v<pending<void()>>);
static_assert(std::is_nothrow_move_constructible_v<pending<void()>>);
static_assert(std::is_nothrow_move_assignable_v<pending<void()>>);
static_assert(!std::is_copy_constructible_v<pending<void()>>);
static_assert(!std::is_copy_assignable_v<pending<void()>>);

struct statistics {
  std::size_t allocations{0};
  std::size_t deallocations{0};
};

template<typename T>
struct mock_allocator : std::allocator<T> {
private:
  using base = std::allocator<T>;
public:
  template<typename U>
  struct rebind {
    using type = mock_allocator<U>;
  };
  explicit mock_allocator(statistics& stats) noexcept : stats_(&stats) {}
  template<typename U>
  explicit mock_allocator(const mock_allocator<U>& alloc) noexcept : base(
    alloc), stats_(&alloc.stats())
  {
    assert(stats_);
  }
  template<typename U>
  mock_allocator& operator=(const mock_allocator<U>& rhs) noexcept {
    static_cast<base&>(*this) = static_cast<std::allocator<U>&>(rhs);
    stats_ = &rhs.stats();
    return *this;
  }
  template<typename Size>
  T* allocate(Size s) {
    assert(stats_);
    ++stats_->allocations;
    return std::allocator_traits<base>::allocate(static_cast<base&>(*this), s);
  }
  template<typename Size>
  void deallocate(T* ptr, Size s) {
    assert(stats_);
    ++stats_->deallocations;
    return std::allocator_traits<base>::deallocate(static_cast<base&>(*this),
      ptr, s);
  }
  statistics& stats() const noexcept {
    assert(stats_);
    return *stats_;
  }
private:
  statistics* stats_;
};

TEST_CASE("Completion handlers can be stored and invoked only once",
  "[pending]")
{
  bool invoked = false;
  pending<void()> p;
  CHECK(!p);
  p = [&]() {
    CHECK(!p);
    CHECK(!invoked);
    invoked = true;
  };
  REQUIRE(p);
  p();
  CHECK(!p);
  struct move_only {
    explicit move_only(bool& invoked) noexcept : invoked(invoked) {}
    move_only(const move_only&) = delete;
    move_only(move_only&&) = default;
    move_only& operator=(const move_only&) = delete;
    move_only& operator=(move_only&&) = delete;
    void operator()() noexcept {
      CHECK(!invoked);
      invoked = true;
    }
    bool& invoked;
  };
  p = move_only(invoked);
  invoked = false;
  p();
  CHECK(!p);
  CHECK(invoked);
}

TEST_CASE("The allocator associated with the completion handler is used to "
  "allocate and deallocate storage", "[pending]")
{
  statistics stats;
  bool invoked = false;
  {
    pending<void()> p;
    CHECK(!p);
    struct {
      using allocator_type = mock_allocator<int>;
      allocator_type get_allocator() const noexcept { return alloc; }
      void operator()() noexcept {
        CHECK(!invoked);
        invoked = true;
        CHECK(alloc.stats().deallocations == 1U);
      }
      bool& invoked;
      allocator_type alloc;
    } h{invoked, mock_allocator<int>(stats)};
    auto alloc = ::asio::get_associated_allocator(h);
    static_assert(std::is_same_v<decltype(alloc), mock_allocator<int>>);
    p = std::move(h);
    REQUIRE(p);
    CHECK(stats.allocations == 1U);
    CHECK(!stats.deallocations);
    p();
    CHECK(invoked);
    CHECK(stats.allocations == 1U);
    CHECK(stats.deallocations == 1U);
    p = decltype(h){invoked, mock_allocator<int>(stats)};
    CHECK(p);
    CHECK(stats.allocations == 2U);
    CHECK(stats.deallocations == 1U);
  }
  CHECK(stats.allocations == 2U);
  CHECK(stats.deallocations == 2U);
}

TEST_CASE("If moving the completion handler to the stack immediately before "
  "invocation throws then the memory is freed anyway", "[pending]")
{
  statistics stats;
  bool should_throw = false;
  bool invoked = false;
  struct handler {
    handler(bool& invoked, bool& should_throw, statistics& stats) noexcept :
      invoked_(invoked), should_throw_(should_throw), alloc_(stats) {}
    handler(const handler&) = delete;
    handler(handler&& rhs) : invoked_(rhs.invoked_), should_throw_(rhs
      .should_throw_), alloc_(rhs.alloc_)
    {
      if (should_throw_) {
        throw std::logic_error("TEST");
      }
    }
    void operator()() {
      invoked_ = true;
    }
    using allocator_type = mock_allocator<int>;
    allocator_type get_allocator() const noexcept {
      return alloc_;
    }
  private:
    bool& invoked_;
    bool& should_throw_;
    allocator_type alloc_;
  };
  pending<void()> p;
  p = handler(invoked, should_throw, stats);
  REQUIRE(p);
  should_throw = true;
  bool threw = false;
  try {
    p();
  } catch (const std::logic_error& ex) {
    (void) ex;
    threw = true;
  }
  CHECK(threw);
  CHECK(stats.allocations == 1U);
  CHECK(stats.deallocations == 1U);
}

TEST_CASE("Moving leaves the source empty and populates the destination "
  "without moving the wrapped callable", "[pending]")
{
  statistics stats;
  bool invoked = false;
  struct handler {
    void operator()() noexcept {
      CHECK(!invoked);
      invoked = true;
    };
    using allocator_type = mock_allocator<int>;
    allocator_type get_allocator() const noexcept {
      return alloc;
    }
    bool& invoked;
    allocator_type alloc;
  };
  pending<void()> p;
  p = handler{invoked, handler::allocator_type(stats)};
  CHECK(stats.allocations == 1U);
  CHECK(!stats.deallocations);
  CHECK(p);
  auto moved = std::move(p);
  REQUIRE(moved);
  CHECK(!p);
  CHECK(stats.allocations == 1U);
  CHECK(!stats.deallocations);
  CHECK(!invoked);
  moved();
  CHECK(invoked);
  CHECK(stats.allocations == 1U);
  CHECK(stats.deallocations == 1U);
}

TEST_CASE("Move assigning overwrites the destination and leaves the source "
  "empty", "[pending]")
{
  statistics stats;
  bool invoked = false;
  struct handler {
    void operator()() noexcept {
      CHECK(!invoked);
      invoked = true;
    };
    using allocator_type = mock_allocator<int>;
    allocator_type get_allocator() const noexcept {
      return alloc;
    }
    bool& invoked;
    allocator_type alloc;
  };
  pending<void()> p;
  p = handler{invoked, handler::allocator_type(stats)};
  pending<void()> other;
  other = handler{invoked, handler::allocator_type(stats)};
  CHECK(stats.allocations == 2U);
  CHECK(!stats.deallocations);
  CHECK(p);
  CHECK(other);
  p = std::move(other);
  CHECK(!other);
  CHECK(stats.allocations == 2U);
  CHECK(stats.deallocations == 1U);
  CHECK(!invoked);
  REQUIRE(p);
  p();
  CHECK(invoked);
  CHECK(stats.allocations == 2U);
  CHECK(stats.deallocations == 2U);
}

TEST_CASE("May be stored in a std::vector", "[pending]") {
  statistics stats;
  bool invoked = false;
  struct {
    void operator()() noexcept {
      CHECK(!invoked);
      invoked = true;
    };
    using allocator_type = mock_allocator<int>;
    allocator_type get_allocator() const noexcept {
      return alloc;
    }
    bool& invoked;
    allocator_type alloc;
  } h{invoked, mock_allocator<int>(stats)};
  std::vector<pending<void()>> vec;
  vec.emplace_back(h);
  vec.emplace_back(h);
  REQUIRE(vec.front());
  vec.front()();
  CHECK(invoked);
  vec.erase(vec.begin());
  vec.clear();
  CHECK(stats.allocations == 2U);
  CHECK(stats.deallocations == 2U);
}

}
}
