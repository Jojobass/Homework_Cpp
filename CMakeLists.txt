cmake_minimum_required(VERSION 3.16)
project(HW2)


add_compile_options(-Wall -Werror -Wpedantic)

option(WITH_COVERAGE "Add coverage" ON)
if(WITH_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

option(WITH_SANITIZERS "Add address sanitizers" ON)
if(WITH_SANITIZERS)
    add_compile_options(-fno-omit-frame-pointer -fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

option(WITH_TESTS "Build tests" ON)
if (WITH_TESTS OR WITH_COVERAGE OR WITH_SANITIZERS)
    enable_testing()
    find_package(GTest REQUIRED)
    set(BUILD_TESTS ON)
endif()

add_subdirectory(lib/shared)
add_subdirectory(lib/static)
add_subdirectory(tests)

add_executable(main main.c)

option(WITH_PARALLEL "Using shared library" ON)
if(WITH_PARALLEL)
    target_link_libraries(main lib_shared)
else()
    target_link_libraries(main lib_static)
endif()