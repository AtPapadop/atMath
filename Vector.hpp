#pragma once

#include <iostream>
#include <type_traits>
#include <iomanip>
#include <limits>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <vector>
#include "Complex.hpp"
#include "Quartenion.hpp"

namespace atMath
{   
    const double PI = 3.14159265358979323846;

    template <class T>
    class Vector;

    template <class T>
    class Vec2;

    template <class T>
    class Vec3;

    template <class T>
    class Vec4;

    template <class T = float>
    class Vector
    {

    protected:
        std::unique_ptr<T[]> v_data;
        size_t v_size;

    public:

        using iterator = T *;
        using const_iterator = const T *;

        iterator begin() { return v_data.get(); }
        iterator end() { return v_data.get() + v_size; }
        const_iterator begin() const { return v_data.get(); }
        const_iterator end() const { return v_data.get() + v_size; }


        Vector();
        Vector(size_t size);
        Vector(size_t size, T value);
        Vector(const Vector<T> &v);
        Vector(const std::vector<T> &v);
        Vector(std::initializer_list<T> list);
        Vector(std::unique_ptr<T[]> v_data, size_t size);
        Vector(const Vec2<T> &v);
        Vector(const Vec3<T> &v);
        Vector(const Vec4<T> &v);
        Vector(const Complex<T> &c);
        ~Vector();

        size_t size() const;

        static Vector<T> repeat(size_t size, T value);
        template <class U>
        static Vector<U> repeat(size_t size, U value);

        T &operator[](size_t index);
        const T &operator[](size_t index) const;

        Vector<T> &operator=(const Vector<T> &v);
        template <class U>
        Vector<T> &operator=(const Vector<U> &v);
        template <class U>
        Vector<T> &operator+=(const Vector<U> &v);
        template <class U>
        Vector<T> &operator-=(const Vector<U> &v);
        template <class U>
        Vector<T> &operator*=(const Vector<U> &v);


        template <class U>
        Vector<T> &operator*=(const U &value);
        template <class U>
        Vector<T> &operator/=(const U &value);

        template <class U>
        bool operator==(const Vector<U> &v) const;
        template <class U>
        bool operator!=(const Vector<U> &v) const;



        template <class U>
        auto dot(const Vector<U> &v) const -> decltype(v_data[0] * v[0]);
        template <class U>
        auto cross(const Vector<U> &v) const -> Vector<decltype(v_data[0] * v[0])>;
        template <class U>
        auto operator^(const Vector<U> &v) -> Vector<decltype(v_data[0] * v[0])>;


        template <class U>
        double angle(const Vector<U> &v, bool deg = false) const;
        template <class U, class V>
        static double angle(const Vector<U> &v1, const Vector<V> &v2, bool deg = false);
        template <class U>
        auto product(const Vector<U> &v) const -> Vector<decltype(v_data[0] * v[0])>;

        T sum() const;
        auto magnitude() const -> decltype(sqrt(v_data[0] * v_data[0]));

        auto inverse() const -> Vector<decltype(1 / v_data[0])>;
        auto normalize() const -> Vector<decltype(v_data[0] / magnitude())>;
        void clear();

        template <class U>
        Vector<T> append(const U &value);
        template <class U>
        Vector<T> insert(size_t index, const U &value);
        template <class U>
        Vector<T> append(const Vector<U> &v);
        template <class U>
        Vector<T> insert(size_t index, const Vector<U> &v);
        template <class U>
        Vector<T> append(const std::vector<U> &v);
        template <class U>
        Vector<T> insert(size_t index, const std::vector<U> &v);
        template <class U>
        Vector<T> append(const std::initializer_list<U> &list);
        template <class U>
        Vector<T> insert(size_t index, const std::initializer_list<U> &list);

        
        template <class U>
        Vector<T> append(const Vec2<U> &v);
        template <class U>
        Vector<T> insert(size_t index, const Vec2<U> &v);
        template <class U>
        Vector<T> append(const Vec3<U> &v);
        template <class U>
        Vector<T> insert(size_t index, const Vec3<U> &v);
        template <class U>
        Vector<T> append(const Vec4<U> &v);
        template <class U>
        Vector<T> insert(size_t index, const Vec4<U> &v);

        Vector<T> subvector(size_t start, size_t end) const;
        Vector<T> subvector(size_t size) const;

        friend std::ostream &operator<<(std::ostream &os, const Vector<T> &v)
        {   
            os << std::fixed << std::setprecision(std::numeric_limits<T>::digits10 + 1);
            os << "[";
            for (auto i = v.begin(); i != v.end(); i++)
            {
                os << *i;
                if (i != v.end() - 1)
                {
                    os << ", ";
                }
            }
            os << "]";
            return os;
        }
    };

    typedef Vector<float> Vecf;
    typedef Vector<double> Vecd;
    typedef Vector<int> Veci;

