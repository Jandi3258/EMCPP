#ifndef LAB8_RANGE_H
#define LAB8_RANGE_H

#include <iterator>
#include <iostream>

template <typename T>
class Range {
private:
    T start_val;
    T stop_val;
    T step_val;

    //jak stworzyć obiekt, który zachowuje się jak kolekcja, ale nie zajmuje pamięci na przechowywanie elementów. - wirtualny kontener
public:
    explicit Range(T stop) : start_val(0), stop_val(stop), step_val(1) {}
    Range(T start, T stop, T step = 1) : start_val(start), stop_val(stop), step_val(step) {}

    class Iterator {
    private:
        T current_val;
        T step_val;
        T stop_limit;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T val, T step, T stop) : current_val(val), step_val(step), stop_limit(stop) {}

        T operator*() const { return current_val; }

        Iterator& operator++() {
            current_val += step_val;
            return *this;
        }

        Iterator operator++(int) { // do dodawania nastepnego kroku
            Iterator tmp = *this;
            current_val += step_val;
            return tmp;
        }
        bool operator!=(const Iterator& other) const {//do sprawdzania limitu
            if (step_val > 0) {
                return (current_val < stop_limit) != (other.current_val < other.stop_limit);
            }
            else {
                return (current_val > stop_limit) != (other.current_val > other.stop_limit);
            }
        }

        bool operator==(const Iterator& other) const {
            return !(*this != other);
        }
    };

    Iterator begin() const { return Iterator(start_val, step_val, stop_val); }//iterator ustawiony na wartosc pocz
    Iterator end() const { return Iterator(stop_val, step_val, stop_val); }//iterator ustawiony na wartosc kon
};

template <typename T>
auto begin(const Range<T>& r) { return r.begin(); }

template <typename T>
auto end(const Range<T>& r) { return r.end(); }

template <typename T>
Range<T> make_range(T stop) {
    return Range<T>(stop);
}

template <typename T>
Range<T> make_range(T start, T stop, T step = 1) {
    return Range<T>(start, stop, step);
}

#endif //LAB8_RANGE_H