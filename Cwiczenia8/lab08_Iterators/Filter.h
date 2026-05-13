#ifndef LAB8_FILTER_H
#define LAB8_FILTER_H

#include <iterator>
#include <utility>
#include <type_traits>

template <typename Container, typename Predicate>
class Filter {

    Container container;
    Predicate predicate;

public:
    Filter(Container&& c, Predicate p) 
        : container(std::forward<Container>(c)), predicate(p) {}

    class iterator {
        using BaseIterator = decltype(std::begin(std::declval<typename std::remove_reference<Container>::type&>()));
        //aby iterator filtra wiedział, jakiego typu jest iterator oryginalnego kontenera
        BaseIterator current;
        BaseIterator end_it;
        Predicate* pred;

        void skip_to_next() {
            while (current != end_it && !(*pred)(*current)) {
                ++current;
            }
        }//Za każdym razem, gdy iterator się przesuwa, sprawdza on bieżący element za pomocą predykatu (*pred).
        //Jeśli predykat zwraca false, iterator automatycznie przeskakuje do następnego elementu


    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = typename std::iterator_traits<BaseIterator>::value_type;
        using difference_type   = typename std::iterator_traits<BaseIterator>::difference_type;
        using pointer           = typename std::iterator_traits<BaseIterator>::pointer;
        using reference         = typename std::iterator_traits<BaseIterator>::reference;

        iterator(BaseIterator it, BaseIterator end, Predicate& p) 
            : current(it), end_it(end), pred(&p) {
            skip_to_next();
        }

        reference operator*() const { return *current; }
        pointer operator->() const { return &(*current); }

        iterator& operator++() {
            if (current != end_it) {
                ++current;
                skip_to_next();
            }
            return *this;
        }

        bool operator==(const iterator& other) const { return current == other.current; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    auto begin() { 
        return iterator(std::begin(container), std::end(container), predicate); 
    }
    
    auto end() { 
        return iterator(std::end(container), std::end(container), predicate); 
    }
};

template <typename Container, typename Predicate>
auto make_filter(Container&& c, Predicate p) {
    return Filter<Container, Predicate>(std::forward<Container>(c), p);
}

#endif //LAB8_FILTER_H