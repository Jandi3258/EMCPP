#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <utility>

template <typename T, typename... Ts>
struct IndexOf;

template <typename T, typename... Rest>
struct IndexOf<T, T, Rest...> {
    static constexpr std::size_t value = 0;
};

template <typename T, typename Head, typename... Rest>
struct IndexOf<T, Head, Rest...> {
    static constexpr std::size_t value = 1 + IndexOf<T, Rest...>::value;
};


//rekurencyjny szablon (metaprogramowanie). W czasie kompilacji
//przeszukuje listę typów (Ts...). Jeśli znajdzie typ T, zwraca 0.
//Jeśli nie, dodaje 1 do wyniku wyszukiwania w pozostałej części listy (Rest...).

template<typename... Ts>
class MultiVector {
    std::tuple<std::vector<Ts>...> storage;

public:
    template<typename T>
    void push_back(const T& value) {
        constexpr std::size_t idx = IndexOf<T, Ts...>::value;
        std::get<idx>(storage).push_back(value);
    }
    //zamienia typ na konkretny numer indeksu (np. 0, 1, 2...).
    //Dzięki temu std::get<idx>(storage) jest zawsze jednoznaczne,
    //nawet jeśli typy się powtarzają.

    void print() const {
        std::apply([](const auto&... vecs) {//Rozpakowuje krotkę storage na poszczególne argumenty (wektory) i przekazuje je do lambdy.
            auto print_one = [](const auto& vec) {
                std::cout << "[ ";
                for (const auto& item : vec) std::cout << item << " ";
                std::cout << "] ";
            };

            (print_one(vecs), ...); //vecs - paczka parametrów zawierająca wszystkie wektory z krotki.
            // to print_one to fold expression
            std::cout << std::endl;
        }, storage);
    }
};

int main(){
    MultiVector<int, std::string, double> m;
    m.push_back(5);
    m.push_back(std::string("text"));
    m.push_back(7);
    m.push_back(1.2);
    m.print();   // [ 5 7 ] [ text ] [ 1.2 ]

    auto v = std::move(m);
    for(auto x: { 1, 2, 3}){
        v.push_back(x+10);
        v.push_back(std::to_string(x));
        v.push_back(x/10.0);
    }

    std::cout << "M po przeniesieniu:" << std::endl;
    m.print(); // [ ] [ ] [ ]
    std::cout << "V po push_back:" << std::endl;
    v.print(); // [ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]

    MultiVector<int, int, double, int> w;
    w.push_back(1);
    w.push_back(2.0);
    w.print(); // [ 1 ] [ ] [ 2 ] [ ]
}