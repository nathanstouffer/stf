#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include <stf/stf.hpp>

#include "stf/scaffolding/alg/clipping.hpp"
#include "stf/scaffolding/verify.hpp"

namespace stf::alg
{

TEST(clipping, segment)
{
    stff::aabb2 box(stff::vec2(10), stff::vec2(20));
    stff::segment2 irrelevent(stff::vec2(0), stff::vec2(0));
    std::vector<scaffolding::alg::clipping::segment<float>> tests = {
        // segments entirely in the box
        {box, stff::segment2(stff::vec2(11, 11), stff::vec2(19, 19)), true,
         stff::segment2(stff::vec2(11, 11), stff::vec2(19, 19))},
        {box, stff::segment2(stff::vec2(11, 19), stff::vec2(19, 11)), true,
         stff::segment2(stff::vec2(11, 19), stff::vec2(19, 11))},
        {box, stff::segment2(stff::vec2(11, 11), stff::vec2(11, 19)), true,
         stff::segment2(stff::vec2(11, 11), stff::vec2(11, 19))},
        {box, stff::segment2(stff::vec2(11, 11), stff::vec2(19, 11)), true,
         stff::segment2(stff::vec2(11, 11), stff::vec2(19, 11))},

        // segments with one endpoint in the box and one endpoint out of the box
        {box, stff::segment2(stff::vec2(9, 9), stff::vec2(11, 11)), true,
         stff::segment2(stff::vec2(10, 10), stff::vec2(11, 11))},
        {box, stff::segment2(stff::vec2(9, 10), stff::vec2(11, 10)), true,
         stff::segment2(stff::vec2(10, 10), stff::vec2(11, 10))},
        {box, stff::segment2(stff::vec2(15, 25), stff::vec2(15, 15)), true,
         stff::segment2(stff::vec2(15, 20), stff::vec2(15, 15))},

        // segments with both endpoints outside the box that do intersect the box
        {box, stff::segment2(stff::vec2(9, 11), stff::vec2(21, 11)), true,
         stff::segment2(stff::vec2(10, 11), stff::vec2(20, 11))},
        {box, stff::segment2(stff::vec2(11, 9), stff::vec2(11, 21)), true,
         stff::segment2(stff::vec2(11, 10), stff::vec2(11, 20))},
        {box, stff::segment2(stff::vec2(9, 9), stff::vec2(21, 21)), true,
         stff::segment2(stff::vec2(10, 10), stff::vec2(20, 20))},
        {box, stff::segment2(stff::vec2(9, 21), stff::vec2(21, 9)), true,
         stff::segment2(stff::vec2(10, 20), stff::vec2(20, 10))},
        {box, stff::segment2(stff::vec2(9, 21), stff::vec2(21, 9)), true,
         stff::segment2(stff::vec2(10, 20), stff::vec2(20, 10))},

        // segments that do not intersect the box
        {box, stff::segment2(stff::vec2(4, 15), stff::vec2(15, 4)), false, irrelevent},
    };
    scaffolding::verify(tests);
}

TEST(clipping, polyline)
{
    stff::aabb2 box(stff::vec2(10), stff::vec2(20));
    std::vector<scaffolding::alg::clipping::polyline<float>> tests = {
        // polylines entirely in the box
        {box, stff::polyline2({stff::vec2(10), stff::vec2(20)}), {stff::polyline2({stff::vec2(10), stff::vec2(20)})}},
        {box,
         stff::polyline2({stff::vec2(10), stff::vec2(10, 20), stff::vec2(20)}),
         {stff::polyline2({stff::vec2(10), stff::vec2(10, 20), stff::vec2(20)})}},
        // polylines that partially intersect the box
        {box, stff::polyline2({stff::vec2(9), stff::vec2(21)}), {stff::polyline2({stff::vec2(10), stff::vec2(20)})}},
        {box,
         stff::polyline2({stff::vec2(9), stff::vec2(21), stff::vec2(21, 11), stff::vec2(15, 11)}),
         {stff::polyline2({stff::vec2(10), stff::vec2(20)}),
          stff::polyline2({stff::vec2(20, 11), stff::vec2(15, 11)})}},
        // polylines entirely outside the box
        {box, stff::polyline2({stff::vec2(9), stff::vec2(21, 9), stff::vec2(21)}), {}},
    };
    scaffolding::verify(tests);
}

TEST(clipping, index_out_of_stack_array_bounds)
{
    int i = 50;
    int arr[10];
    arr[i] = 0;
    std::cout << arr[i] << std::endl;
}

TEST(clipping, index_out_of_heap_array_bounds)
{
    int* arr = new int[50];
    arr[50] = 90;
    std::cout << arr[50] << std::endl;
}

TEST(clipping, use_heap_after_free)
{
    int* arr = new int[50];
    arr[0] = 7;
    delete[] arr;
    arr[0] = 8;
    std::cout << arr[0] << std::endl;
}

TEST(clipping, use_stl_container_after_free)
{
    std::vector<int> vec = {1, 2, 3};
    auto it = vec.begin();
    for (size_t i = 0; i < 4096; ++i)
    {
        vec.push_back(i);
    }
    std::cout << *it << std::endl;
}

} // namespace stf::alg
