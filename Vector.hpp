#pragma once

#include <iostream>
#include <type_traits>
#include <memory>
#include <initializer_list>
#include <vector>

namespace atMath
{

    template <typename T>
    class Vector
    {
        static_assert(std::is_arithmetic<T>::value, "Numeric type required.");

    private:
        // T* v_data;
        std::unique_ptr<T[]> v_data;
        size_t v_size;

    public:
        Vector();
        Vector(size_t size);
        Vector(size_t size, T value);
        Vector(const Vector<T> &v);
        Vector(const std::vector<T> &v);
        Vector(std::initializer_list<T> list);
        ~Vector();
        size_t size() const;

        T &operator[](size_t index);
        const T &operator[](size_t index) const;

        template <typename U>
        auto operator+(const Vector<U> &v) const -> Vector<decltype(v_data[0] + v[0])>;

        template <typename U>
        auto operator-(const Vector<U> &v) const -> Vector<decltype(v_data[0] - v[0])>;

        // template <typename U>
        // auto operator*(const Vector<U>& v) const -> Vector<decltype(v_data[0] * v[0])>;

        template <typename U>
        auto operator*(const U &value) const -> Vector<decltype(v_data[0] * value)>;

        template <typename U>
        auto operator/(const U &value) const -> Vector<decltype(v_data[0] / value)>;

        template <typename U>
        Vector<T> &operator=(const Vector<U> &v);

        template <typename U>
        Vector<T> &operator+=(const Vector<U> &v);

        template <typename U>
        Vector<T> &operator-=(const Vector<U> &v);

        template <typename U>
        Vector<T> &operator*=(const Vector<U> &v);

        template <typename U>
        Vector<T> &operator*=(const U &value);

        template <typename U>
        Vector<T> &operator/=(const U &value);

        template <typename U>
        bool operator==(const Vector<U> &v) const;

        template <typename U>
        bool operator!=(const Vector<U> &v) const;

        template <typename U>
        auto dot(const Vector<U> &v) const -> decltype(v_data[0] * v[0]);

        template <typename U>
        auto operator*(const Vector<U> &v) -> decltype(v_data[0] * v[0]);

        template <typename U>
        auto cross(const Vector<U> &v) const -> Vector<decltype(v_data[0] * v[0])>;

        template <typename U>
        auto operator^(const Vector<U> &v) -> Vector<decltype(v_data[0] * v[0])>;

        template <typename U>
        auto product(const Vector<U> &v) const -> Vector<decltype(v_data[0] * v[0])>;

        auto inverse() const -> Vector<decltype(1 / v_data[0])>;

        T sum() const;

        double magnitude() const;
        auto normalize() const -> Vector<decltype(v_data[0] / magnitude())>;
       
        template <typename U>
        void resize(size_t size, U value);

        void resize(size_t size);
        void clear();

        template <typename U>
        void append(const U &value);

        template <typename U>
        void insert(size_t index, const U &value);

        template <typename U>
        void append(const Vector<U> &v);

        template <typename U>
        void insert(size_t index, const Vector<U> &v);

        friend std::ostream &operator<<(std::ostream &os, const Vector<T> &v)
        {
            os << "[";
            for (size_t i = 0; i < v.size(); i++)
            {
                os << v[i];
                if (i < v.size() - 1)
                {
                    os << ", ";
                }
            }
            os << "]";
            return os;
        }
    };
}
