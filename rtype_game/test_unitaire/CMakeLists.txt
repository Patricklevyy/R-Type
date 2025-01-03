file(GLOB_RECURSE TEST_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(r-type_tests ${TEST_SRC})

link_common_libraries(r-type_tests)
target_link_libraries(r-type_tests PRIVATE
    rtype_shared
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME RTypeTests COMMAND r-type_tests)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS r-type_tests
)
