#pragma once

#include <iostream>
#include <type_traits>

namespace atMath
{
    template <class T = float>
    class Complex{
    public:
        T real;
        T imag;

        Complex(T real, T imag, bool is_polar = false);
        Complex(const T real);
        Complex(const Complex<T> &c);
        template <class U>
        Complex(const Complex<U> &c);
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
        bool operator==(const Complex<U> &c) const;
        template <class U>
        bool operator!=(const Complex<U> &c) const;

        double modulus() const;
        T squared_modulus() const;

        Complex<double> pow(const double &epx);
        template <class U>
        Complex<double> pow(const Complex<U> &c);
        Complex<T> conjugate() const;
        double argz() const;
        
        static Complex<T> rotate(const double &angle);


        friend std::ostream &operator<<(std::ostream &os, const Complex<T> &c){
            os << std::fixed << std::setprecision(2);
            float epsilon = 0.01f;
            if (std::abs(c.real) < epsilon && std::abs(c.imag) < epsilon){
                os << 0;
            } else if (std::abs(c.real) < epsilon){
                if (c.imag == 1){
                    os << "i";
                } else if (c.imag == -1){
                    os << "-i";
                } else {
                    os << c.imag << "i";
                }
            } else if (std::abs(c.imag) < epsilon){
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

    template <class T, class U>
    inline auto operator+(const Complex<T> &c1, const Complex<U> &c2) -> Complex<decltype(c1.real + c2.real)>;
    template <class T, class U>
    inline auto operator-(const Complex<T> &c1, const Complex<U> &c2) -> Complex<decltype(c1.real - c2.real)>;
    template <class T, class U>
    inline auto operator*(const Complex<T> &c1, const Complex<U> &c2) -> Complex<decltype(c1.real * c2.real)>;
    template <class T, class U>
    inline auto operator/(const Complex<T> &c1, const Complex<U> &c2) -> Complex<decltype(1.f * c1.real / c2.real)>;

    template <class T, class U>
    inline auto operator+(const Complex<T> &c, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real + value)>>;
    template <class T, class U>
    inline auto operator+(const U &value, const Complex<T> &c) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real + value)>>;
    template <class T, class U>
    inline auto operator-(const Complex<T> &c, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real - value)>>;
    template <class T, class U>
    inline auto operator-(const U &value, const Complex<T> &c) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(value - c.real)>>;
    template <class T, class U>
    inline auto operator*(const Complex<T> &c, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real * value)>>;
    template <class T, class U>
    inline auto operator*(const U &value, const Complex<T> &c) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(c.real * value)>>;
    template <class T, class U>
    inline auto operator/(const Complex<T> &c, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Complex<decltype(1.f * c.real / value)>>;
    template <class T, class U>
    auto operator/(const U &value, const Complex<T> &c) -> std::enable_if_t<std::is_arithmetic<U>::value,Complex<decltype(1.f * value * c.real / c.squared_modulus())>>;

};


template <class T>
atMath::Complex<double> sqrt(const atMath::Complex<T> &c);

template <class T>
atMath::Complex<double> log(const atMath::Complex<T> &c);

template <class T>
atMath::Complex<double> exp(const atMath::Complex<T> &c);