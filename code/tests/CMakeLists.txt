if (BUILD_TESTING)
    enable_testing()
    
    # NOTE: this method of collecting files requires that cmake must be reran every time we add/remove a file
    # TODO (stouff) set up post-merge and post-checkout scripts
    file(GLOB_RECURSE TEST_FILES "*.cpp")

    add_executable(tests ${TEST_FILES})

    target_include_directories(tests 
        PUBLIC "${CMAKE_SOURCE_DIR}/src/"
        PUBLIC "."
    )
    
    target_link_libraries(tests PRIVATE GTest::gtest_main)

    include(GoogleTest)
    # finds all the tests associated with the executable
    gtest_discover_tests(tests)
endif()