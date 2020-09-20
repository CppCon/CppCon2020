message(INFO " Hello from 05")
set(EXE_NAME 05QTableWidget)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        main.cpp
        TableWidgetTextTest.cpp
        helpers/QTableWidgetExamples.cpp
        helpers/QTableWidgetExamples.h
        )
target_link_libraries(${EXE_NAME} ApprovalTestsQt::ApprovalTestsQt Catch2::Catch2)
target_compile_definitions(${EXE_NAME} PRIVATE CATCH_CONFIG_FAST_COMPILE)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
