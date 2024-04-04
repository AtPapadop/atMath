#include "Vector.hpp"
#include <cmath>
#include <map>



namespace atMath
{
    std::map<std::string, std::string> type_map = {
    {"c", "char"},
    {"h", "signed char"},
    {"H", "unsigned char"},
    {"i", "int"},
    {"j", "unsigned int"},
    {"l", "long"},
    {"L", "unsigned long"},
    {"x", "long long int"},
    {"y", "unsigned long long int"},
    {"q", "long long"},
    {"Q", "unsigned long long"},
    {"f", "float"},
    {"d", "double"},
    {"e", "long double"},
    {"b", "bool"},
    {"s", "std::string"},
    {"v", "void"}};

    template <typename T>
    Vector<T>::Vector()
    {
        static_assert(std::is_arithmetic<T>::value, "Numeric type required.");

        v_data(nullptr);
        v_size = 0;
    }

    template <typename T>
    Vector<T>::Vector(size_t size)
    {
        static_assert(std::is_arithmetic<T>::value, "Numeric type required.");

        v_data = std::make_unique<T[]>(size);
        ;
        v_size = size;
    }

    template <typename T>
    Vector<T>::Vector(size_t size, T value)
    {
        static_assert(std::is_arithmetic<T>::value, "Numeric type required.");

        v_data = std::make_unique<T[]>(size);
        ;
        v_size = size;
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] = value;
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector<T> &v)
    {
        static_assert(std::is_arithmetic<T>::value, "Numeric type required.");
        v_size = v.size();

        v_data = std::make_unique<T[]>(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] = v[i];
        }
    }

    template <typename T>
    Vector<T>::Vector(const std::vector<T> &v)
    {
        static_assert(std::is_arithmetic<T>::value, "Numeric type required.");
        v_size = v.size();

        v_data = std::make_unique<T[]>(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            v_data[i] = v[i];
        }
    }

    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> list)
    {
        static_assert(std::is_arithmetic<T>::value, "Numeric type required.");
        v_size = list.size();

        v_data = std::make_unique<T[]>(v_size);
        size_t i = 0;
        for (auto it = list.begin(); it != list.end(); it++)
        {
            v_data[i] = *it;
            i++;
        }
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        if (v_data != nullptr)
        {

            v_data.reset();
        }
    }

    template <typename T>
    size_t Vector<T>::size() const
    {
        return v_size;
    }

    template <typename T>
    T &Vector<T>::operator[](size_t index)
    {
        return v_data[index];
    }

    template <typename T>
    const T &Vector<T>::operator[](size_t index) const
    {
        return v_data[index];
    }

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
    auto Vector<T>::operator+(const Vector<U> &v) const -> Vector<decltype(v_data[0] + v[0])>
    {
        if (v_size != v.size())
        {
            throw std::runtime_error("Vectors must be the same size to add.");
        }
        Vector<decltype(v_data[0] + v[0])> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i] + v[i];
        }
        return result;
    }

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
    auto Vector<T>::operator*(const U &value) const -> Vector<decltype(v_data[0] * value)>
    {
        Vector<decltype(v_data[0] * value)> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i] * value;
        }
        return result;
    }

    template <typename T>
    template <typename U>
    auto Vector<T>::operator/(const U &value) const -> Vector<decltype(v_data[0] / value)>
    {
        Vector<decltype(v_data[0] / value)> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = v_data[i] / value;
        }
        return result;
    }

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
    bool Vector<T>::operator!=(const Vector<U> &v) const
    {
        return !(*this == v);
    }

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
    auto Vector<T>::operator*(const Vector<U> &v) -> decltype(v_data[0] * v[0])
    {
        return dot(v);
    }

    template <typename T>
    template <typename U>
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

    template <typename T>
    template <typename U>
    auto Vector<T>::operator^(const Vector<U> &v) -> Vector<decltype(v_data[0] * v[0])>
    {
        return cross(v);
    }

    template <typename T>
    template <typename U>
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

    template <typename T>
    auto Vector<T>::inverse() const -> Vector<decltype(1 / v_data[0])>
    {
        Vector<decltype(1 / v_data[0])> result(v_size);
        for (size_t i = 0; i < v_size; i++)
        {
            result[i] = 1 / v_data[i];
        }
        return result;
    }

    template <typename T>
    T Vector<T>::sum() const
    {
        T result = 0;
        for (size_t i = 0; i < v_size; i++)
        {
            result += v_data[i];
        }
        return result;
    }

    template <typename T>
    double Vector<T>::magnitude() const
    {
        double result = 0;
        for (size_t i = 0; i < v_size; i++)
        {
            result += v_data[i] * v_data[i];
        }
        return sqrt(result);
    }

    template <typename T>
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


    template <typename T>
    template <typename U>
    void Vector<T>::resize(size_t size, U value)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        std::unique_ptr<T[]> new_data(new T[size]);
        for (size_t i = 0; i < size; i++)
        {
            if (i < v_size)
            {
                new_data[i] = v_data[i];
            }
            else
            {
                new_data[i] = static_cast<T>(value);
            }
        }

        v_data.swap(new_data);
        v_size = size;
    }

    template <typename T>
    void Vector<T>::resize(size_t size)
    {

        std::unique_ptr<T[]> new_data(new T[size]);
        for (size_t i = 0; i < size; i++)
        {
            if (i < v_size)
            {
                new_data[i] = v_data[i];
            }
            else
            {
                new_data[i] = 0;
            }
        }

        v_data.swap(new_data);
        v_size = size;
    }

    template <typename T>
    void Vector<T>::clear()
    {

        v_data.reset();
        v_data(nullptr);
        v_size = 0;
    }

    template <typename T>
    template <typename U>
    void Vector<T>::append(const U &value)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        std::unique_ptr<T[]> new_data(new T[v_size + 1]);
        for (size_t i = 0; i < v_size; i++)
        {
            new_data[i] = v_data[i];
        }
        new_data[v_size] = static_cast<T>(value);

        v_data.swap(new_data);
        v_size++;
    }

    template <typename T>
    template <typename U>
    void Vector<T>::insert(size_t index, const U &value)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        std::unique_ptr<T[]> new_data(new T[v_size + 1]);
        for (size_t i = 0; i < index; i++)
        {
            new_data[i] = v_data[i];
        }
        new_data[index] = static_cast<T>(value);
        for (size_t i = index; i < v_size; i++)
        {
            new_data[i + 1] = v_data[i];
        }

        v_data.swap(new_data);
        v_size++;
    }

    template <typename T>
    template <typename U>
    void Vector<T>::append(const Vector<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }

        std::unique_ptr<T[]> new_data(new T[v_size + v.size()]);
        for (size_t i = 0; i < v_size; i++)
        {
            new_data[i] = v_data[i];
        }
        for (size_t i = 0; i < v.size(); i++)
        {
            new_data[v_size + i] = static_cast<T>(v[i]);
        }

        v_data.swap(new_data);
        v_size += v.size();
    }

    template <typename T>
    template <typename U>
    void Vector<T>::insert(size_t index, const Vector<U> &v)
    {
        if (typeid(T) != typeid(U))
        {
            std::cout << "Warning: Type mismatch. Converting " << (type_map.find(typeid(U).name()) != type_map.end() ? type_map[typeid(U).name()] : typeid(U).name()) << " to " << (type_map.find(typeid(T).name()) != type_map.end() ? type_map[typeid(T).name()] : typeid(T).name()) << std::endl;
        }
        if (index > v_size)
        {
            throw std::runtime_error("Index out of bounds.");
        }

        std::unique_ptr<T[]> new_data(new T[v_size + v.size()]);
        for (size_t i = 0; i < index; i++)
        {
            new_data[i] = v_data[i];
        }
        for (size_t i = 0; i < v.size(); i++)
        {
            new_data[index + i] = static_cast<T>(v[i]);
        }
        for (size_t i = index; i < v_size; i++)
        {
            new_data[i + v.size()] = v_data[i];
        }

        v_data.swap(new_data);
        v_size += v.size();
    }

}
