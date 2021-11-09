if(BUILD_TESTS)
    add_library(test_stress_static source/test_static.c)
    target_link_libraries(test_stress_static PRIVATE lib_static)
    target_include_directories(test_stress_static PUBLIC headers)

    add_library(test_stress_shared source/test_shared.c)
    target_link_libraries(test_stress_shared PRIVATE lib_shared)
    target_include_directories(test_stress_shared PUBLIC headers)
endif()