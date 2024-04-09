#pragma once
#include "Vector.hpp"
#include "Complex.hpp"
#include "Quaternion.hpp"


namespace atMath{

    template <class T>
    class Vector;

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
        template <class U>
        Vec2(const Vector<U> &v) : Vector<T>(v) {}
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

    template <class T, class U> 
    auto operator*(const Complex<T> &c, const Vec2<U> &v) -> Vec2<decltype(c.real * v[0])>
    {
        Vec2<decltype(c.real * v[0])> result;
        result[0] = c.real * v[0] - c.imag * v[1];
        result[1] = c.real * v[1] + c.imag * v[0];
        return result;
    }

    template <class T, class U>
    auto operator*(const Vec2<U> &v, const Complex<T> &c) -> Vec2<decltype(v[0] * c.real)>
    {
        return c * v;
    }

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
        template <class U>
        Vec3(const Vector<U> &v) : Vector<T>(v) {}
        Vec3(std::initializer_list<T> list) : Vector<T>(list) {}
        void setX(T x) { Vector<T>::operator[](0) = x; }
        void setY(T y) { Vector<T>::operator[](1) = y; }
        void setZ(T z) { Vector<T>::operator[](2) = z; }

        Quaternion<T> toQuaternion() const{
            return Quaternion<T>(0,x,y,z);
        }

        static Quaternion<T> rotate(const Vec3<T> &axis, const double &angle){
            Vec3<double> axis_norm = axis.normalize();
            double s = sin(angle / 2);
            double c = cos(angle / 2);
            return Quaternion<T>(c, s * axis_norm.x, s * axis_norm.y, s * axis_norm.z);

        }

    };

    template <class T, class U> 
    auto operator*(const Quaternion<T> &q, const Vec3<U> &v) -> Vec3<decltype(q.real * v[0])>{
        Quaternion<U> q_u(0,v.x,v.y,v.z);
        Quaternion<decltype(q.real * v[0])> q_v = q * q_u * q.inverse();
        return Vec3<decltype(q.real * v[0])>(q_v.i,q_v.j,q_v.k);
    }
    template <class T, class U>
    auto operator*(const Vec3<U> &v, const Quaternion<T> &q) -> Vec3<decltype(v[0] * q.real)>{
        return q * v;
    }

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
        template <class U>
        Vec4(const Vector<U> &v) : Vector<T>(v) {}
        Vec4(std::initializer_list<T> list) : Vector<T>(list) {}
        void setX(T x) { Vector<T>::operator[](0) = x; }
        void setY(T y) { Vector<T>::operator[](1) = y; }
        void setZ(T z) { Vector<T>::operator[](2) = z; }
        void setW(T w) { Vector<T>::operator[](3) = w; }

    };

}