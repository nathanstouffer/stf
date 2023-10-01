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
        std::cout << std::endl << "write 3 to tmp[0][0]" << std::endl << tmp << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::mat2 tmp;
        std::cout << "tmp: " << std::endl << tmp << std::endl;
        tmp[0] = stf::gpu::vec2(3, 4);
        std::cout << std::endl << "write [3, 4] to first column" << std::endl << tmp << std::endl;
        std::cout << "transpose: " << std::endl << tmp.transposed() << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::mat2 lhs(1);
        stf::gpu::mat2 rhs(2);
        std::cout << "lhs: " << std::endl << lhs << std::endl;
        std::cout << "rhs: " << std::endl << rhs << std::endl;
        std::cout << std::endl << "multiply" << std::endl << lhs * rhs << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::mat2 lhs(1);
        stf::gpu::vec2 rhs(2);
        std::cout << "lhs: " << std::endl << lhs << std::endl;
        std::cout << "rhs: " << std::endl << rhs << std::endl;
        std::cout << std::endl << "multiply" << std::endl << lhs * rhs << std::endl;
        std::cout << std::endl;
    }

    {
        stf::gpu::vec3 tmp(1, 0, 0);
        std::cout << "tmp: " << tmp << std::endl;
        std::cout << "rotated:" << stf::math::rotate_around(tmp, stf::gpu::vec3(0, 0, 1), stf::constants<stf::gpu_float_t>::half_pi) << std::endl;
        std::cout << "rotated:" << stf::math::rotate_around(stf::gpu::vec3(0, 0, 1), stf::constants<stf::gpu_float_t>::half_pi) * stf::gpu::vec4(tmp, 0) << std::endl;
        std::cout << std::endl;
    }
}