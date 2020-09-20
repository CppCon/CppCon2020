cppcon_add_test(no_service SOURCES async_event.cpp main.cpp pending.cpp
  LIBRARIES Asio::asio Catch2::Catch2 no_service)
