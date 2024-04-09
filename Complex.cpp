#include "Complex.hpp"
#include <cmath>



namespace atMath{


    template <class T>
    Complex<T>::Complex(T real, T imag, bool is_polar) : real(real), imag(imag){
        static_assert(std::is_arithmetic<T>::value, "Complex type must be arithmetic");
        if (is_polar){
            this->real = real * cos(imag);
            this->imag = real * sin(imag);
        }
    }

    template <class T>
    Complex<T>::Complex(const T real) : real(real), imag(0) {
        static_assert(std::is_arithmetic<T>::value, "Complex type must be arithmetic");
    }

    template <class T>
    Complex<T>::Complex(const Complex<T> &c) : real(c.real), imag(c.imag) {
        static_assert(std::is_arithmetic<T>::value, "Complex type must be arithmetic");
    }

    template <class T>
    template <class U>
    Complex<T>::Complex(const Complex<U> &c) : real(static_cast<T>(c.real)), imag(static_cast<T>(c.imag)) {
        static_assert(std::is_arithmetic<T>::value, "Complex type must be arithmetic");
    }

    template <class T>
    Complex<T>::Complex() : real(0), imag(0) {
        static_assert(std::is_arithmetic<T>::value, "Complex type must be arithmetic");
    }

    template <class T>
    Complex<T>::~Complex() {}


    template <class T>
    Complex<T> &Complex<T>::operator=(const Complex<T> &c){
        if (this != &c){
            real = c.real;
            imag = c.imag;
        }
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator=(const Complex<U> &c){
        real = static_cast<T>(c.real);
        imag = static_cast<T>(c.imag);
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator+=(const Complex<U> &c){
        real += static_cast<T>(c.real);
        imag += static_cast<T>(c.imag);
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator-=(const Complex<U> &c){
        real -= static_cast<T>(c.real);
        imag -= static_cast<T>(c.imag);
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator*=(const Complex<U> &c){
        T temp = real;
        real = real * static_cast<T>(c.real) - imag * static_cast<T>(c.imag);
        imag = temp * static_cast<T>(c.imag) + imag * static_cast<T>(c.real);
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator/=(const Complex<U> &c){
        T temp = real;
        real = (real * static_cast<T>(c.real) + imag * static_cast<T>(c.imag)) / (c.real * c.real + c.imag * c.imag);
        imag = (imag * static_cast<T>(c.real) - temp * static_cast<T>(c.imag)) / (c.real * c.real + c.imag * c.imag);
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator=(const U &value){
        real = static_cast<T>(value);
        imag = 0;
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator+=(const U &value){
        real += static_cast<T>(value);
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator-=(const U &value){
        real -= static_cast<T>(value);
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator*=(const U &value){
        *this = *this * value;
        return *this;
    }

    template <class T>
    template <class U>
    Complex<T> &Complex<T>::operator/=(const U &value){
        *this = *this / value;
        return *this;
    }

    template <class T>
    template <class U>
    bool Complex<T>::operator==(const Complex<U> &c) const{
        float epsilon = 0.00001f;
        return abs(real - c.real) < epsilon && abs(imag - c.imag) < epsilon;
    }

    template <class T>
    template <class U>
    bool Complex<T>::operator!=(const Complex<U> &c) const{
        return !(*this == c);
    }

    template <class T>
    double Complex<T>::modulus() const{
        return sqrt(real * real + imag * imag);
    }

    template <class T>
    T Complex<T>::squared_modulus() const{
        return real * real + imag * imag;
    }

    template <class T>
    Complex<double> Complex<T>::pow(const double &epx){
        double r = std::pow(modulus(), epx);
        double theta = atan2(imag, real);
        return Complex<double>(r * cos(theta * epx), r * sin(theta * epx));
    }

    template <class T>
    template <class U>
    Complex<double> Complex<T>::pow(const Complex<U> &c){
        double r = std::pow(modulus(), c.real) * exp(-c.imag * atan2(imag, real));
        double theta = c.real * atan2(imag, real) + 0.5 * c.imag * log(squared_modulus());
        return Complex<double>(r * cos(theta), r * sin(theta));
    }
    
    template <class T>
    Complex<T> Complex<T>::conjugate() const{
        return Complex<T>(real, -imag);
    }

    template <class T>
    double Complex<T>::argz() const{
        return atan2(imag, real);
    }

    template <class T>
    Complex<T> Complex<T>::rotate(const double &angle){
        return Complex<T>(cos(angle), sin(angle));
    }

    template <class T>
    bool is_complex(const T &value){
        const std::type_info &type = typeid(value);
        return std::is_base_of<Complex<int>, T>::value || std::is_base_of<Complex<float>, T>::value || std::is_base_of<Complex<double>, T>::value || std::is_base_of<Complex<uint32_t>, T>::value || std::is_base_of<Complex<uint64_t>, T>::value || std::is_base_of<Complex<int32_t>, T>::value || std::is_base_of<Complex<int64_t>, T>::value || std::is_base_of<Complex<uint8_t>, T>::value || std::is_base_of<Complex<int8_t>, T>::value || std::is_base_of<Complex<uint16_t>, T>::value || std::is_base_of<Complex<int16_t>, T>::value;
    }

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

    const Complex<int> i(0, 1);
}

template <class T>
atMath::Complex<double> sqrt(const atMath::Complex<T> &c){
    double r = sqrt(c.modulus());
    double theta = atan2(c.imag, c.real);
    return atMath::Complex<double>(r * cos(theta / 2), r * sin(theta / 2));
}

template <class T>
atMath::Complex<double> log(const atMath::Complex<T> &c){
    return atMath::Complex<double>(log(c.modulus()), atan2(c.imag, c.real));
}
template <class T> 
atMath::Complex<double> exp(const atMath::Complex<T> &c){
    return atMath::Complex<double>(exp(c.real) * cos(c.imag), exp(c.real) * sin(c.imag));
}







