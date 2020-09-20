# ASIO_FOUND
# ASIO_INCLUDE_DIR
find_package(Asio CONFIG QUIET)
if(Asio_FOUND AND NOT THIRDPARTY)
  message(STATUS "Found Asio")
else()
  if(THIRDPARTY OR ANDROID)
    find_path(ASIO_INCLUDE_DIR NAMES asio.hpp NO_CMAKE_FIND_ROOT_PATH)
  else()
    find_path(ASIO_INCLUDE_DIR NAMES asio.hpp)
  endif()
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(Asio DEFAULT_MSG ASIO_INCLUDE_DIR)
  mark_as_advanced(ASIO_INCLUDE_DIR)
  if(Asio_FOUND)
    find_package(Threads)
    add_library(Asio::asio INTERFACE IMPORTED)
    set_target_properties(Asio::asio PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
      "${ASIO_INCLUDE_DIR}")
    set_target_properties(Asio::asio PROPERTIES INTERFACE_LINK_LIBRARIES
      Threads::Threads)
  endif()
endif()
