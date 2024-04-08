#pragma once

#include <iostream>
#include <type_traits>
#include <iomanip>
#include <limits>
#include <cmath>
#include <iterator>
#include "Complex.hpp"

namespace atMath{

    template <class T = float>
    class Quaternion{
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    public:
        T real;
        T i;
        T j;
        T k;

        Quaternion(T real, T i, T j, T k);
        template <class U>
        Quaternion(U real, U i, U j, U k);
        Quaternion(const T real);
        template <class U>
        Quaternion(const U real);
        Quaternion(const Complex<T> &c);
        template <class U>
        Quaternion(const Complex<U> &c);
        Quaternion(const Quaternion<T> &q);
        template <class U>
        Quaternion(const Quaternion<U> &q);
        Quaternion();
        ~Quaternion();

        Quaternion<T> &operator=(const Quaternion<T> &q);
        template <class U>
        Quaternion<T> &operator=(const Quaternion<U> &q);
        template <class U>
        Quaternion<T> &operator+=(const Quaternion<U> &q);
        template <class U>
        Quaternion<T> &operator-=(const Quaternion<U> &q);
        template <class U>
        Quaternion<T> &operator*=(const Quaternion<U> &q);
        template <class U>
        Quaternion<T> &operator/=(const Quaternion<U> &q);

        template <class U>
        Quaternion<T> &operator+=(const Complex<U> &c);
        template <class U>
        Quaternion<T> &operator-=(const Complex<U> &c);
        template <class U>
        Quaternion<T> &operator*=(const Complex<U> &c);
        template <class U>
        Quaternion<T> &operator/=(const Complex<U> &c);

        template <class U>
        std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> operator+=(const U &value);
        template <class U>
        std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> operator-=(const U &value);
        template <class U>
        std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> operator*=(const U &value);
        template <class U>
        std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> operator/=(const U &value);

        Quaternion<T> operator-() const{
            return Quaternion<T>(-real, -i, -j, -k);
        }

        template <class U>
        operator U() const{
            return static_cast<U>(real);
        }

        double norm() const{
            return sqrt(real * real + i * i + j * j + k * k);
        }

        T norm_squared() const{
            return real * real + i * i + j * j + k * k;
        }

        Quaternion<T> conjugate() const{
            return Quaternion<T>(real, -i, -j, -k);
        }

        auto inverse() const -> Quaternion<decltype(1.f / (real * real + i * i + j * j + k * k))>{
            T norm_squared = real * real + i * i + j * j + k * k;
            Quaternion<decltype(1.f / norm_squared)> q(real, -i, -j, -k);
            q /= real * real + i * i + j * j + k * k;
            return q;
        }

        friend std::ostream &operator<<(std::ostream &os, const Quaternion<T> &q){
            os << std::fixed << std::setprecision(std::min(std::numeric_limits<T>::digits10, 2));
            bool real = false, i = false, j = false, k = false;
            if (q.real != 0){
                os << q.real;
                real = true;
            }
            if (q.i != 0){
                if (q.i > 0 && real)
                    os << " + ";
                else if (q.i < 0)
                    os << " - ";
                os << (std::abs(q.i) == 1 ? "" : std::to_string(std::abs(q.i))) << "i";
                i = true;
            }
            if (q.j != 0){
                if (q.j > 0 && (real || i))
                    os << " + ";
                else if (q.j < 0)
                    os << " - ";
                os << (std::abs(q.j) == 1 ? "" : std::to_string(std::abs(q.j))) << "j";
                j = true;
            }
            if (q.k != 0){
                if (q.k > 0 && (real || i || j))
                    os << " + ";
                else if (q.k < 0)
                    os << " - ";
                os << (std::abs(q.k) == 1 ? "" : std::to_string(std::abs(q.k))) << "k";
            }
            if (!(real || i || j || k))
                os << "0";
            return os;
        }

    };

    template <class T, class U>
    auto operator+(const Quaternion<T> &q1, const Quaternion<U> &q2) -> Quaternion<decltype(q1.real + q2.real)>;
    template <class T, class U>
    auto operator-(const Quaternion<T> &q1, const Quaternion<U> &q2) -> Quaternion<decltype(q1.real - q2.real)>;
    template <class T, class U>
    auto operator*(const Quaternion<T> &q1, const Quaternion<U> &q2) -> Quaternion<decltype(q1.real * q2.real)>;
    template <class T, class U>
    auto operator/(const Quaternion<T> &q1, const Quaternion<U> &q2) -> Quaternion<decltype(1.f /(q2.real * q2.real + q2.i * q2.i + q2.j * q2.j + q2.k * q2.k))>;

    template <class T, class U>
    auto operator+(const Quaternion<T> &q, const Complex<U> &c) -> Quaternion<decltype(q.real + c.real)>;
    template <class T, class U>
    auto operator+(const Complex<T> &c, const Quaternion<U> &q) -> Quaternion<decltype(c.real + q.real)>;
    template <class T, class U>
    auto operator-(const Quaternion<T> &q, const Complex<U> &c) -> Quaternion<decltype(q.real - c.real)>;
    template <class T, class U>
    auto operator-(const Complex<T> &c, const Quaternion<U> &q) -> Quaternion<decltype(c.real - q.real)>;
    template <class T, class U>
    auto operator*(const Quaternion<T> &q, const Complex<U> &c) -> Quaternion<decltype(q.real * c.real)>;
    template <class T, class U>
    auto operator*(const Complex<T> &c, const Quaternion<U> &q) -> Quaternion<decltype(c.real * q.real)>;
    template <class T, class U>
    auto operator/(const Quaternion<T> &q, const Complex<U> &c) -> Quaternion<decltype(1.f / (c.real * c.real + c.imag * c.image))>;
    template <class T, class U> 
    auto operator/(const Complex<T> &c, const Quaternion<U> &q) -> Quaternion<decltype(1.f / (q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k))>;

    template <class T, class U>
    auto operator+(const Quaternion<T> &q, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(q.real + value)>>;
    template <class T, class U>
    auto operator+(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(value + q.real)>>;
    template <class T, class U>
    auto operator-(const Quaternion<T> &q, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(q.real - value)>>;
    template <class T, class U>
    auto operator-(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(value - q.real)>>;
    template <class T, class U>
    auto operator*(const Quaternion<T> &q, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(q.real * value)>>;
    template <class T, class U>
    auto operator*(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(value * q.real)>>;
    template <class T, class U>
    auto operator/(const Quaternion<T> &q, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(1.f * q.real / value)>>;
    template <class T, class U>
    auto operator/(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(1.f / (q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k))>>;

}