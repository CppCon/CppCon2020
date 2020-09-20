set(LIB_NAME shared_code)
set(CMAKE_CXX_STANDARD 17)
add_library(${LIB_NAME}
        SVGDrawing.cpp
        SVGDrawing.h
        ComplexOperation.cpp
        ComplexOperation.h
        HelloApprovals.cpp
        HelloApprovals.h
        FileUtilities.cpp
        FileUtilities.h
        Logger.cpp
        Logger.h
        StringUtilities.cpp
        StringUtilities.h
        )
add_library(
        ${LIB_NAME}::${LIB_NAME}
        ALIAS
        ${LIB_NAME}
)
target_include_directories(${LIB_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
