add_executable(shared_test lib_shared_tests.cpp)
target_link_libraries(shared_test GTest::Main lib_shared)

add_test(NAME shared_test COMMAND shared_test)