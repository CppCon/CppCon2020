cppcon_add_test(service SOURCES async_event.cpp main.cpp pending.cpp
  service.cpp LIBRARIES Asio::asio Catch2::Catch2 service)
