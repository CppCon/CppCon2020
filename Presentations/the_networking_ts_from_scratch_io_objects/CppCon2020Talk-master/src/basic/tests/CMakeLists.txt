cppcon_add_test(basic SOURCES async_event.cpp main.cpp pending.cpp LIBRARIES
  Asio::asio Catch2::Catch2 basic)
