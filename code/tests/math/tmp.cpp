#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include <stf/types.h>

// TODO (stouff) possibly put this in the vector header?
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& s, stf::math::vec<T, N> const& rhs)
{
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
std::ostream& operator<<(std::ostream& s, stf::math::mtx<T, N> const& rhs)
{
    s << rhs.row(0).as_vec();
    for (size_t i = 1; i < N; ++i)
    {
        s << std::endl << rhs.row(i).as_vec();
    }
    return s;
}

int tmp()
{

    {
        stff::vec3 tmp(8);
        tmp.z = 9;

        std::cout << "cast: " << tmp.as<double>() << std::endl;
        std::cout << std::endl;
    }

    {
        stff::vec2 lhs(1);
        stff::vec2 rhs(2);
        std::cout << lhs << " * " << rhs << " = " << lhs * rhs << std::endl;
        std::cout << std::endl;
    }

    {
        stff::vec2 tmp(5);
        std::cout << "length(" << tmp << ") = " << tmp.length() << std::endl;
        std::cout << "normalize(" << tmp << ") = " << tmp.normalized() << std::endl;
        std::cout << std::endl;
    }

    {
        stff::vec2 tmp(5);
        std::cout << "2 * " << tmp << " = " << 2.f * tmp << std::endl;
        std::cout << std::endl;
    }

    {
        stff::mtx2 tmp(1);
        std::cout << "tmp: " << std::endl << tmp << std::endl;
        std::cout << "tmp[0][0] = " << tmp[0][0] << std::endl;
        tmp[0][0] = 3;
        std::cout << std::endl << "write 3 to tmp[0][0]" << std::endl << tmp << std::endl;
        std::cout << std::endl;
    }

    {
        stff::mtx2 tmp;
        std::cout << "tmp: " << std::endl << tmp << std::endl;
        tmp[0] = stff::vec2(3, 4);
        std::cout << std::endl << "write [3, 4] to first row" << std::endl << tmp << std::endl;
        std::cout << "transpose: " << std::endl << tmp.transposed() << std::endl;
        std::cout << std::endl;
    }

    {
        stff::mtx2 lhs(1);
        stff::mtx2 rhs(2);
        std::cout << "lhs: " << std::endl << lhs << std::endl;
        std::cout << "rhs: " << std::endl << rhs << std::endl;
        std::cout << std::endl << "multiply" << std::endl << lhs * rhs << std::endl;
        std::cout << std::endl;
    }

    {
        stff::mtx4 lhs;
        lhs[0][0] = 0; lhs[0][1] = 4; lhs[0][2] = 8;  lhs[0][3] = 12;
        lhs[1][0] = 1; lhs[1][1] = 5; lhs[1][2] = 9;  lhs[1][3] = 13;
        lhs[2][0] = 2; lhs[2][1] = 6; lhs[2][2] = 10; lhs[2][3] = 14;
        lhs[3][0] = 3; lhs[3][1] = 7; lhs[3][2] = 11; lhs[3][3] = 15;
        stff::mtx4 rhs;
        rhs[0][0] = 0; rhs[0][1] = 4; rhs[0][2] = 8;  rhs[0][3] = 12;
        rhs[1][0] = 1; rhs[1][1] = 5; rhs[1][2] = 9;  rhs[1][3] = 13;
        rhs[2][0] = 2; rhs[2][1] = 6; rhs[2][2] = 10; rhs[2][3] = 14;
        rhs[3][0] = 3; rhs[3][1] = 7; rhs[3][2] = 11; rhs[3][3] = 15;
        std::cout << "lhs: " << std::endl << lhs << std::endl;
        std::cout << "rhs: " << std::endl << rhs << std::endl;
        std::cout << std::endl << "multiply" << std::endl << lhs * rhs << std::endl;
        std::cout << std::endl;
    }

    {
        stff::vec3 tmp(1, 0, 0);
        std::cout << "tmp: " << tmp << std::endl;
        std::cout << "rotated: " << stf::math::rotate(tmp, stff::vec3(0, 0, 1), stf::constants<float>::half_pi) << std::endl;
        std::cout << "rotated: " << stf::math::rotate(stff::vec3(0, 0, 1), stf::constants<float>::half_pi) * stff::vec4(tmp, 0) << std::endl;
        std::cout << std::endl;
    }

    {
        stff::vec3 tmp(0, -1, 0);
        float constexpr delta_phi = -stf::constants<float>::quarter_pi;
        float constexpr delta_theta= stf::constants<float>::half_pi;
        std::cout << "tmp: " << tmp << "   delta_phi: -pi/4    delta_theta: pi/2" << std::endl;
        std::cout << "desired: " << stff::vec3(0.707107, 0, 0.707107) << std::endl;
        stff::mtx4 mtx = stf::math::orbit(stff::vec3(), stff::vec3(1, 0, 0), delta_phi, delta_theta);
        std::cout << "orbited:" << mtx * stff::vec4(tmp, 1) << std::endl;
        std::cout << "orbited:" << stf::math::orbit(tmp, stff::vec3(), stff::vec3(1, 0, 0), delta_phi, delta_theta) << std::endl;
        std::cout << std::endl;
    }

    {
        float constexpr quarter_pi = stf::constants<float>::quarter_pi ;
        std::cout << "perspective:" << std::endl << stf::math::perspective(quarter_pi, 1.7777777f, 2.0f, 1000.0f) << std::endl;
        std::cout << std::endl;
    }
    return 0;
}