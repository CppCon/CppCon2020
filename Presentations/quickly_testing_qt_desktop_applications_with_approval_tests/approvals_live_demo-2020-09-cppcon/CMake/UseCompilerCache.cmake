# From Craig Scott's "Professional CMake: A Practical Guide", 6th Edition
function(useCompilerCache)
    if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        message(INFO " useCompilerCache() disabled, as not called at root of project")
        return()
    endif()

    find_program(CCACHE_PROGRAM ccache)
    if(NOT CCACHE_PROGRAM)
        message(INFO " useCompilerCache() disabled, as ccache program not found")
        return()
    endif()

    message(INFO " useCompilerCache() enabled")

    set(ccacheEnv
            CCACHE_BASEDIR=${CMAKE_BINARY_DIR}
            CCACHE_CPP2=true
            CCACHE_SLOPPINESS=pch_defines,time_macros
    )

    if(CMAKE_GENERATOR MATCHES "Ninja|Makefiles")
        foreach(lang IN ITEMS C CXX OBJC OBJCXX CUDA)
        set(CMAKE_${lang}_COMPILER_LAUNCHER
                ${CMAKE_COMMAND} -E env ${ccacheEnv} ${CCACHE_PROGRAM}
                PARENT_SCOPE)
        endforeach()
    elseif(CMAKE_GENERATOR STREQUAL Xcode)
        foreach(lang IN ITEMS C CXX)
            set(launcher ${CMAKE_BINARY_DIR}/launch-${lang})
            file(WRITE ${launcher} "#!/bin/bash\n\n")
            foreach(keyVal IN LISTS ccacheEnv)
                file(APPEND ${launcher} "export ${keyVal}\n")
            endforeach()
            file(APPEND ${launcher}
                    "exec \"${CCACHE_PROGRAM}\" "
                    "\"${CMAKE_${lang}_COMPILER}\" \"$@\"\n")
            execute_process(COMMAND chmod a+rx ${launcher})
        endforeach()
        set(CMAKE_XCODE_ATTRIBUTE_CC
                ${CMAKE_BINARY_DIR}/launch-C PARENT_SCOPE)
        set(CMAKE_XCODE_ATTRIBUTE_CXX
                ${CMAKE_BINARY_DIR}/launch-CXX PARENT_SCOPE)
        set(CMAKE_XCODE_ATTRIBUTE_LD
                ${CMAKE_BINARY_DIR}/launch-C PARENT_SCOPE)
        set(CMAKE_XCODE_ATTRIBUTE_LDPLUSPLUS
                ${CMAKE_BINARY_DIR}/launch-CXX PARENT_SCOPE)
    endif()
endfunction()
