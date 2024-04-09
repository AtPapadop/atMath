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
#include "Quaternion.hpp"

namespace atMath
{   


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
        template <class U>
        Vector(const Vector<U> &v);
        Vector(const std::vector<T> &v);
        Vector(std::initializer_list<T> list);
        Vector(std::unique_ptr<T[]> v_data, size_t size);
        // Vector(const Vec2<T> &v);
        // Vector(const Vec3<T> &v);
        // Vector(const Vec4<T> &v);
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
        double magnitude() const;
        auto inverse() const -> Vector<decltype(1 / v_data[0])>;
        auto normalize() const -> Vector<decltype(v_data[0] / magnitude())>;
        void clear();

        template <class U>
        std::enable_if_t<std::is_arithmetic<U>::value, Vector<T>> append(const U &value);
        template <class U>
        std::enable_if_t<std::is_arithmetic<U>::value, Vector<T>> insert(size_t index, const U &value);
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

        
        // template <class U>
        // Vector<T> append(const Vec2<U> &v);
        // template <class U>
        // Vector<T> insert(size_t index, const Vec2<U> &v);
        // template <class U>
        // Vector<T> append(const Vec3<U> &v);
        // template <class U>
        // Vector<T> insert(size_t index, const Vec3<U> &v);
        // template <class U>
        // Vector<T> append(const Vec4<U> &v);
        // template <class U>
        // Vector<T> insert(size_t index, const Vec4<U> &v);

        Vector<T> subvector(size_t start, size_t end) const;
        Vector<T> subvector(size_t size) const;

        friend std::ostream &operator<<(std::ostream &os, const Vector<T> &v)
        {   
            os << std::fixed << std::setprecision(3);
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

    template <class T, class U>
    auto operator/(const Vector<T> &v, const Quaternion<U> &q) -> Vector<decltype(v[0] / q)>;

    template <class T, class U>
    auto operator/(const Quaternion<U> &q, const Vector<T> &v) -> Vector<decltype(q / v[0])>;


}

template <class T>
auto exp(const atMath::Vector<T> &v) -> atMath::Vector<decltype(exp(v[0]))>;

template <class T>
auto log(const atMath::Vector<T> &v) -> atMath::Vector<decltype(log(v[0]))>;
