#pragma once

#include "Vector.hpp"
#include "Complex.hpp"
#include "Quaternion.hpp"


namespace atMath{

    typedef Vector<float> Vecf;
    typedef Vector<double> Vecd;
    typedef Vector<int> Veci;


    typedef Vec2<float> Vec2f;
    typedef Vec2<double> Vec2d;
    typedef Vec2<int> Vec2i;
    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;
    typedef Vec3<int> Vec3i;
    typedef Vec4<float> Vec4f;
    typedef Vec4<double> Vec4d;
    typedef Vec4<int> Vec4i;

    typedef Complex<int> int_c;
    typedef Complex<float> float_c;
    typedef Complex<double> double_c;
    typedef Complex<uint32_t> uint32_c;
    typedef Complex<uint64_t> uint64_c;
    typedef Complex<int32_t> int32_c;
    typedef Complex<int64_t> int64_c;
    typedef Complex<uint8_t> uint8_c;
    typedef Complex<int8_t> int8_c;
    typedef Complex<uint16_t> uint16_c;
    typedef Complex<int16_t> int16_c;

    typedef Quaternion<int> int_q;
    typedef Quaternion<float> float_q;
    typedef Quaternion<double> double_q;
    typedef Quaternion<uint32_t> uint32_q;
    typedef Quaternion<uint64_t> uint64_q;
    typedef Quaternion<int32_t> int32_q;
    typedef Quaternion<int64_t> int64_q;
    typedef Quaternion<uint8_t> uint8_q;
    typedef Quaternion<int8_t> int8_q;
    typedef Quaternion<uint16_t> uint16_q;
    typedef Quaternion<int16_t> int16_q;

    typedef Vector<int_c> Veci_c;
    typedef Vector<float_c> Vecf_c;
    typedef Vector<double_c> Vecd_c;

    typedef Vector<int_q> Veci_q;
    typedef Vector<float_q> Vecf_q;
    typedef Vector<double_q> Vecd_q;

    typedef Vec2<int_c> Vec2i_c;
    typedef Vec2<float_c> Vec2f_c;
    typedef Vec2<double_c> Vec2d_c;

    typedef Vec2<int_q> Vec2i_q;
    typedef Vec2<float_q> Vec2f_q;
    typedef Vec2<double_q> Vec2d_q;

    typedef Vec3<int_c> Vec3i_c;
    typedef Vec3<float_c> Vec3f_c;
    typedef Vec3<double_c> Vec3d_c;

    typedef Vec3<int_q> Vec3i_q;
    typedef Vec3<float_q> Vec3f_q;
    typedef Vec3<double_q> Vec3d_q;

    typedef Vec4<int_c> Vec4i_c;
    typedef Vec4<float_c> Vec4f_c;
    typedef Vec4<double_c> Vec4d_c;
}