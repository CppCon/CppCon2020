set(EXE_NAME 02GildedRose)

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME}
        tests/main.cpp
        lib/GildedRose.cc
        lib/GildedRose.h
        tests/GildedRoseTest.cpp
        tests/GildedRoseApprovals.cpp
        tests/TestHelpers.cpp
        tests/TestHelpers.h
        tests/detailed_tests/GildedRoseApprovalsAllSteps.cpp
        )
target_link_libraries(${EXE_NAME}
        ApprovalTests::ApprovalTests
        Catch2::Catch2
        )
target_compile_definitions(${EXE_NAME} PRIVATE CATCH_CONFIG_FAST_COMPILE)
add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})

if (COLLECT_CODE_COVERAGE)
    set(COVERAGE_TARGET ${EXE_NAME}_branch_coverage)
    setup_target_for_coverage_lcov(
            NAME ${COVERAGE_TARGET}
            EXECUTABLE ${EXE_NAME}
            DEPENDENCIES ${EXE_NAME})
endif ()
