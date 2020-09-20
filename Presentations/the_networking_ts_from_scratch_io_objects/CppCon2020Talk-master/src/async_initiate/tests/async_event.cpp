#include <cppcon20/async_event.hpp>

#include <chrono>
#include <cstddef>
#include <future>
#include <type_traits>
#include <utility>
#include <asio/bind_executor.hpp>
#include <asio/io_context.hpp>
#include <asio/use_future.hpp>

#include <catch2/catch.hpp>

namespace cppcon20::tests {
namespace {

static_assert(!std::is_default_constructible_v<async_event>);
static_assert(!std::is_copy_constructible_v<async_event>);
static_assert(!std::is_move_constructible_v<async_event>);
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
  CHECK(ctx.stopped());
  ctx.restart();
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
  CHECK(ctx.stopped());
  ctx.restart();
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
  CHECK(ctx.stopped());
  ctx.restart();
  auto released = event.notify_one();
  CHECK(released == 1U);
  ran = ctx.poll();
  CHECK(ran == 1U);
  CHECK(ctx.stopped());
  ctx.restart();
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
  CHECK(ctx.stopped());
  ctx.restart();
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
  CHECK(a.stopped());
  a.restart();
  ran = b.poll();
  CHECK_FALSE(ran);
  CHECK(b.stopped());
  b.restart();
  auto released = event.notify_one();
  CHECK(released == 1U);
  ran = a.poll();
  CHECK_FALSE(ran);
  CHECK(a.stopped());
  CHECK_FALSE(invoked);
  ran = b.run();
  CHECK(ran == 1U);
  CHECK(b.stopped());
  CHECK(invoked == 1U);
  released = event.notify_one();
  CHECK_FALSE(released);
}

TEST_CASE("Completion tokens are correctly handled", "[async_event]") {
  asio::io_context ctx;
  async_event event(ctx.get_executor());
  auto f = event.async_wait(asio::use_future);
  auto status = f.wait_for(std::chrono::seconds(0));
  CHECK(status != std::future_status::ready);
  auto ran = ctx.poll();
  CHECK_FALSE(ran);
  CHECK(ctx.stopped());
  status = f.wait_for(std::chrono::seconds(0));
  CHECK(status != std::future_status::ready);
  ctx.restart();
  auto released = event.notify_one();
  CHECK(released == 1U);
  ctx.run();
  CHECK(ctx.stopped());
  status = f.wait_for(std::chrono::seconds(0));
  CHECK(status == std::future_status::ready);
  released = event.notify_one();
  CHECK_FALSE(released);
}

}
}
