cmake_minimum_required(VERSION 3.8)

# Provide path for scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

project(demo)

include(UseCompilerCache)
useCompilerCache()

set(CMAKE_VERBOSE_MAKEFILE off)

# If building the code with clang gives 'Error: could not load cache'
#   1 turn COLLECT_CODE_COVERAGE to FALSE
#   2 build and run the tests
#   3 turn COLLECT_CODE_COVERAGE back to TRUE
set(COLLECT_CODE_COVERAGE FALSE)
if (COLLECT_CODE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
    set(COVERAGE_EXCLUDES
            "/Applications/Xcode.app/*"
            "/opt/local/*"
            "third_party/*"
            )
endif ()

add_subdirectory(shared_code)
add_subdirectory(third_party)

enable_testing()
add_subdirectory(demos)

# See https://stackoverflow.com/questions/41936659/code-coverage-warrnings-spam-output
# Build this if you start getting messages like:
# profiling: ..../cmake-build-debug/..../2019_11_18_fuzzing_gilded_rose.dir/GildedRoseApprovalTests.cc.gcda:
#   cannot merge previous GCDA file: corrupt arc tag (0x01000000)
add_custom_target(delete_coverage_gcda_files
        COMMAND find ${CMAKE_BINARY_DIR} -name '*.gcda' -print -delete
        COMMENT "Deleting *.gcda files."
        )
