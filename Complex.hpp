#pragma once

#include <iostream>
#include <type_traits>
#include <iomanip>
#include <limits>
#include <cmath>
#include <iterator>


namespace atMath
{
    template <class T = float>
    class Complex{
        //static_assert(std::is_arithmetic<T>::value, "Complex type must be arithmetic");
    public:
        T real;
        T imag;

        Complex(T real, T imag);
        Complex(const T real);
        Complex(const Complex<T> &c);
        Complex();
        ~Complex();


        template <class U>
        auto operator+(const Complex<U> &c) const -> Complex<decltype(real + c.real)>;
        template <class U>
        auto operator-(const Complex<U> &c) const -> Complex<decltype(real - c.real)>;
        template <class U>
        auto operator*(const Complex<U> &c) const -> Complex<decltype(real * c.real)>;
        template <class U>
        auto operator/(const Complex<U> &c) const -> Complex<decltype(real / c.real)>;

        template <class U>
        auto operator+(const U &value) const -> Complex<decltype(real + value)>;
        template <class U>
        auto operator-(const U &value) const -> Complex<decltype(real - value)>;
        template <class U>
        auto operator*(const U &value) const -> Complex<decltype(real * value)>;
        template <class U>
        auto operator/(const U &value) const -> Complex<decltype(real / value)>;


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
        Complex<T> conjugate() const;




        friend std::ostream &operator<<(std::ostream &os, const Complex<T> &c){
            os << std::setprecision(std::min(std::numeric_limits<T>::digits10, 6));
            if (!c.real && !c.imag){
                os << 0;
            } else if (!c.real){
                os << c.imag << "i";
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
    auto operator/(int value, const Complex<T> &c) -> Complex<decltype(c.real / c.squared_modulus())>;


    template <class T>
    bool is_complex(const T &value);
}


template <class T>
atMath::Complex<double> sqrt(const atMath::Complex<T> &c);
