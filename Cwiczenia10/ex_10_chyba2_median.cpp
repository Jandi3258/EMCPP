#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

namespace details {
    template <typename Container>
    double median_impl(Container set, std::random_access_iterator_tag) {
        if (set.empty()) return 0.0;

        size_t n = set.size();
        size_t mid = n / 2;
        std::nth_element(set.begin(), set.begin() + mid, set.end());
        //znalezienie elementu, który znalazłby się na konkretnej pozycji po pełnym posortowaniu i na set[mid] jest wartosc ktora powinna tam byc

        if (n % 2 != 0) {
            return static_cast<double>(set[mid]);
        }
        else {
            auto mid_element = set[mid];
            std::nth_element(set.begin(), set.begin() + mid - 1, set.end());
            auto mid_minus_one_element = set[mid - 1];

            return (static_cast<double>(mid_element) + static_cast<double>(mid_minus_one_element)) / 2.0;
        }
    }

    template <typename Container>
    double median_impl(Container& set, std::forward_iterator_tag) {
        size_t n = std::distance(set.begin(), set.end());
        if (n == 0) return 0.0;
        set.sort();

        size_t mid = n / 2;
        auto it = set.begin();
        std::advance(it, mid); // Przesuwa iterator o mid pozycji do przodu

        if (n % 2 != 0) {
            return static_cast<double>(*it);
        } 
        else {
            // Dla liczby parzystej potrzebujemy również elementu o jeden wcześniejszego
            auto it2 = set.begin();
            std::advance(it2, mid - 1);
            return (static_cast<double>(*it) + static_cast<double>(*it2)) / 2.0;
        }
    }
}

// Główny interfejs szablonu - przyjmuje przez referencję, aby nie wymuszać kopii na starcie
template <typename Container>
double median(Container& set) {
    // Wyciągnięcie kategorii iteratora w czasie kompilacji
    using it_category = typename std::iterator_traits<typename Container::iterator>::iterator_category;

    // Tag Dispatching - przekierowanie do odpowiedniej przeciążonej wersji
    return details::median_impl(set, it_category{});
}

int main() {
    std::list<int> a{3, 2, 5, 1, 4};
    cout << "median(list {3,2,5,1,4}): " << median(a) << endl; //3
    std::vector<int> v{3, 1, 4, 2};
    cout << "median(vector {3,1,4,2}): " << median(v) << endl; //2.5

    // Test dla std::forward_list (modyfikacja w miejscu, brak kopii)
    std::forward_list<double> fl{1.1, 4.4, 2.2, 3.3};
    cout << "median(forward_list):     " << median(fl) << endl; //2.75

    // Test dla std::deque (pracuje na wewnętrznej kopii)
    std::deque<int> dq{10, 20, 30};
    cout << "median(deque):            " << median(dq) << endl; //20

    return 0;
}