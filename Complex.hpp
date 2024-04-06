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
        Complex<T> conjugate() const;




        friend std::ostream &operator<<(std::ostream &os, const Complex<T> &c){
            os << std::setprecision(std::min(std::numeric_limits<T>::digits10, 6));
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


}


template <class T>
atMath::Complex<double> sqrt(const atMath::Complex<T> &c);
