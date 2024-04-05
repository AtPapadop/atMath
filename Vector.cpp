#include "Vector.hpp"
#include "Complex.hpp"
#include <cmath>
#include <map>



namespace atMath
{
    std::map<std::string, std::string> type_map = {
    {"c", "char"},
    {"i", "int"},
    {"f", "float"},
    {"d", "double"},
    {"j", "uint32_t"},
    {"y", "uint64_t"},
    {"i", "int32_t"},
    {"x", "int64_t"},
    {"h", "uint8_t"},
    {"a", "int8_t"},
    {"t", "uint16_t"},
    {"s", "int16_t"},
    {"N6atMath7ComplexIiEE", "complex int"},
    {"N6atMath7ComplexIfEE", "complex float"},
    {"N6atMath7ComplexIdEE", "complex double"},
    {"N6atMath7ComplexIjEE", "complex uint32_t"},
    {"N6atMath7ComplexIyEE", "complex uint64_t"},
    {"N6atMath7ComplexIiEE", "complex int32_t"},
    {"N6atMath7ComplexIxEE", "complex int64_t"},
    {"N6atMath7ComplexIhEE", "complex uint8_t"},
    {"N6atMath7ComplexIaEE", "complex int8_t"},
    {"N6atMath7ComplexItEE", "complex uint16_t"},
    {"N6atMath7ComplexIsEE", "complex int16_t"}};

    template <class T>
    Vector<T>::Vector()
    {
        static_assert(std::is_arithmetic<T>::value || std::is_base_of<Complex<int>, T>::value || std::is_base_of<Complex<float>, T>::value || std::is_base_of<Complex<double>, T>::value || std::is_base_of<Complex<uint32_t>, T>::value || std::is_base_of<Complex<uint64_t>, T>::value || std::is_base_of<Complex<int32_t>, T>::value || std::is_base_of<Complex<int64_t>, T>::value || std::is_base_of<Complex<uint8_t>, T>::value || std::is_base_of<Complex<int8_t>, T>::value || std::is_base_of<Complex<uint16_t>, T>::value || std::is_base_of<Complex<int16_t>, T>::value, "Vector type must be arithmetic or Complex"); 


        v_data(nullptr);
        v_size = 0;
    }

