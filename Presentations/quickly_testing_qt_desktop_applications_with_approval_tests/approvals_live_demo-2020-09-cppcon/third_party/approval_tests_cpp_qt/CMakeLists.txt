if (NOT TARGET ApprovalTestsQt)
    set(LIB_NAME ApprovalTestsQt)
    add_library(${LIB_NAME} INTERFACE)
    target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
    add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

    find_package(Qt5 COMPONENTS Widgets Test REQUIRED)
    target_link_libraries(${LIB_NAME} INTERFACE ApprovalTests Qt5::Widgets Qt5::Test)
endif ()
