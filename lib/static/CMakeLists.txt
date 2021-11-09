add_library(lib_static STATIC source/lib_static.c)
target_include_directories(lib_static PUBLIC ../headers)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()