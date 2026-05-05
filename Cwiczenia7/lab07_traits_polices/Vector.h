#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <string>

// Zad 2 - co jest obiektem
template <typename T>//wzorzec Traits
struct vector_traits {//specjalizacja szablonu traits
    using param_type = const T&; //T jako argument optymalny typ argumentu (nie domyslny)
    using scalar_type = T; // T przy dzialaniach matematycznych, pozwala np na vector * int

    static T zero() { return T(); }
    static T mult(const T& val, const T& scalar) { return val * scalar; }
};

template <> struct vector_traits<int> {
    using param_type = int;
    using scalar_type = int;
    static int zero() { return 0; }
    static int mult(int val, int scalar) { return val * scalar; }
};
template <> struct vector_traits<double> {
    using param_type = double; // Wartość
    using scalar_type = double;
    static double zero() { return 0.0; }
    static double mult(double val, double scalar) { return val * scalar; }
};

template <> struct vector_traits<std::string> {
    using param_type = const std::string&;
    using scalar_type = int;
    static std::string zero() { return "0"; }
    static std::string mult(const std::string& val, int scalar) {
       std::string res = "";
       for(int i=0; i<scalar; ++i) res += val;
       return res;
    }
};

// Zad 3 - jak sie zachowuje obiekt
//Pozwala on na wstrzykiwanie zachowania do klasy Vector za pomocą argumentów szablonu
//wzorzec policy based
struct SafePolicy { // sprawdza wywalanie z tablicy
    static void check(size_t index, size_t N) {
       if (index >= N) throw std::out_of_range("Index out of bounds");
    }
    static bool should_init() { return true; }
};

struct FastPolicy {// nie robi sprawdzań, więc jest szybsza
    static void check(size_t index, size_t N) {}
    static bool should_init() { return false; }
};

struct InitFastPolicy { // inicjalizuje pamiec zerami
    static void check(size_t index, size_t N) {}
    static bool should_init() { return true; }
};

template <typename T, size_t N, typename Policy = SafePolicy> // domyslnie wstawia safe policy
class Vector {
  T data[N];
 public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T& reference;
  typedef const T& const_reference;

  Vector() {
      if (Policy::should_init()) {//tu sprawdzamy polityke
          for(size_t i = 0; i < N; ++i) {
              data[i] = vector_traits<T>::zero();//inicjalizujemy zerami
          }
      }
  }

  Vector(const Vector & v) = default;
  Vector &operator=(const Vector & m) = default;

  Vector(const std::initializer_list<T> &list) {
    std::copy(list.begin(), list.begin() + std::min(list.size(), (size_t)N), data);
  }

  size_type size() const { return N; }

  const_reference get(size_type index) const {
    Policy::check(index, N);
    return data[index];
  }

  void set(size_type index, typename vector_traits<T>::param_type value) {
    Policy::check(index, N);
    data[index] = value;
  }

  friend Vector operator* (typename vector_traits<T>::scalar_type s, const Vector & v) {
    Vector result;
    for(size_t i=0; i < N; ++i){
       result.set(i, vector_traits<T>::mult(v.get(i), s));
    }
    return result;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
    for(size_t i=0; i < N; ++i){
      out << v.get(i) << (i == N - 1 ? "" : " ");
    }
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Vector & v) {
    typename vector_traits<T>::scalar_type value;
    for(size_t i=0; i < N; ++i){
      in >> value;
      if(in) v.set(i, value);
    }
    return in;
  }
};

#endif // LAB8_VECTOR_H