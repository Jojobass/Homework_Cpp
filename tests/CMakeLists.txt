if(BUILD_TESTS)
    add_subdirectory(direct)

    add_executable(stress_test test.cpp)
    target_link_libraries(stress_test test_stress_static test_stress_shared)

    add_test(NAME stress_test COMMAND stress_test)
endif()