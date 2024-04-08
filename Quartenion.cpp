#include "Quartenion.hpp"

namespace atMath{

    template <class T>
    Quaternion<T>::Quaternion(T real, T i, T j, T k) : real(real), i(i), j(j), k(k){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    template <class U>
    Quaternion<T>::Quaternion(U real, U i, U j, U k) : real(static_cast<T>(real)), i(static_cast<T>(i)), j(static_cast<T>(j)), k(static_cast<T>(k)){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    Quaternion<T>::Quaternion(const T real) : real(real), i(0), j(0), k(0){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    template <class U>
    Quaternion<T>::Quaternion(const U real) : real(static_cast<T>(real)), i(0), j(0), k(0){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    Quaternion<T>::Quaternion(const Complex<T> &c) : real(c.real), i(c.imag), j(0), k(0){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    template <class U>
    Quaternion<T>::Quaternion(const Complex<U> &c) : real(static_cast<T>(c.real)), i(static_cast<T>(c.imag)), j(0), k(0){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    Quaternion<T>::Quaternion(const Quaternion<T> &q) : real(q.real), i(q.i), j(q.j), k(q.k){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    template <class U>
    Quaternion<T>::Quaternion(const Quaternion<U> &q) : real(static_cast<T>(q.real)), i(static_cast<T>(q.i)), j(static_cast<T>(q.j)), k(static_cast<T>(q.k)){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    Quaternion<T>::Quaternion() : real(0), i(0), j(0), k(0){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    Quaternion<T>::~Quaternion(){}

    template <class T>
    Quaternion<T> &Quaternion<T>::operator=(const Quaternion<T> &q){
        if (this != &q){
            real = q.real;
            i = q.i;
            j = q.j;
            k = q.k;
        }
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator=(const Quaternion<U> &q){
        real = static_cast<T>(q.real);
        i = static_cast<T>(q.i);
        j = static_cast<T>(q.j);
        k = static_cast<T>(q.k);
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator+=(const Quaternion<U> &q){
        real += static_cast<T>(q.real);
        i += static_cast<T>(q.i);
        j += static_cast<T>(q.j);
        k += static_cast<T>(q.k);
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator-=(const Quaternion<U> &q){
        real -= static_cast<T>(q.real);
        i -= static_cast<T>(q.i);
        j -= static_cast<T>(q.j);
        k -= static_cast<T>(q.k);
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator*=(const Quaternion<U> &q){
        T temp_real = real;
        T temp_i = i;
        T temp_j = j;
        T temp_k = k;

        real = temp_real * static_cast<T>(q.real) - temp_i * static_cast<T>(q.i) - temp_j * static_cast<T>(q.j) - temp_k * static_cast<T>(q.k);
        i = temp_real * static_cast<T>(q.i) + temp_i * static_cast<T>(q.real) + temp_j * static_cast<T>(q.k) - temp_k * static_cast<T>(q.j);
        j = temp_real * static_cast<T>(q.j) - temp_i * static_cast<T>(q.k) + temp_j * static_cast<T>(q.real) + temp_k * static_cast<T>(q.i);
        k = temp_real * static_cast<T>(q.k) + temp_i * static_cast<T>(q.j) - temp_j * static_cast<T>(q.i) + temp_k * static_cast<T>(q.real);
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator/=(const Quaternion<U> &q){
        T temp_real = real;
        T temp_i = i;
        T temp_j = j;
        T temp_k = k;

        T norm = q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k;
        real = (temp_real * static_cast<T>(q.real) + temp_i * static_cast<T>(q.i) + temp_j * static_cast<T>(q.j) + temp_k * static_cast<T>(q.k)) / norm;
        i = (temp_real * static_cast<T>(q.i) - temp_i * static_cast<T>(q.real) - temp_j * static_cast<T>(q.k) + temp_k * static_cast<T>(q.j)) / norm;
        j = (temp_real * static_cast<T>(q.j) + temp_i * static_cast<T>(q.k) - temp_j * static_cast<T>(q.real) - temp_k * static_cast<T>(q.i)) / norm;
        k = (temp_real * static_cast<T>(q.k) - temp_i * static_cast<T>(q.j) + temp_j * static_cast<T>(q.i) - temp_k * static_cast<T>(q.real)) / norm;
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator+=(const Complex<U> &c){
        real += static_cast<T>(c.real);
        i += static_cast<T>(c.imag);
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator-=(const Complex<U> &c){
        real -= static_cast<T>(c.real);
        i -= static_cast<T>(c.imag);
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator*=(const Complex<U> &c){
        Quaternion<T> q(c);
        return *this *= q;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator/=(const Complex<U> &c){
        Quaternion<T> q(c);
        return *this /= q;
    }

    template <class T>
    template <class U>
    std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> Quaternion<T>::operator+=(const U &value){
        real += static_cast<T>(value);
        return *this;
    }

    template <class T>
    template <class U>
    std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> Quaternion<T>::operator-=(const U &value){
        real -= static_cast<T>(value);
        return *this;
    }

    template <class T>
    template <class U>
    std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> Quaternion<T>::operator*=(const U &value){
        real *= static_cast<T>(value);
        i *= static_cast<T>(value);
        j *= static_cast<T>(value);
        k *= static_cast<T>(value);
        return *this;
    }

    template <class T>
    template <class U>
    std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> Quaternion<T>::operator/=(const U &value){
        real /= static_cast<T>(value);
        i /= static_cast<T>(value);
        j /= static_cast<T>(value);
        k /= static_cast<T>(value);
        return *this;
    }

    template <class T, class U>
    auto operator+(const Quaternion<T> &q1, const Quaternion<U> &q2) -> Quaternion<decltype(q1.real + q2.real)>{
        Quaternion<decltype(q1.real + q2.real)> q(q1);
        q += q2;
        return q;
    }

    template <class T, class U>
    auto operator-(const Quaternion<T> &q1, const Quaternion<U> &q2) -> Quaternion<decltype(q1.real - q2.real)>{
        Quaternion<decltype(q1.real - q2.real)> q(q1);
        q -= q2;
        return q;
    }

    template <class T, class U>
    auto operator*(const Quaternion<T> &q1, const Quaternion<U> &q2) -> Quaternion<decltype(q1.real * q2.real)>{
        Quaternion<decltype(q1.real * q2.real)> q(q1);
        q *= q2;
        return q;
    }
    
    template <class T, class U>
    auto operator/(const Quaternion<T> &q1, const Quaternion<U> &q2) -> Quaternion<decltype(1.f /(q2.real * q2.real + q2.i * q2.i + q2.j * q2.j + q2.k * q2.k))>{
        Quaternion<decltype(1.f /(q2.real * q2.real + q2.i * q2.i + q2.j * q2.j + q2.k * q2.k))> q(1.f * q1);
        q /= q2;
        return q;
    }

    template <class T, class U>
    auto operator+(const Quaternion<T> &q, const Complex<U> &c) -> Quaternion<decltype(q.real + c.real)>{
        Quaternion<decltype(q.real + c.real)> q1(q);
        q1 += c;
        return q1;
    }

    template <class T, class U>
    auto operator+(const Complex<T> &c, const Quaternion<U> &q) -> Quaternion<decltype(c.real + q.real)>{
        Quaternion<decltype(c.real + q.real)> q1(q);
        q1 += c;
        return q1;
    }

    template <class T, class U>
    auto operator-(const Quaternion<T> &q, const Complex<U> &c) -> Quaternion<decltype(q.real - c.real)>{
        Quaternion<decltype(q.real - c.real)> q1(q);
        q1 -= c;
        return q1;
    }

    template <class T, class U>
    auto operator-(const Complex<T> &c, const Quaternion<U> &q) -> Quaternion<decltype(c.real - q.real)>{
        Quaternion<decltype(c.real - q.real)> q1(-q);
        q1 += c;
        return q1;
    }

    template <class T, class U>
    auto operator*(const Quaternion<T> &q, const Complex<U> &c) -> Quaternion<decltype(q.real * c.real)>{
        Quaternion<decltype(q.real * c.real)> q1(q);
        q1 *= c;
        return q1;
    }

    template <class T, class U>
    auto operator*(const Complex<T> &c, const Quaternion<U> &q) -> Quaternion<decltype(c.real * q.real)>{
        Quaternion<decltype(c.real * q.real)> q1(q);
        q1 *= c;
        return q1;
    }

    template <class T, class U>
    auto operator/(const Quaternion<T> &q, const Complex<U> &c) -> Quaternion<decltype(1.f / (c.real * c.real + c.imag * c.image))>{
        Quaternion<decltype(1.f / (c.real * c.real + c.imag * c.image))> q1(1.f * q);
        q1 /= c;
        return q1;
    }

    template <class T, class U> 
    auto operator/(const Complex<T> &c, const Quaternion<U> &q) -> Quaternion<decltype(1.f / (q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k))>{
        Quaternion<decltype(1.f / (q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k))> q1(1.f *c);
        q1 /= q;
        return q1;
    }

    template <class T, class U>
    auto operator+(const Quaternion<T> &q, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(q.real + value)>>{
        Quaternion<decltype(q.real + value)> q1(q);
        q1 += value;
        return q1;
    }

    template <class T, class U>
    auto operator+(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(value + q.real)>>{
        Quaternion<decltype(value + q.real)> q1(q);
        q1 += value;
        return q1;
    }

    template <class T, class U>
    auto operator-(const Quaternion<T> &q, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(q.real - value)>>{
        Quaternion<decltype(q.real - value)> q1(q);
        q1 -= value;
        return q1;
    }

    template <class T, class U>
    auto operator-(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(value - q.real)>>{
        Quaternion<decltype(value - q.real)> q1(-q);
        q1 += value;
        return q1;
    }

    template <class T, class U>
    auto operator*(const Quaternion<T> &q, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(q.real * value)>>{
        Quaternion<decltype(q.real * value)> q1(q);
        q1 *= value;
        return q1;
    }

    template <class T, class U>
    auto operator*(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(value * q.real)>>{
        Quaternion<decltype(value * q.real)> q1(q);
        q1 *= value;
        return q1;
    }

    template <class T, class U>
    auto operator/(const Quaternion<T> &q, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(1.f * q.real / value)>>{
        Quaternion<decltype(1.f * q.real / value)> q1(1.f * q);
        q1 /= 1.f * value;
        return q1;
    }

    template <class T, class U>
    auto operator/(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(1.f / (q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k))>>{
        Quaternion<decltype(1.f / (q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k))> q1(1.f *value);
        q1 /= q;
        return q1;
    }


}