#include <iostream>
#include "Vector.h"
using  namespace std;
int main() {
    int value = 5;
    {
        using Vect = Vector<double, 3, SafePolicy>;
        Vect a{};
        a.set(1, -1);
        cout << a << endl;              // 0 -1 0

        try { a.set(-1, 1.); }
        catch (const std::exception& e) { cout << "Exception: " << e.what() << "\n"; }

        try { cout << a.get(3) << endl; }
        catch (const std::exception& e) { cout << "Exception: " << e.what() << "\n"; }

        try { Vect b{1, 2, 3, 4}; }
        catch (const std::exception& e) { cout << "Exception: " << e.what() << "\n"; }
    }
    {
        using Vect = Vector<double, 3, FastPolicy>;//
        Vect a{};
        a.set(1, -1);
        cout << a << endl;             // unspecified garbage for [0] and [2]
        a.set(-1, 1.);                 // writes to random memory
        cout << value << endl;         // possibly corrupted
        cout << a.get(3) << endl;      // unspecified
        Vect b{1, 2, 3, 4};           // OK, copies only first 3
    }
    {
        using Vect = Vector<double, 3, InitFastPolicy>;
        Vect a{};
        a.set(1, -1);
        cout << a << endl;             // 0 -1 0
        a.set(-1, 1.);                 // unspecified
        cout << value << endl;         // possibly corrupted
        cout << a.get(3) << endl;      // unspecified
        Vect b{1, 2, 3, 4};           // OK, copies only first 3
    }
    return 0;
}