#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H
//Paweł Janduła
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T, size_t N>
class Vector;

template <typename T>
class Vector<T, 0> {
private:
    T* data;
    size_t sz;

public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    explicit Vector(size_type size = 0) : sz(size) {//lista inicjalizacyjna
        if (sz > 0) {
            data = new T[sz]{};
        } else {
            data = nullptr;
        }
    }

    Vector(std::initializer_list<T> list) : sz(list.size()) {
        if (sz > 0) {
            data = new T[sz];
            size_type i = 0;
            for (auto elem : list) {
                data[i++] = elem;
            }
        } else {
            data = nullptr;
        }
    }

    Vector(const Vector& other) : sz(other.sz) {
        if (sz > 0) {
            data = new T[sz];
            for (size_type i = 0; i < sz; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }
    //konwersja z dynamicznego na statyczny
    template <size_t N_other>
    operator Vector<T, N_other>() const {
        if (sz != N_other) {
            throw std::runtime_error("Size mismatch during conversion to static vector");
        }
        Vector<T, N_other> result; // wektor statyczny
        for (size_t i = 0; i < N_other; ++i) {
            result[i] = data[i];
        }
        return result;
    }

    template <typename S, size_t M>
    explicit Vector(const Vector<S, M>& other) : sz(other.size()) {
        if (sz > 0) {
            data = new T[sz];
            for(size_type i = 0; i < sz; ++i) {
                data[i] = static_cast<T>(other[i]);
            }
        } else {
            data = nullptr;
        }
    }

    ~Vector() {
        delete[] data;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            sz = other.sz;
            if (sz > 0) {
                data = new T[sz];
                for (size_type i = 0; i < sz; ++i) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    size_type size() const {
        return sz;
    }

    void resize(size_type new_size) {
        if (new_size == sz) return;

        T* new_data = nullptr;
        if (new_size > 0) {
            new_data = new T[new_size]{};

            size_type copy_count = sz;
            if (new_size < sz) {
                copy_count = new_size;
            }

            for (size_type i = 0; i < copy_count; ++i) {
                new_data[i] = data[i];
            }
        }

        delete[] data;
        data = new_data;
        sz = new_size;
    }

    T& operator[](size_type index) {
        return data[index];
    }

    T operator[](size_type index) const {
        return data[index];
    }

    friend Vector operator+(const Vector& u, const Vector& v) { //dynamic + dynamic
        if (u.sz != v.sz) {
            throw std::runtime_error("incompatible sizes in Vector::operator+");
        }
        Vector result(u.sz);
        for (size_type i = 0; i < u.sz; ++i) {
            result.data[i] = u.data[i] + v.data[i];
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector& v) {
        for (size_type i = 0; i < v.sz; ++i) {
            out << v.data[i];
            if (i < v.sz - 1) out << " ";
        }
        return out;
    }
};

#endif