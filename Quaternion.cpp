#include "Quaternion.hpp"

namespace atMath{

    template <class T>
    Quaternion<T>::Quaternion(T real, T i, T j, T k) : real(real), i(i), j(j), k(k){
        static_assert(std::is_arithmetic<T>::value, "Quaternion type must be arithmetic");
    }

    template <class T>
    Quaternion<T>::Quaternion(const T real) : real(real), i(0), j(0), k(0){
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
        T a = real;
        T b = i;
        T c = j;
        T d = k;

        T e = static_cast<T>(q.real);
        T f = static_cast<T>(q.i);
        T g = static_cast<T>(q.j);
        T h = static_cast<T>(q.k);

        real = a * e - b * f - c * g - d * h;
        i = a * f + b * e + c * h - d * g;  
        j = a * g - b * h + c * e + d * f;
        k = a * h + b * g - c * f + d * e;
        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator/=(const Quaternion<U> &q){
        T q0 = real;
        T q1 = i;
        T q2 = j;
        T q3 = k;

        T r0 = static_cast<T>(q.real);
        T r1 = static_cast<T>(q.i);
        T r2 = static_cast<T>(q.j);
        T r3 = static_cast<T>(q.k);

        T norm_squared = r0 * r0 + r1 * r1 + r2 * r2 + r3 * r3;

        real = (q0 * r0 + q1 * r1 + q2 * r2 + q3 * r3) / norm_squared;
        i = (q1 * r0 - q0 * r1 - q3 * r2 + q2 * r3) / norm_squared;
        j = (q2 * r0 + q3 * r1 - q0 * r2 - q1 * r3) / norm_squared;
        k = (q3 * r0 - q2 * r1 + q1 * r2 - q0 * r3) / norm_squared;

        return *this;
    }

    template <class T>
    template <class U>
    Quaternion<T> &Quaternion<T>::operator=(const Complex<U> &c){
        real = static_cast<T>(c.real);
        i = static_cast<T>(c.imag);
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
    std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<T> &> Quaternion<T>::operator=(const U &value){
        real = static_cast<T>(value);
        i = 0;
        j = 0;
        k = 0;
        return *this;
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

    template <class T>
    template <class U>
    bool Quaternion<T>::operator==(const Quaternion<U> &q) const{
        float epsilon = 0.00001f;
        return std::abs(real - static_cast<T>(q.real)) < epsilon && std::abs(i - static_cast<T>(q.i)) < epsilon && std::abs(j - static_cast<T>(q.j)) < epsilon && std::abs(k - static_cast<T>(q.k)) < epsilon;
    }

    template <class T>
    template <class U>
    bool Quaternion<T>::operator!=(const Quaternion<U> &q) const{
        return !(*this == q);
    }

    template <class T>
    double Quaternion<T>::modulus() const{
        return std::sqrt(real * real + i * i + j * j + k * k);
    }

    template <class T>
    T Quaternion<T>::modulus_squared() const{
        return real * real + i * i + j * j + k * k;
    }

    template <class T>
    Quaternion<double> Quaternion<T>::pow(const double &exp) const{
        double norm = modulus();
        double v_norm = std::sqrt(i * i + j * j + k * k);
        double exp_real = std::pow(norm, exp) * std::cos(exp * std::acos(real / norm));
        double exp_imag = std::pow(norm, exp) * std::sin(exp * std::acos(real / norm)) / v_norm;
        return Quaternion<double>(exp_real, exp_imag * i, exp_imag * j, exp_imag * k);
    }

    template <class T>
    template <class U>
    Quaternion<double> Quaternion<T>::pow(const Quaternion<U> &q) const{
        double norm = modulus();
        double v_norm = std::sqrt(i * i + j * j + k * k);
        double exp_real = std::pow(norm, q.real) * std::cos(q.real * std::acos(real / norm));
        double exp_imag = std::pow(norm, q.real) * std::sin(q.real * std::acos(real / norm)) / v_norm;
        Quaternion<double> q1(exp_real, exp_imag * i, exp_imag * j, exp_imag * k);
        return q1 * q / q.modulus();
    }

    template <class T>
    template <class U>
    Quaternion<double> Quaternion<T>::pow(const Complex<U> &c) const{
        Quaternion<double> q(c);
        return pow(q);
    }
    
    template <class T>
    Quaternion<T> Quaternion<T>::conjugate() const{
        return Quaternion<T>(real, -i, -j, -k);
    }

    template <class T>
    auto Quaternion<T>::inverse() const -> Quaternion<decltype(1.f / (real * real + i * i + j * j + k * k))>{
        T norm_squared = real * real + i * i + j * j + k * k;
        Quaternion<decltype(1.f / norm_squared)> q(real, -i, -j, -k);
        q /= norm_squared;
        return q;
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
        Quaternion<decltype(c.real * q.real)> q1(c);
        q1 *= q;
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
        Quaternion<decltype(1.f * q.real / value)> q1 = 1.f * q;
        //std::cout << 1.f *q << std::endl;
        q1 /= 1.f * value;
        return q1;
    }

    template <class T, class U>
    auto operator/(const U &value, const Quaternion<T> &q) -> std::enable_if_t<std::is_arithmetic<U>::value, Quaternion<decltype(1.f / (q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k))>>{
        Quaternion<decltype(1.f / (q.real * q.real + q.i * q.i + q.j * q.j + q.k * q.k))> q1(1.f *value);
        q1 /= q;
        return q1;
    }

    const Quaternion<int> j(0, 0, 1, 0);
    const Quaternion<int> k(0, 0, 0, 1); 

}

template <class T>
atMath::Quaternion<double> exp(const atMath::Quaternion<T> &q){
    double v_norm = std::sqrt(q.i * q.i + q.j * q.j + q.k * q.k);
    double exp_real = std::exp(q.real) * std::cos(v_norm);
    double exp_imag = std::exp(q.real) * std::sin(v_norm) / v_norm;
    return atMath::Quaternion<double>(exp_real, exp_imag * q.i, exp_imag * q.j, exp_imag * q.k);
}

template <class T>
atMath::Quaternion<double> log(const atMath::Quaternion<T> &q){
    double norm = q.modulus();
    double v_norm = std::sqrt(q.i * q.i + q.j * q.j + q.k * q.k);
    double log_real = std::log(norm);
    double log_imag = std::acos(q.real / norm) / v_norm;
    return atMath::Quaternion<double>(log_real, log_imag * q.i, log_imag * q.j, log_imag * q.k);
}