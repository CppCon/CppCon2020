#pragma once

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>
#include <asio/associated_executor.hpp>
#include <asio/async_result.hpp>
#include <asio/execution/allocator.hpp>
#include <asio/execution/context.hpp>
#include <asio/execution/execute.hpp>
#include <asio/execution/executor.hpp>
#include <asio/execution/outstanding_work.hpp>
#include <asio/execution_context.hpp>
#include <asio/io_context.hpp>
#include <asio/prefer.hpp>
#include <asio/query.hpp>
#include "pending.hpp"
#include "service.hpp"

namespace cppcon20 {

template<asio::execution::executor Executor>
struct basic_async_event {
  using executor_type = Executor;
  basic_async_event(basic_async_event&& other) = delete;
  basic_async_event& operator=(basic_async_event&&) = delete;
private:
  using pendings_type = std::vector<pending<void()>>;
  using service_type = service<pendings_type>;
  Executor ex_;
  service_type& service_;
  pendings_type* pendings_;
public:
  explicit basic_async_event(executor_type ex) : ex_(std::move(ex)),
    service_(
      asio::use_service<service_type>(
        asio::query(ex_, asio::execution::context))),
    pendings_(service_.create()) {}
  ~basic_async_event() noexcept {
    service_.destroy(pendings_);
  }
  auto get_executor() const noexcept {
    return ex_;
  }
  std::size_t notify_one() {
    if (pendings_->empty()) return 0;
    auto pending = std::move(pendings_->front());
    pendings_->erase(pendings_->begin());
    pending();
    return 1;
  }
  std::size_t notify_all() {
    std::size_t invoked(0);
    while (notify_one()) ++invoked;
    return invoked;
  }
  template<typename CompletionToken>
  decltype(auto) async_wait(CompletionToken&& token) {
    return asio::async_initiate<CompletionToken, void()>([&](auto h) {
      auto ex = asio::get_associated_executor(h, ex_);
      pendings_->emplace_back([h = std::move(h), ex = std::move(ex)]() mutable {
        auto alloc = asio::get_associated_allocator(h);
        auto alloc_ex = asio::prefer(std::move(ex), asio::execution::allocator(
          alloc));
        asio::execution::execute(alloc_ex, std::move(h));
      });
    }, token);
  }
};

using async_event = basic_async_event<asio::io_context::executor_type>;

}
