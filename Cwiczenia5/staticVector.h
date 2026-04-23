#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H
//Paweł Janduła
#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <initializer_list>
#include <stdexcept>

template <typename T, size_t N>
class Vector;

template <typename T>
class Vector<T, 0>;

template <typename T, size_t N> // N to nie typ
class Vector {
    T data[N]; //stosik

public:
    typedef T value_type;
    typedef std::size_t  size_type;
    //typedef T* pointer;
    //typedef T& reference;
    //typedef const T& const_reference;

    Vector() : data{} { }

    Vector(const Vector & v) {
        for(size_type i = 0; i < N; ++i) {
            data[i] = v.data[i];
        }
    }
    //z dynamicznego na statyczny
    template <typename S, size_t M>
    explicit Vector(const Vector<S, M>& other) {
        size_type limit = N;
        if (other.size() < N) {
            limit = other.size();
        }

        for(size_type i = 0; i < limit; ++i) {
            data[i] = static_cast<T>(other[i]);
        }

        for(size_type i = limit; i < N; ++i) {
            data[i] = T{};//dopelnienie zerami
        }
    }

    Vector &operator=(const Vector & m) {
        if (this != &m) {
            for(size_type i = 0; i < N; ++i) {
                data[i] = m.data[i];
            }
        }
        return *this;
    }
    //konwersja ze statycznego na dynamiczny
    template <typename T_other>
    operator Vector<T_other, 0>() const {
        Vector<T_other, 0> result(N); // nowy wektor dynamiczny
        for (size_t i = 0; i < N; ++i) {
            result[i] = static_cast<T_other>(data[i]);//przepisujemy
        }
        return result;
    }

    Vector(const std::initializer_list<T> &list) {
        auto it = list.begin();
        for(size_type i = 0; i < N; ++i) {
            if (it != list.end()) {
                data[i] = *it;
                ++it;
            } else {
                data[i] = T{};
            }
        }
    }

    friend Vector operator+ (const Vector & u, const Vector & v ) {//static + static
        Vector result;
        for(size_type i = 0; i < N; ++i) {
            result.data[i] = u.data[i] + v.data[i];
        }
        return result;
    }

    constexpr size_type size() const {
        return N;
    }

    T get(size_type index) const {
        return data[index];
    }

    void set(size_type index, T value) {
        data[index] = value;
    }

    T& operator[](size_type index){
        return data[index];
    }

    T operator[](size_type index) const{
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for(size_type i = 0; i < N; ++i) {
            out << v.data[i];
            if (i < N - 1) out << " ";
        }
        return out;
    }
};

//zadanie 4
template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N>& stat_vec, const Vector<T, 0>& dyn_vec) { //static + dynamic
    if (N != dyn_vec.size()) {
        throw std::runtime_error("incompatible sizes in Vector::operator+");
    }
    Vector<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = stat_vec[i] + dyn_vec[i];
    }
    return result;
}

template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, 0>& dyn_vec, const Vector<T, N>& stat_vec) {//dynamic + static
    return stat_vec + dyn_vec;//odwracamy tą funkcje wyzej i tyle
}




#endif
//nie trzeba implementowac move semantics bo to jest na stacku identycznie kosztowo jak copy