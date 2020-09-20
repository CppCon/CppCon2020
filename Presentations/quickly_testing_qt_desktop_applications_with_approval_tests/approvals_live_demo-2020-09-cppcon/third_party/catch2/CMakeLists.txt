if (NOT TARGET Catch2)
    project(Catch2 CXX)
    set(CMAKE_CXX_STANDARD 11)
    add_library(${PROJECT_NAME} INTERFACE)
    target_include_directories(${PROJECT_NAME}
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

    # Mimic the library names in Catch2's own CMake files:
    add_library(Catch2::Catch2 ALIAS Catch2)

    # This one is historical, left over from when ApprovalTests.cpp was first created.
    # We could encourage users to move away from it.
    add_library(catch2 ALIAS Catch2)
endif ()
