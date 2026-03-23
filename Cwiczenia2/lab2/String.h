//Pawel Jandula Zadanie 4
#include <iostream>
#include <algorithm>
#include <memory>
#include "MyString.h"

using namespace std;

class String {
    using MyStr = emcpp::MyString;
    std::shared_ptr<MyStr> data;

public:
    String() : data(std::make_shared<MyStr>()) {}//wiele wskaznikow moze wskazywac na ten sam obiekt
    String(const char * str) : data(std::make_shared<MyStr>(str)) {}//konstruktor nowego obiektu

    // Płytka kopia
    String(const String & s) : data(s.data) {}//szybsza duzo

    String& operator=(const String & s) {
        if (this != &s) {
            data = s.data;
        }
        return *this;
    }

    void set(int index, char ch) {
        if (data.use_count() > 1) {//wiecej niz 1 taki sam string

            data = std::make_shared<MyStr>(*data);//robimy deep copy bo jeden tylko modyfikujemy i musimy dac mu nowa pamiec
        }
        (*data)[index] = ch;
    }

    char get(int index) const {
        return (*data)[index];
    }

    friend String operator+(const String& a, const String& b) {
        if (a.data->empty()) return b;//by 2 razy konstruktor sie nie wywolywal
        if (b.data->empty()) return a;
        String res((*a.data + *b.data).data());
        return res;
    }

    friend std::ostream & operator<<(std::ostream & out, const String& s) {
        if (s.data) out << *s.data;
        return out;
    }
};