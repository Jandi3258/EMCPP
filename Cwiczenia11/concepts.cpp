//Pawel Jandula
#include <iostream>
#include <vector>
#include <concepts>
using namespace std;

// Koncept sprawdzający, czy z typem zadziała operator <<
template <typename T>
concept HasOstream = requires(std::ostream& os, const T& obj) {
    { os << obj } -> std::same_as<std::ostream&>;
};

// Koncept sprawdzający, czy typ ma metodę print()
template <typename T>
concept HasPrintMethod = requires(const T& obj) {
    obj.print();
};

// Koncept Kontenera z wytycznych z zadania
template <typename T>
concept Container = requires(T t) {
    typename T::value_type;          // Ma typ zagnieżdżony value_type
    { t.begin() };                   // Można go iterować przez range-based for
    { t.end() };
    { *t.begin() + *t.begin() };     // Jego elementy można dodać operatorem +
};

// Deklaracja wyprzedzająca dla rekurencji
template <typename T> void print(const T& obj);

template <Container C>
void print(const C& container) {
    int i = 0;
    for (const auto& elem : container) {
        std::cout << i++ << " : ";
        print(elem);
    }
    std::cout << "-------\n";
}

//Typ nie jest kontenerem, ale ma przeciążony operator<<
// C++ zawsze wybierze to przeciążenie zamiast trzeciego, jeśli typ ma obie opcje
template <typename T>
requires (!Container<T> && HasOstream<T>)
void print(const T& obj) {
    std::cout << obj << '\n';
}

// Typ nie jest kontenerem, nie ma operator<<, ale ma metodę print()
template <typename T>
requires (!Container<T> && !HasOstream<T> && HasPrintMethod<T>)
void print(const T& obj) {
    obj.print();
    std::cout << '\n';
}



template <Container C>
auto sum(const C& c) {
    // Inicjujemy sumę używając domyślnego konstruktora
    typename C::value_type total{};

    for (const auto& elem : c) {
        total = total + elem;
    }
    return total;
}




template <typename  T>
class A{
protected:
    T x;
public:
    A(T x = T()) : x(x) {}
    void print() const{
      cout << "[" << x << "]";
    }
    friend A operator+(const A & a, const A & b){
      return a.x + b.x;
    }

};

template <typename T>
class B: public A<T>{
public:
    using A<T>::A;
    B(const A<T> & a): A<T>(a) {}
    friend std::ostream & operator<<(std::ostream & out, const B & b){
      return (out << "#" << b.x << "#");
    }
};



using namespace std;
int main() {
  vector v{1,2,4,5};
  print(v);
  A<int> a{5};
  print(a);
  B<double> b{3.14};
  print(b);
  print(2.7);
  vector<A<int>> va{ 4, 5, 7, 9};
  vector<B<int>> vb{ 4, 5, 7, 9};
  print(va);
  print(vb);
  print( sum(v) );
  print( sum(vb) );
  return 0;
}
/**
* Expected output
0 : 1
1 : 2
2 : 4
3 : 5
-------
[5]
#3.14#
2.7
0 : [4]
1 : [5]
2 : [7]
3 : [9]
-------
0 : #4#
1 : #5#
2 : #7#
3 : #9#
-------
12
#25#
*/
//g++ -std=c++20 concepts.cpp -o program