    template <class T>
    class Vec2 : public Vector<T>
    {
    public:
        T &x = Vector<T>::operator[](0);
        T &y = Vector<T>::operator[](1);
        Vec2() : Vector<T>(2) {}
        Vec2(T x_, T y_) : Vector<T>(2)
        {
            Vector<T>::operator[](0) = x_;
            Vector<T>::operator[](1) = y_;
        }
        Vec2(const Vector<T> &v) : Vector<T>(v) {}
        Vec2(std::initializer_list<T> list) : Vector<T>(list) {}
        Vec2(const Complex<T> &c) : Vector<T>(c) {}
        void setX(T x) { Vector<T>::operator[](0) = x; }
        void setY(T y) { Vector<T>::operator[](1) = y; }

        Vec2<T> &operator=(const Complex<T> &c)
        {
            Vector<T>::operator[](0) = c.real;
            Vector<T>::operator[](1) = c.imag;
            return *this;
        }

        template <class U>
        Vec2<T> &operator=(const Complex<U> &c)
        {
            Vector<T>::operator[](0) = static_cast<T>(c.real);
            Vector<T>::operator[](1) = static_cast<T>(c.imag);
            return *this;  
        }

        Vec2<T> rotate(double angle, bool deg = false) const;

    
    };
    template <class T>
    class Vec3 : public Vector<T>
    {
    public:
        T &x = Vector<T>::operator[](0);
        T &y = Vector<T>::operator[](1);
        T &z = Vector<T>::operator[](2);
        Vec3() : Vector<T>(3)
        {
        }
        Vec3(T x_, T y_, T z_) : Vector<T>(3)
        {
            Vector<T>::operator[](0) = x_;
            Vector<T>::operator[](1) = y_;
            Vector<T>::operator[](2) = z_;
        }
        Vec3(const Vector<T> &v) : Vector<T>(v) {}
        Vec3(std::initializer_list<T> list) : Vector<T>(list) {}
        void setX(T x) { Vector<T>::operator[](0) = x; }
        void setY(T y) { Vector<T>::operator[](1) = y; }
        void setZ(T z) { Vector<T>::operator[](2) = z; }

    };

    template <class T>
    class Vec4 : public Vector<T>
    {
    public:
        T &x = Vector<T>::operator[](0);
        T &y = Vector<T>::operator[](1);
        T &z = Vector<T>::operator[](2);
        T &w = Vector<T>::operator[](3);
        Vec4() : Vector<T>(4) {}
        Vec4(T x_, T y_, T z_, T w_) : Vector<T>(4)
        {
            Vector<T>::operator[](0) = x_;
            Vector<T>::operator[](1) = y_;
            Vector<T>::operator[](2) = z_;
            Vector<T>::operator[](3) = w_;
        }
        Vec4(const Vector<T> &v) : Vector<T>(v) {}
        Vec4(std::initializer_list<T> list) : Vector<T>(list) {}
        void setX(T x) { Vector<T>::operator[](0) = x; }
        void setY(T y) { Vector<T>::operator[](1) = y; }
        void setZ(T z) { Vector<T>::operator[](2) = z; }
        void setW(T w) { Vector<T>::operator[](3) = w; }

    };


    template <class T, class U>
    auto operator+(const Vector<T> &v1, const Vector<U> &v2) -> Vector<decltype(v1[0] + v2[0])>;

    template <class T, class U>
    auto operator-(const Vector<T> &v1, const Vector<U> &v2) -> Vector<decltype(v1[0] - v2[0])>;

    template <class T, class U>
    auto operator*(const Vector<T> &v1, const Vector<U> &v2) -> decltype(v1[0] * v2[0]);

    template <class T, class U>
    auto operator*(const Vector<T> &v, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Vector<decltype(v[0] * value)>>;

    template <class T, class U>
    auto operator*(const U &value, const Vector<T> &v) -> std::enable_if_t<std::is_arithmetic<U>::value, Vector<decltype(v[0] * value)>>;

    template <class T, class U>
    auto operator*(const Vector<T> &v, const Complex<U> &c) -> Vector<decltype(v[0] * c)>;

    template <class T, class U>
    auto operator*(const Complex<U> &c, const Vector<T> &v) -> Vector<decltype(c * v[0])>;

    template <class T, class U>
    auto operator*(const Vector<T> &v, const Quaternion<U> &q) -> Vector<decltype(v[0] * q)>;

    template <class T, class U>
    auto operator*(const Quaternion<U> &q, const Vector<T> &v) -> Vector<decltype(q * v[0])>;

    template <class T, class U>
    auto operator/(const Vector<T> &v, const U &value) -> std::enable_if_t<std::is_arithmetic<U>::value, Vector<decltype(v[0] / value)>>;

    template <class T, class U>
    auto operator/(const U &value, const Vector<T> &v) -> std::enable_if_t<std::is_arithmetic<U>::value, Vector<decltype(value / v[0])>>;

    template <class T, class U>
    auto operator/(const Vector<T> &v, const Complex<U> &c) -> Vector<decltype(v[0] / c)>;

    template <class T, class U>
    auto operator/(const Complex<U> &c, const Vector<T> &v) -> Vector<decltype(c / v[0])>;

    typedef Vec2<float> Vec2f;
    typedef Vec2<double> Vec2d;
    typedef Vec2<int> Vec2i;
    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;
    typedef Vec3<int> Vec3i;
    typedef Vec4<float> Vec4f;
    typedef Vec4<double> Vec4d;
    typedef Vec4<int> Vec4i;

}
