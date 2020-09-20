#include <cppcon20/async_event.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>
#include <asio/bind_executor.hpp>
#include <asio/io_context.hpp>

#include <catch2/catch.hpp>

namespace cppcon20::tests {
namespace {

static_assert(!std::is_default_constructible_v<async_event>);
static_assert(!std::is_copy_constructible_v<async_event>);
static_assert(std::is_move_constructible_v<async_event>);
static_assert(!std::is_copy_assignable_v<async_event>);
static_assert(!std::is_move_assignable_v<async_event>);

TEST_CASE("When there are no events waiting notify_one does nothing",
  "[async_event]")
{
  asio::io_context ctx;
  async_event event(ctx.get_executor());
  CHECK(ctx.get_executor() == event.get_executor());
  auto released = event.notify_one();
  CHECK_FALSE(released);
  auto ran = ctx.run();
  CHECK_FALSE(ran);
  CHECK(ctx.stopped());
}

TEST_CASE("When there are no events waiting notify_all does nothing",
  "[async_event]")
{
  asio::io_context ctx;
  async_event event(ctx.get_executor());
  auto released = event.notify_all();
  CHECK_FALSE(released);
  auto ran = ctx.run();
  CHECK_FALSE(ran);
  CHECK(ctx.stopped());
}

TEST_CASE("When there is one event waiting notify_one releases that one event",
  "[async_event]")
{
  std::size_t invoked(0);
  auto f = [&]() noexcept { ++invoked; };
  asio::io_context ctx;
  async_event event(ctx.get_executor());
  event.async_wait(f);
  CHECK_FALSE(invoked);
  auto ran = ctx.poll();
  CHECK_FALSE(ran);
  CHECK_FALSE(ctx.stopped());
  auto released = event.notify_one();
  CHECK(released == 1U);
  ran = ctx.run();
  CHECK(ran == 1U);
  CHECK(ctx.stopped());
  CHECK(invoked == 1U);
  released = event.notify_one();
  CHECK_FALSE(released);
}

TEST_CASE("When there is one event waiting notify_all releases that one event",
  "[async_event]")
{
  std::size_t invoked(0);
  auto f = [&]() noexcept { ++invoked; };
  asio::io_context ctx;
  async_event event(ctx.get_executor());
  event.async_wait(f);
  CHECK_FALSE(invoked);
  auto ran = ctx.poll();
  CHECK_FALSE(ran);
  CHECK_FALSE(ctx.stopped());
  auto released = event.notify_all();
  CHECK(released == 1U);
  ran = ctx.run();
  CHECK(ran == 1U);
  CHECK(ctx.stopped());
  CHECK(invoked == 1U);
  released = event.notify_all();
  CHECK_FALSE(released);
}

TEST_CASE("When there are multiple events waiting notify_one releases them "
  "one at a time", "[async_event]")
{
  std::size_t invoked(0);
  auto f = [&]() noexcept { ++invoked; };
  asio::io_context ctx;
  async_event event(ctx.get_executor());
  event.async_wait(f);
  event.async_wait(f);
  CHECK_FALSE(invoked);
  auto ran = ctx.poll();
  CHECK_FALSE(ran);
  CHECK_FALSE(ctx.stopped());
  auto released = event.notify_one();
  CHECK(released == 1U);
  ran = ctx.poll();
  CHECK(ran == 1U);
  CHECK_FALSE(ctx.stopped());
  CHECK(invoked == 1U);
  released = event.notify_one();
  CHECK(released == 1U);
  ran = ctx.poll();
  CHECK(ran == 1U);
  CHECK(ctx.stopped());
  CHECK(invoked == 2U);
  released = event.notify_one();
  CHECK_FALSE(released);
}

TEST_CASE("When there are multiple events waiting notify_all releases them all",
  "[async_event]")
{
  std::size_t invoked(0);
  auto f = [&]() noexcept { ++invoked; };
  asio::io_context ctx;
  async_event event(ctx.get_executor());
  event.async_wait(f);
  event.async_wait(f);
  CHECK_FALSE(invoked);
  auto ran = ctx.poll();
  CHECK_FALSE(ran);
  CHECK_FALSE(ctx.stopped());
  auto released = event.notify_all();
  CHECK(released == 2U);
  ran = ctx.run();
  CHECK(ran == 2U);
  CHECK(ctx.stopped());
  CHECK(invoked == 2U);
  released = event.notify_all();
  CHECK_FALSE(released);
}

TEST_CASE("Work is executed using the associated executor", "[async_event]") {
  std::size_t invoked(0);
  auto f = [&]() noexcept { ++invoked; };
  asio::io_context a;
  asio::io_context b;
  async_event event(a.get_executor());
  event.async_wait(asio::bind_executor(b.get_executor(), f));
  CHECK_FALSE(invoked);
  auto ran = a.poll();
  CHECK_FALSE(ran);
  CHECK_FALSE(a.stopped());
  ran = b.poll();
  CHECK_FALSE(ran);
  CHECK_FALSE(b.stopped());
  auto released = event.notify_one();
  CHECK(released == 1U);
  ran = a.poll();
  CHECK_FALSE(ran);
  CHECK_FALSE(a.stopped());
  CHECK_FALSE(invoked);
  ran = b.run();
  CHECK(ran == 1U);
  CHECK(a.stopped());
  CHECK(b.stopped());
  CHECK(invoked == 1U);
  released = event.notify_one();
  CHECK_FALSE(released);
}

TEST_CASE("Move construction works as expected", "[async_event]") {
  std::size_t invoked(0);
  auto f = [&]() noexcept { ++invoked; };
  asio::io_context ctx;
  async_event event(ctx.get_executor());
  event.async_wait(f);
  async_event other(std::move(event));
  CHECK(other.get_executor() == ctx.get_executor());
  other.async_wait(f);
  CHECK_FALSE(invoked);
  auto ran = ctx.poll();
  CHECK_FALSE(ran);
  CHECK_FALSE(ctx.stopped());
  auto released = other.notify_one();
  CHECK(released == 1U);
  ran = ctx.poll();
  CHECK(ran == 1U);
  CHECK_FALSE(ctx.stopped());
  CHECK(invoked == 1U);
  released = other.notify_one();
  CHECK(released == 1U);
  ran = ctx.poll();
  CHECK(ran == 1U);
  CHECK(ctx.stopped());
  CHECK(invoked == 2U);
  released = other.notify_one();
  CHECK_FALSE(released);
}

}
}