    template <class T>
    Vector<T>::Vector(size_t size)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_base_of<Complex<int>, T>::value || std::is_base_of<Complex<float>, T>::value || std::is_base_of<Complex<double>, T>::value || std::is_base_of<Complex<uint32_t>, T>::value || std::is_base_of<Complex<uint64_t>, T>::value || std::is_base_of<Complex<int32_t>, T>::value || std::is_base_of<Complex<int64_t>, T>::value || std::is_base_of<Complex<uint8_t>, T>::value || std::is_base_of<Complex<int8_t>, T>::value || std::is_base_of<Complex<uint16_t>, T>::value || std::is_base_of<Complex<int16_t>, T>::value, "Vector type must be arithmetic or Complex"); 
        try{
            v_data = std::make_unique<T[]>(size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        v_size = size;
    }

    template <class T>
    Vector<T>::Vector(size_t size, T value)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_base_of<Complex<int>, T>::value || std::is_base_of<Complex<float>, T>::value || std::is_base_of<Complex<double>, T>::value || std::is_base_of<Complex<uint32_t>, T>::value || std::is_base_of<Complex<uint64_t>, T>::value || std::is_base_of<Complex<int32_t>, T>::value || std::is_base_of<Complex<int64_t>, T>::value || std::is_base_of<Complex<uint8_t>, T>::value || std::is_base_of<Complex<int8_t>, T>::value || std::is_base_of<Complex<uint16_t>, T>::value || std::is_base_of<Complex<int16_t>, T>::value, "Vector type must be arithmetic or Complex"); 

        try{
        v_data = std::make_unique<T[]>(size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        v_size = size;
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] = value;
        }
    }

    template <class T>
    Vector<T>::Vector(const Vector<T> &v)
    {
        v_size = v.size();

        try{
        v_data = std::make_unique<T[]>(v_size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }


        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] = v[i];
        }
    }

    template <class T>
    Vector<T>::Vector(const std::vector<T> &v)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_base_of<Complex<int>, T>::value || std::is_base_of<Complex<float>, T>::value || std::is_base_of<Complex<double>, T>::value || std::is_base_of<Complex<uint32_t>, T>::value || std::is_base_of<Complex<uint64_t>, T>::value || std::is_base_of<Complex<int32_t>, T>::value || std::is_base_of<Complex<int64_t>, T>::value || std::is_base_of<Complex<uint8_t>, T>::value || std::is_base_of<Complex<int8_t>, T>::value || std::is_base_of<Complex<uint16_t>, T>::value || std::is_base_of<Complex<int16_t>, T>::value, "Vector type must be arithmetic or Complex"); 
        v_size = v.size();

        try{
        v_data = std::make_unique<T[]>(v_size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

  
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] = v[i];
        }

    }

    template <class T>
    Vector<T>::Vector(std::initializer_list<T> list)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_base_of<Complex<int>, T>::value || std::is_base_of<Complex<float>, T>::value || std::is_base_of<Complex<double>, T>::value || std::is_base_of<Complex<uint32_t>, T>::value || std::is_base_of<Complex<uint64_t>, T>::value || std::is_base_of<Complex<int32_t>, T>::value || std::is_base_of<Complex<int64_t>, T>::value || std::is_base_of<Complex<uint8_t>, T>::value || std::is_base_of<Complex<int8_t>, T>::value || std::is_base_of<Complex<uint16_t>, T>::value || std::is_base_of<Complex<int16_t>, T>::value, "Vector type must be arithmetic or Complex"); 
        v_size = list.size();

        try{
        v_data = std::make_unique<T[]>(v_size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        size_t i = 0;
        for (auto it = list.begin(); it != list.end(); it++)
        {
            v_data[i] = *it;
            i++;
        }
    }

    template <class T>
    Vector<T>::Vector(std::unique_ptr<T[]> data, size_t size)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_base_of<Complex<int>, T>::value || std::is_base_of<Complex<float>, T>::value || std::is_base_of<Complex<double>, T>::value || std::is_base_of<Complex<uint32_t>, T>::value || std::is_base_of<Complex<uint64_t>, T>::value || std::is_base_of<Complex<int32_t>, T>::value || std::is_base_of<Complex<int64_t>, T>::value || std::is_base_of<Complex<uint8_t>, T>::value || std::is_base_of<Complex<int8_t>, T>::value || std::is_base_of<Complex<uint16_t>, T>::value || std::is_base_of<Complex<int16_t>, T>::value, "Vector type must be arithmetic or Complex"); 
        v_size = size;
        v_data.swap(data);
    }

    template <class T>
    Vector<T>::Vector(const Vec2<T> &v)
    {
        v_size = 2;

        try{
        v_data = std::make_unique<T[]>(v_size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        v_data[0] = v.x;
        v_data[1] = v.y;
    }

    template <class T>
    Vector<T>::Vector(const Vec3<T> &v)
    {
        v_size = 3;

        try{
        v_data = std::make_unique<T[]>(v_size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        v_data[0] = v.x;
        v_data[1] = v.y;
        v_data[2] = v.z;
    }

    template <class T>
    Vector<T>::Vector(const Vec4<T> &v)
    {
        v_size = 4;

        try{
        v_data = std::make_unique<T[]>(v_size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        v_data[0] = v.x;
        v_data[1] = v.y;
        v_data[2] = v.z;
        v_data[3] = v.w;
    }

    template <class T>
    Vector<T>::Vector(const Complex<T> &c)
    {
        v_size = 2;

        try{
        v_data = std::make_unique<T[]>(v_size);
        }catch(const std::bad_alloc& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        v_data[0] = c.real;
        v_data[1] = c.imag;
    }

    template <class T>
    Vector<T>::~Vector()
    {
        if (v_data != nullptr)
        {

            v_data.reset();
        }
    }

    template <class T>
    size_t Vector<T>::size() const
    {
        return v_size;
    }

    template <class T>
    Vector<T> Vector<T>::repeat(size_t size, T value)
    {
        Vector<T> result(size);
        for (size_t i = 0; i < size; i++)
        {
            result[i] = value;
        }
        return result;
    }

    template <class T>
    T &Vector<T>::operator[](size_t index)
    {
        if (index >= v_size)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        return v_data[index];
    }

    template <class T>
    const T &Vector<T>::operator[](size_t index) const
    {
        if (index >= v_size)
        {
            throw std::out_of_range("Index out of bounds.");
        }
        return v_data[index];
    }

    template <class T>
    template <class U>
    Vector<T> &Vector<T>::operator=(const Vector<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        if (*this != v)
        {

            v_data.reset();
            v_size = v.size();
            v_data = std::make_unique<T[]>(v_size);
            for (size_t i = 0; i < v_size; i++)
            {
                v_data[i] = static_cast<T>(v[i]);
            }
        }
        return *this;
    }

    template <class T>
    template <class U>
    auto Vector<T>::operator+(const Vector<U> &v) const -> Vector<decltype(v_data[0] + v[0])>
    {
        if (v_size != v.size())
        {
            throw std::runtime_error("Vectors must be the same size to add.");
        }
        
        // decltype(v_data[0] + v[0]) test = v_data[0] + v[0];
        // std::cout << "Type: " << typeid(test).name() << std::endl;
        // std::cout << "value: " << test << std::endl;
        Vector<decltype(v_data[0] + v[0])> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i] + v[i];
        }
        return result;
    }

    template <class T>
    template <class U>
    auto Vector<T>::operator-(const Vector<U> &v) const -> Vector<decltype(v_data[0] - v[0])>
    {
        if (v_size != v.size())
        {
            throw std::runtime_error("Vectors must be the same size to subtract.");
        }
        Vector<decltype(v_data[0] - v[0])> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i] - v[i];
        }
        return result;
    }

    template <class T>
    template <class U>
    auto Vector<T>::operator*(const U &value) const -> Vector<decltype(v_data[0] * value)>
    {
        Vector<decltype(v_data[0] * value)> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i] * value;
        }
        return result;
    }

    template <class T>
    template <class U>
    auto Vector<T>::operator/(const U &value) const -> Vector<decltype(v_data[0] / value)>
    {
        Vector<decltype(v_data[0] / value)> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i] / value;
        }
        return result;
    }

    template <class T>
    template <class U>
    Vector<T> &Vector<T>::operator+=(const Vector<U> &v)
    {
        if (v_size != v.size())
        {
            throw std::runtime_error("Vectors must be the same size to add.");
        }
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] += static_cast<T>(v[i]);
        }
        return *this;
    }

    template <class T>
    template <class U>
    Vector<T> &Vector<T>::operator-=(const Vector<U> &v)
    {
        if (v_size != v.size())
        {
            throw std::runtime_error("Vectors must be the same size to subtract.");
        }
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] -= static_cast<T>(v[i]);
        }
        return *this;
    }

    template <class T>
    template <class U>
    Vector<T> &Vector<T>::operator*=(const Vector<U> &v)
    {
        if (v_size != v.size())
        {
            throw std::runtime_error("Vectors must be the same size to multiply.");
        }
        if (typeid(T) != typeid(decltype(v[0] * v_data[0])))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(decltype(v[0] * v_data[0])).name()) != type_map.end() ? type_map[typeid(decltype(v[0] * v_data[0])).name()] : typeid(decltype(v[0] * v_data[0])).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] *= static_cast<T>(v[i]);
        }
        return *this;
    }

    template <class T>
    template <class U>
    Vector<T> &Vector<T>::operator*=(const U &value)
    {
        if (typeid(T) != typeid(decltype(value * v_data[0])))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(decltype(value * v_data[0])).name()) != type_map.end() ? type_map[typeid(decltype(value * v_data[0])).name()] : typeid(decltype(value * v_data[0])).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] *= value;
        }
        return *this;
    }

    template <class T>
    template <class U>
    bool Vector<T>::operator==(const Vector<U> &v) const
    {
        if (v_size != v.size())
        {
            return false;
        }

        float epsilon = 0.0001;

        for (size_t i = 0; i < v_size; i++)
        {
            if (abs(v_data[i] - v[i]) > epsilon)
            {
                return false;
            }
        }
        return true;
    }

    template <class T>
    template <class U>
    bool Vector<T>::operator!=(const Vector<U> &v) const
    {
        return !(*this == v);
    }


    template <class T>
    template <class U>
    auto Vector<T>::dot(const Vector<U> &v) const -> decltype(v_data[0] * v[0])
    {
        if (v_size != v.size())
        {
            throw std::runtime_error("Vectors must be the same size to take the dot product.");
        }
        decltype(v_data[0] * v[0]) result = 0;
        for (size_t i = 0; i < v_size; i++)
        {
            result += v_data[i] * v[i];
        }
        return result;
    }

    template <class T>
    template <class U>
    auto Vector<T>::operator*(const Vector<U> &v) -> decltype(v_data[0] * v[0])
    {
        return dot(v);
    }

    template <class T>
    template <class U>
    auto Vector<T>::cross(const Vector<U> &v) const -> Vector<decltype(v_data[0] * v[0])>
    {
        if (v_size != 3 || v.size() != 3)
        {
            throw std::runtime_error("Cross product requires two 3D vectors.");
        }
        Vector<decltype(v_data[0] * v[0])> result(3);
        result[0] = v_data[1] * v[2] - v_data[2] * v[1];
        result[1] = v_data[2] * v[0] - v_data[0] * v[2];
        result[2] = v_data[0] * v[1] - v_data[1] * v[0];
        return result;
    }

    template <class T>
    template <class U>
    auto Vector<T>::operator^(const Vector<U> &v) -> Vector<decltype(v_data[0] * v[0])>
    {
        return cross(v);
    }

    template <class T>
    template <class U>
    double Vector<T>::angle(const Vector<U> &v, bool deg) const
    {
        if (v_size != v.size())
        {
            throw std::runtime_error("Vectors must be the same size to calculate the angle.");
        }
        double angle = acos(dot(v) / (magnitude() * v.magnitude()));
        if (deg)
        {
            angle = angle * 180 / M_PI;
        }
        return angle;
    }

    template <class T>
    template <class U, class V>
    double Vector<T>::angle(const Vector<U> &v1, const Vector<V> &v2, bool deg)
    {
        return v1.angle(v2, deg);
    }

    template <class T>
    template <class U>
    auto Vector<T>::product(const Vector<U>& v) const -> Vector<decltype(v_data[0] * v[0])>{
        if (v_size != v.size()){
            throw std::runtime_error("Vectors must be the same size to multiply.");
        }
        Vector<decltype(v_data[0] * v[0])> result(v_size);
        for(size_t i = 0; i < v_size; i++){
            result[i] = v_data[i] * v[i];
        }
        return result;
    }

    template <class T>
    auto Vector<T>::inverse() const -> Vector<decltype(1 / v_data[0])>
    {
        Vector<decltype(1 / v_data[0])> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = 1 / v_data[i];
        }
        return result;
    }

    template <class T>
    T Vector<T>::sum() const
    {
        T result = 0;
        for (size_t i = 0; i < v_size; i++)
        {
            result += v_data[i];
        }
        return result;
    }

    template <class T>
    auto Vector<T>::magnitude() const -> decltype(sqrt(v_data[0] * v_data[0]))
    {
        decltype(v_data[0] * v_data[0]) result = 0;
        for (size_t i = 0; i < v_size; i++)
        {
            result += v_data[i] * v_data[i];
        }
        return sqrt(result);
    }

    template <class T>
    auto Vector<T>::normalize() const -> Vector<decltype(v_data[0] / magnitude())>
    {
        Vector<decltype(v_data[0] / magnitude())> result(v_size);
        double mag = magnitude();
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i] / mag;
        }
        return result;
    }

    template <class T>
    void Vector<T>::clear()
    {

        v_data.reset();
        v_data(nullptr);
        v_size = 0;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::append(const U &value)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        Vector<T> result(v_size + 1);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i];
        }
  
        result[v_size] = value;

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::insert(size_t index, const U &value)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        Vector<T> result(v_size + 1);
        for (size_t i = 0; i < index; i++)
        {
            result[i] = v_data[i];
        }
        result[index] = value;
        for (size_t i = index; i < v_size; i++)
        {
            result[i + 1] = v_data[i];
        }

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::append(const Vector<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        Vector<T> result(v_size + v.size());
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i];
        }
        for (size_t i = 0; i < v.size(); i++)
        {
            result[v_size + i] = v[i];
        }

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::insert(size_t index, const Vector<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        Vector result(v_size + v.size());
        for (size_t i = 0; i < index; i++)
        {
            result[i] = v_data[i];
        }
        for (size_t i = 0; i < v.size(); i++)
        {
            result[index + i] = v[i];
        }
        for (size_t i = index; i < v_size; i++)
        {
            result[i + v.size()] = v_data[i];
        }

       return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::append(const std::vector<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        Vector<T> result(v_size + v.size());
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i];
        }
        for (size_t i = 0; i < v.size(); i++)
        {
            result[v_size + i] = v[i];
        }

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::insert(size_t index, const std::vector<U> &v)
    {
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        Vector<T> result(v_size + v.size());
        for (size_t i = 0; i < index; i++)
        {
            result[i] = v_data[i];
        }
        for (size_t i = 0; i < v.size(); i++)
        {
            result[index + i] = v[i];
        }
        for (size_t i = index; i < v_size; i++)
        {
            result[i + v.size()] = v_data[i];
        }

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::append(const std::initializer_list<U> &list)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        Vector<T> result(v_size + list.size());
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i];
        }
        size_t j = 0;
        for (auto it = list.begin(); it != list.end(); it++)
        {
            result[v_size + j] = *it;
            j++;
        }

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::insert(size_t index, const std::initializer_list<U> &list)
    {
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        Vector<T> result(v_size + list.size());
        for (size_t i = 0; i < index; i++)
        {
            result[i] = v_data[i];
        }
        size_t j = 0;
        for (auto it = list.begin(); it != list.end(); it++)
        {
            result[index + j] = *it;
            j++;
        }
        for (size_t i = index; i < v_size; i++)
        {
            result[i + list.size()] = v_data[i];
        }

        return result;
    }

    // apend and insert for Vec2, Vec3, Vec4

    template <class T>
    template <class U>
    Vector<T> Vector<T>::append(const Vec2<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        Vector<T> result(v_size + 2);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i];
        }
        result[v_size] = v[0];
        result[v_size + 1] = v[1];

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::insert(size_t index, const Vec2<U> &v)
    {
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        Vector<T> result(v_size + 2);
        for (size_t i = 0; i < index; i++)
        {
            result[i] = v_data[i];
        }
        result[index] = v[0];
        result[index + 1] = v[1];
        for (size_t i = index; i < v_size; i++)
        {
            result[i + 2] = v_data[i];
        }

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::append(const Vec3<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        Vector<T> result(v_size + 3);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i];
        }
        result[v_size] = v[0];
        result[v_size + 1] = v[1];
        result[v_size + 2] = v[2];

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::insert(size_t index, const Vec3<U> &v)
    {
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        Vector<T> result(v_size + 3);
        for (size_t i = 0; i < index; i++)
        {
            result[i] = v_data[i];
        }
        result[index] = v[0];
        result[index + 1] = v[1];
        result[index + 2] = v[2];
        for (size_t i = index; i < v_size; i++)
        {
            result[i + 3] = v_data[i];
        }

        return result;
    }
    
    template <class T>
    template <class U>
    Vector<T> Vector<T>::append(const Vec4<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        Vector<T> result(v_size + 4);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i];
        }
        result[v_size] = v[0];
        result[v_size + 1] = v[1];
        result[v_size + 2] = v[2];
        result[v_size + 3] = v[3];

        return result;
    }

    template <class T>
    template <class U>
    Vector<T> Vector<T>::insert(size_t index, const Vec4<U> &v)
    {
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        Vector<T> result(v_size + 4);
        for (size_t i = 0; i < index; i++)
        {
            result[i] = v_data[i];
        }
        result[index] = v[0];
        result[index + 1] = v[1];
        result[index + 2] = v[2];
        result[index + 3] = v[3];
        for (size_t i = index; i < v_size; i++)
        {
            result[i + 4] = v_data[i];
        }

        return result;
    }

    

    template <class T>
    Vector<T> Vector<T>::subvector(size_t start, size_t end) const
    {
        if (start > end || end > v_size)
        {
            throw std::runtime_error("Invalid start or end index.");
        }
        Vector<T> result(end - start);
        for (size_t i = start; i < end; i++)
        {
            result[i - start] = v_data[i];
        }
        return result;
    }

    template <class T>
    Vector<T> Vector<T>::subvector(size_t size) const
    {
        return subvector(0, size);
    }

}
