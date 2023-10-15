enable_testing()

set(TEST_FILES
    "math/vec2_tests.cpp"
    "math/vec3_tests.cpp"
    "math/vec4_tests.cpp"
    "math/vec5_tests.cpp"
    "math/mtx4_tests.cpp"
    "alg/circle_tests.cpp"
    "alg/interpolation_tests.cpp"
    "alg/transform_tests.cpp"
)

add_executable(tests ${TEST_FILES})

target_include_directories(tests 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(tests PRIVATE stf GTest::gtest_main)

include(GoogleTest)
# finds all the tests associated with the executable
gtest_discover_tests(tests)