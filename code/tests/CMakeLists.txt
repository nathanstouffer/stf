if (BUILD_TESTING)
    add_executable(tests math/vec_tests.cpp)
    target_include_directories(tests 
    PUBLIC "${CMAKE_SOURCE_DIR}/src/"
    PUBLIC ".")
    
    target_link_libraries(tests PRIVATE GTest::gtest_main)

    include(GoogleTest)
    # finds all the tests associated with the executable
    gtest_discover_tests(tests)
endif()