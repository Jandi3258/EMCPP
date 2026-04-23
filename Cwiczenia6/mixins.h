

#ifndef CWICZENIA6_MIXINS_H
#define CWICZENIA6_MIXINS_H

#include <iostream>
template<class ...T>
class Mixins : public T... {//klasa Mixins dziedziczy publicznie po wszystkich typach przekazanych do szablonu
    public:
    Mixins(T&&... args) : T(std::forward<T>(args))... {}//pack expansion w liście inicjalizacyjnej. Kompilator rozwija tę konstrukcję na listę wywołań konstruktorów dla każdej klasy bazowej
    Mixins(const T&... args) : T(args)... {}
};

#endif //CWICZENIA6_MIXINS_H