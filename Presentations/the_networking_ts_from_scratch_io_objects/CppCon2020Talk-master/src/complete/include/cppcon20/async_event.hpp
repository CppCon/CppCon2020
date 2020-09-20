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
  basic_async_event(basic_async_event&& other) noexcept : ex_(std::move(other
    .ex_)), pendings_(std::exchange(other.pendings_, nullptr)) {}
private:
  using pending_type = pending<void()>;
  using pendings_type = std::vector<pending_type>;
  using service_type = service<pendings_type>;
  static service_type& get_service(executor_type& ex) {
    return asio::use_service<service_type>(asio::query(ex, asio::execution::
      context));
  }
public:
  explicit basic_async_event(executor_type ex) : ex_(std::move(ex)), pendings_(
    get_service(ex).create()) {}
  ~basic_async_event() noexcept {
    if (pendings_) {
      get_service(ex_).destroy(pendings_);
    }
  }
  auto get_executor() const noexcept {
    return ex_;
  }
  //  TODO: Move ctor? Move assignment operator?
  std::size_t notify_one() {
    assert(pendings_);
    if (pendings_->empty()) {
      return 0;
    }
    auto pending = std::move(pendings_->front());
    assert(pending);
    pendings_->erase(pendings_->begin());
    pending();
    return 1;
  }
  std::size_t notify_all() {
    assert(pendings_);
    auto iter = pendings_->begin();
    struct guard {
      ~guard() noexcept {
        self.pendings_->erase(self.pendings_->begin(), it);
      }
      decltype(iter)& it;
      basic_async_event& self;
    };
    guard g{iter, *this};
    std::size_t retr(0);
    for (auto end = pendings_->end(); iter != end; ++iter, ++retr) {
      assert(*iter);
      (*iter)();
    }
    return retr;
  }
  template<typename CompletionToken>
  decltype(auto) async_wait(CompletionToken&& token) {
    assert(pendings_);
    return asio::async_initiate<CompletionToken, void()>([ex = ex_,
      pendings = pendings_](auto h)
    {
      assert(pendings);
      auto io_ex = asio::prefer(ex, asio::execution::outstanding_work.tracked);
      auto assoc_ex = asio::get_associated_executor(h, ex);
      auto ex = asio::prefer(std::move(assoc_ex), asio::execution::
        outstanding_work.tracked);
      pendings->emplace_back([h = std::move(h), io_ex = std::move(io_ex), ex =
        std::move(ex)]() mutable
      {
        auto alloc = asio::get_associated_allocator(h);
        auto alloc_ex = asio::prefer(std::move(ex), asio::execution::allocator(
          alloc));
        asio::execution::execute(alloc_ex, [h = std::move(h), io_ex = std::move
          (io_ex)]() mutable
        {
          auto local_ex = std::move(io_ex);
          std::move(h)();
        });
      });
    }, token);
  }
private:
  Executor ex_;
  pendings_type* pendings_;
};

using async_event = basic_async_event<asio::io_context::executor_type>;

}
