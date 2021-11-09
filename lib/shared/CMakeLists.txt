add_library(lib_shared SHARED source/lib_shared.c)
target_include_directories(lib_shared PUBLIC ../headers)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()