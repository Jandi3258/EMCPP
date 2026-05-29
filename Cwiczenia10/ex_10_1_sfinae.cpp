#include <iostream>
#include <vector>
#include <type_traits> 

using namespace std;

#define test(value, expected) cout << boolalpha << (value) << " | " << (expected) << endl;

class A {
public:
    static const int value_type = 10;
    int size = 0;
};

struct B {
    template <typename T>
    size_t size(T t) {
        return sizeof(t);
    }
};

template <typename T, typename = void>
struct has_size_impl : false_type {};

template <typename T>
struct has_size_impl<T, std::void_t<decltype(declval<T>().size())>> : true_type {};

template <typename T>
struct has_size {
    static constexpr bool value = has_size_impl<T>::value;
};

//wykrywacze metody size 
/*

Baza (false_type): Domyślnie zakładamy, że klasa T nie ma metody .size().

Specjalizacja (true_type): Kompilator próbuje dopasować tę wersję. Sercem tego jest std::void_t<...>, 
które zamienia dowolny poprawny zestaw typów w typ void.

declval<T>().size(): Udaje, że tworzy obiekt typu T i wywołuje na nim metodę .size(). 
Jeśli T nie ma takiej metody, ta linijka jest niepoprawna. Dzięki zasadzie SFINAE kompilator nie wyrzuca błędu, 
tylko po prostu odrzuca tę specjalizację i wraca do wersji bazowej (false_type).
*/

// Baza: Domyślnie brak wewnętrznego typu value_type
template <typename T, typename = void>
struct has_value_type_impl : false_type {};

// Specjalizacja: Sprawdza czy istnieje typename T::value_type
template <typename T>
struct has_value_type_impl<T, std::void_t<typename T::value_type>> : true_type {};

template <typename T>
struct has_value_type {
    static constexpr bool value = has_value_type_impl<T>::value;
};


namespace v1 {
    
    template <typename T>
    typename enable_if<has_size_impl<T>::value && has_value_type_impl<T>::value, size_t>::type
    getSize(const T& x) {
        return x.size() * sizeof(typename T::value_type);
    }

    // Dla całej reszty typów (negacja warunku)
    template <typename T>
    typename enable_if<!(has_size_impl<T>::value && has_value_type_impl<T>::value), size_t>::type
    getSize(const T& x) {
        return sizeof(x);
    }
}

namespace v2 {
    template <typename T>
    size_t getSize(const T& x) {
        if constexpr (has_size_impl<T>::value && has_value_type_impl<T>::value) {
            return x.size() * sizeof(typename T::value_type);
        } else {
            return sizeof(x);
        }
    }
}

int main() {
    test( has_size< int >::value,          false);
    test( has_size< vector<int> >::value,  true);
    test( has_size< A >::value,            false);
    test( has_size< B >::value,            false);

    test( has_value_type< int >::value,         false);
    test( has_value_type< vector<int> >::value, true);
    test( has_value_type< A >::value,           false);

    cout << "\n--- Testy funkcji getSize ---\n";

    vector<int> v{1, 2, 3, 4, 5};
    int i = 42;

    // Test wersji v1 (enable_if)
    cout << "v1::getSize(vector z 5 intami): " << v1::getSize(v) << " bajtow" << endl; // 5 * 4 = 20
    cout << "v1::getSize(int):               " << v1::getSize(i) << " bajtow" << endl; // sizeof(int) = 4

    // Test wersji v2 (if constexpr)
    cout << "v2::getSize(vector z 5 intami): " << v2::getSize(v) << " bajtow" << endl; // 20
    cout << "v2::getSize(int):               " << v2::getSize(i) << " bajtow" << endl; // 4

    return 0;
}

/*
struct CustomBool {
    bool val;
    constexpr operator bool() const { return val; }
    bool operator<<(ostream& (*)(ostream&)) const { return val; }
};
*/