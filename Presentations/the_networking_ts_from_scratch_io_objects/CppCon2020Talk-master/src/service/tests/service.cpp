#include <cppcon20/service.hpp>

#include <cstddef>
#include <vector>
#include <asio/execution_context.hpp>
#include <asio/io_context.hpp>

#include <catch2/catch.hpp>

namespace cppcon20::tests {
namespace {

struct statistics {
  std::size_t destroyed{0};
};

struct object {
  explicit object(statistics& stats) noexcept : stats_(stats) {}
  object() = delete;
  object(const object&) = delete;
  object(object&&) = delete;
  object& operator=(const object&) = delete;
  object& operator=(object&&) = delete;
  ~object() noexcept {
    ++stats_.destroyed;
  }
private:
  statistics& stats_;
};

TEST_CASE("Objects may be created and destroyed", "[service]") {
  statistics stats;
  ::asio::io_context ctx;
  auto&& s = ::asio::use_service<service<object>>(ctx);
  auto ptr = s.create(stats);
  CHECK(!stats.destroyed);
  auto ptr2 = s.create(stats);
  CHECK(!stats.destroyed);
  s.destroy(ptr2);
  CHECK(stats.destroyed == 1U);
  s.destroy(ptr);
  CHECK(stats.destroyed == 2U);
}

TEST_CASE("The lifetime of all objects ends when the service is shutdown",
  "[service]")
{
  statistics stats;
  {
    ::asio::io_context ctx;
    auto&& s = ::asio::use_service<service<object>>(ctx);
    s.create(stats);
    CHECK(!stats.destroyed);
  }
  CHECK(stats.destroyed == 1U);
}

TEST_CASE("After shutdown destroy is a no-op", "[service]") {
  statistics stats;
  ::asio::io_context ctx;
  auto&& s = ::asio::use_service<service<object>>(ctx);
  auto ptr = s.create(stats);
  CHECK(!stats.destroyed);
  s.shutdown();
  CHECK(stats.destroyed == 1U);
  s.destroy(ptr);
  CHECK(stats.destroyed == 1U);
}

TEST_CASE("A service may manage many objects, and those objects may be "
  "destroyed in any order at any time", "[service]")
{
  statistics stats;
  {
    ::asio::io_context ctx;
    auto&& s = ::asio::use_service<service<object>>(ctx);
    using objs_type = std::vector<object*>;
    objs_type objs;
    auto create = [&]() { objs.push_back(s.create(stats)); };
    auto destroy = [&](objs_type::size_type i) noexcept {
      auto iter = objs.begin();
      iter += i;
      s.destroy(*iter);
      objs.erase(iter);
    };
    create();
    REQUIRE(objs.size() == 1U);
    CHECK(!stats.destroyed);
    destroy(0);
    CHECK(stats.destroyed == 1U);
    REQUIRE(objs.empty());
    create();
    REQUIRE(objs.size() == 1U);
    CHECK(stats.destroyed == 1U);
    destroy(0);
    CHECK(stats.destroyed == 2U);
    REQUIRE(objs.empty());
    create();
    REQUIRE(objs.size() == 1U);
    create();
    REQUIRE(objs.size() == 2U);
    create();
    REQUIRE(objs.size() == 3U);
    CHECK(stats.destroyed == 2U);
    destroy(2);
    CHECK(stats.destroyed == 3U);
    REQUIRE(objs.size() == 2U);
    CHECK(stats.destroyed == 3U);
    destroy(0);
    CHECK(stats.destroyed == 4U);
    REQUIRE(objs.size() == 1U);
    create();
    REQUIRE(objs.size() == 2U);
    CHECK(stats.destroyed == 4U);
    destroy(0);
    CHECK(stats.destroyed == 5U);
    REQUIRE(objs.size() == 1U);
    create();
    REQUIRE(objs.size() == 2U);
    create();
    REQUIRE(objs.size() == 3U);
    CHECK(stats.destroyed == 5U);
  }
  CHECK(stats.destroyed == 8U);
}

}
}
