// TODO turn this into a real test project

#include <iostream>

#include "../stf/types.h"

// TODO (stouff) possibly put this in the vector header?
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& s, stf::math::vec<T, N> const& rhs) {
    s << "[ " << rhs[0];
    for (size_t i = 1; i < N; ++i)
    {
        s << ", " << rhs[i];
    }
    s << " ]";
    return s;
}

// TODO (stouff) possibly put this in the matrix header?
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& s, stf::math::mat<T, N> const& rhs)
{
    s << stf::math::vec<T, N>(rhs.row(0));
    for (size_t j = 1; j < N; ++j)
    {
        s << std::endl << stf::math::vec<T, N>(rhs.row(j));
    }
    return s;
}

int main()
{
    {
        stf::gpu::vec2 tmp;
        std::cout << "tmp: " << tmp << std::endl;

        tmp.x = 1;
        std::cout << "edit x: " << tmp << std::endl;

        tmp += tmp;
        std::cout << "+=: " << tmp << std::endl;

        stf::gpu::vec2 other;
        other.y = 2;
        std::cout << "other: " << other << std::endl;

        std::cout << "tmp + other: " << tmp + other << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::vec3 tmp(8);
        tmp.z = 9;

        std::cout << "cast: " << tmp.as<double>() << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::vec2 lhs(1);
        stf::gpu::vec2 rhs(2);
        std::cout << lhs << " * " << rhs << " = " << lhs * rhs << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::vec2 tmp(5);
        std::cout << "length(" << tmp << ") = " << tmp.length() << std::endl;
        std::cout << "normalize(" << tmp << ") = " << tmp.normalized() << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::vec2 tmp(5);
        std::cout << "2 * " << tmp << " = " << 2.f * tmp << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::mat2 tmp(1);
        std::cout << "tmp: " << std::endl << tmp << std::endl;
        std::cout << "tmp[0][0] = " << tmp[0][0] << std::endl;
        tmp[0][0] = 3;
        std::cout << "write 3 to tmp[0][0]" << std::endl << tmp << std::endl;
        std::cout << std::endl;
    }
}