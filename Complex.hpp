#pragma once

#include <iostream>
#include <type_traits>
#include <iomanip>
#include <limits>
#include <cmath>
#include <iterator>
#include "Vector.hpp"


namespace atMath
{
    template <class T = float>
    class Complex{
        //static_assert(std::is_arithmetic<T>::value, "Complex type must be arithmetic");
    public:
        T real;
        T imag;

        Complex(T real, T imag, bool is_polar = false);
        Complex(const T real);
        Complex(const Complex<T> &c);
        Complex();
        ~Complex();


        Complex<T> &operator=(const Complex<T> &c);
        template <class U>
        Complex<T> &operator=(const Complex<U> &c);
        template <class U>
        Complex<T> &operator+=(const Complex<U> &c);
        template <class U>
        Complex<T> &operator-=(const Complex<U> &c);
        template <class U>
        Complex<T> &operator*=(const Complex<U> &c);
        template <class U>
        Complex<T> &operator/=(const Complex<U> &c);

        template <class U>
        Complex<T> &operator=(const U &value);
        template <class U>
        Complex<T> &operator+=(const U &value);
        template <class U>
        Complex<T> &operator-=(const U &value);
        template <class U>
        Complex<T> &operator*=(const U &value);
        template <class U>
        Complex<T> &operator/=(const U &value);

        Complex<T> operator-() const{
            return Complex<T>(-real, -imag);
        }

        template <class U>
        operator U() const{
            return static_cast<U>(real);
        }

        template <class U>
        bool operator==(const Complex<U> &c) const;
        template <class U>
        bool operator!=(const Complex<U> &c) const;

        double modulus() const;
        double squared_modulus() const;

        Complex<double> pow(const double &epx);
        template <class U>
        Complex<double> pow(const Complex<U> &c);

        Complex<T> conjugate() const;


        friend std::ostream &operator<<(std::ostream &os, const Complex<T> &c){
            os << std::fixed << std::setprecision(std::min(std::numeric_limits<T>::digits10, 2));
            if (!c.real && !c.imag){
                os << 0;
            } else if (!c.real){
                if (c.imag == 1){
                    os << "i";
                } else if (c.imag == -1){
                    os << "-i";
                } else {
                    os << c.imag << "i";
                }
            } else if (!c.imag){
                os << c.real;
            } else {
                os << c.real;
                if (c.imag > 0){
                    os << " + " << c.imag << "i";
                } else {
                    os << " - " << -c.imag << "i";
                }
            }
            return os;
        }
    };

    template <class T>
    bool is_complex(const T &value);

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

    template <class T, class U>
    inline auto operator+(const Complex<T> &c1, const Complex<U> &c2) -> Complex<decltype(c1.real + c2.real)>{
        return Complex<decltype(c1.real + c2.real)>(c1.real + c2.real, c1.imag + c2.imag);
    }

    template <class T, class U>
    inline auto operator-(const Complex<T> &c1, const Complex<U> &c2) -> Complex<decltype(c1.real - c2.real)>{
        return Complex<decltype(c1.real - c2.real)>(c1.real - c2.real, c1.imag - c2.imag);
    }

    template <class T, class U>
    inline auto operator*(const Complex<T> &c1, const Complex<U> &c2) -> Complex<decltype(c1.real * c2.real)>{
        return Complex<decltype(c1.real * c2.real)>(c1.real * c2.real - c1.imag * c2.imag, c1.real * c2.imag + c1.imag * c2.real);
    }

    template <class T, class U>
    inline auto operator/(const Complex<T> &c1, const Complex<U> &c2) -> Complex<decltype(1.f * c1.real / c2.real)>{
        return Complex<decltype(1.f * c1.real / c2.real)>( 1.f *(c1.real * c2.real + c1.imag * c2.imag) / (c2.real * c2.real + c2.imag * c2.imag), 1.f *(c1.imag * c2.real - c1.real * c2.imag) / (c2.real * c2.real + c2.imag * c2.imag));
    }

    template <class T, class U>
    inline auto operator+(const Complex<T> &c, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real + value)>>{
        return Complex<decltype(c.real + value)>(c.real + value, c.imag);
    }

    template <class T, class U>
    inline auto operator+(const U &value, const Complex<T> &c) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real + value)>>{
        return c + value;
    }

    template <class T, class U>
    inline auto operator-(const Complex<T> &c, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real - value)>>{
        return Complex<decltype(c.real - value)>(c.real - value, c.imag);
    }

    template <class T, class U>
    inline auto operator-(const U &value, const Complex<T> &c) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(value - c.real)>>{
        return Complex<decltype(value - c.real)>(value - c.real, -c.imag);
    }

    template <class T, class U>
    inline auto operator*(const Complex<T> &c, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real * value)>>{
        return Complex<decltype(c.real * value)>(c.real * value, c.imag * value);
    }

    template <class T, class U>
    inline auto operator*(const U &value, const Complex<T> &c) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real * value)>>{
        return c * value;
    }

    template <class T, class U>
    inline auto operator/(const Complex<T> &c,const  U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(1.f *c.real / value)>>{
        return Complex<decltype(1.f * c.real / value)>(1.f * c.real / value,1.f * c.imag / value);
    }

    template <class T, class U>
    auto operator/(const U &value, const Complex<T> &c) -> std::enable_if_t<std::is_arithmetic<U>::value,Complex<decltype(1.f * value * c.real / c.squared_modulus())>>{
        double mod_rev = 1.f / c.squared_modulus();
        Complex<decltype(value * c.real * mod_rev)> result(c.real * mod_rev, -c.imag * mod_rev);
        return result * value;
    }


};


template <class T>
atMath::Complex<double> sqrt(const atMath::Complex<T> &c);

template <class T, class U>
atMath::Complex<double> pow(const U &value, const atMath::Complex<T> &c);
