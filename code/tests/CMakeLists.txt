if (BUILD_TESTING)
    add_executable(tests tests.cpp)
    target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/src/)
    
    target_link_libraries(tests PRIVATE GTest::gtest_main)

    include(GoogleTest)
    # finds all the tests associated with the executable
    gtest_discover_tests(tests)
endif()