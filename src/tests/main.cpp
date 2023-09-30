// TODO turn this into a real test project

#include <iostream>

#include "../stf/types.h"

// TODO (stouff) possibly put this in the vector header?
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& s, stf::math::vec<T, N> const& rhs) {
    s << "{ " << rhs[0];
    for (size_t i = 1; i < N; ++i)
    {
        s << ", " << rhs[i];
    }
    s << " }";
    return s;
}

int main()
{

    {
        stf::gpu::vec2 tmp;
        std::cout << "tmp: " << tmp << std::endl;

        tmp[0] = 1;
        std::cout << "edit x: " << tmp << std::endl;

        tmp += tmp;
        std::cout << "+=: " << tmp << std::endl;

        stf::gpu::vec2 other;
        other[1] = 2;
        std::cout << "other: " << other << std::endl;

        std::cout << "tmp + other: " << tmp + other << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::vec3 tmp(8);
        tmp[2] = 9;

        std::cout << "cast: " << tmp.as<double>() << std::endl;
    }
}