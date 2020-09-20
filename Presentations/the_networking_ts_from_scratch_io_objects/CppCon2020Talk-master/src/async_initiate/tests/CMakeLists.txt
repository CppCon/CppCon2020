cppcon_add_test(async_initiate SOURCES async_event.cpp main.cpp pending.cpp
  LIBRARIES Asio::asio Catch2::Catch2 async_initiate)
