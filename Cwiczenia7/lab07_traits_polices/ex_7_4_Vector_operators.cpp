#include <iostream>
#include <initializer_list>
#include <algorithm>

using namespace std;

template <typename T>
struct Traits {//dla struktur type VecAdd
    using Type = T; // przechowujemy przez wartosc
};

template <int N> class Vector;

template <int N>
struct Traits<Vector<N>> {// dla prawdziwych danych
    using Type = const Vector<N>&; //surowy wektor przechowujemy przez referencje
};


//węzły drzewa obliczeń. Nie zawierają one wyników, a jedynie jak wynik uzyskać.
template <typename L, typename R>
struct VecAdd {
    typename Traits<L>::Type lhs;
    typename Traits<R>::Type rhs;
    VecAdd(const L& l, const R& r) : lhs(l), rhs(r) {}
    int operator[](int i) const { return lhs[i] + rhs[i]; }
};

template <typename L, typename R>
struct VecSub {
    typename Traits<L>::Type lhs;
    typename Traits<R>::Type rhs;
    VecSub(const L& l, const R& r) : lhs(l), rhs(r) {}
    int operator[](int i) const { return lhs[i] - rhs[i]; }
};

template <typename R>
struct VecScalarMul {
    int scalar;
    typename Traits<R>::Type rhs;
    VecScalarMul(int s, const R& r) : scalar(s), rhs(r) {}
    int operator[](int i) const { return scalar * rhs[i]; }
};


template <int N>
class Vector {//kontener przechowujacy dane
    int data[N];
public:
    Vector() {
        cout << " Default constr" << endl;
        for (int i = 0; i < N; ++i) data[i] = 0;
    }

    Vector(std::initializer_list<int> list) {
        cout << " Init list constr" << endl;
        auto it = list.begin();
        for (int i = 0; i < N && it != list.end(); i++) {
            data[i] = *it++;
        }
    }

    Vector(const Vector& m) {
        cout << " Copy constr" << endl;
        std::copy(m.data, m.data + N, data);
    }

    template <typename Expr>
    Vector(const Expr& expr) : Vector() {
        for (int i = 0; i < N; ++i) {
            data[i] = expr[i];
        }
    }

    template <typename Expr>
    Vector& operator=(const Expr& expr) {
        for (int i = 0; i < N; ++i) {
            data[i] = expr[i];
        }
        return *this;
    }

	//operatory nie dodają liczb. One jedynie zwracają obiekt VecAdd, który "pamięta", że ma dodać lhs do rhs w przyszłości.
    int operator[](int index) const { return data[index]; }
    int& operator[](int index) { return data[index]; }

    friend ostream& operator<<(ostream& out, const Vector& m) {
        for (int i = 0; i < N; i++) {
            out << m.data[i] << (i == N - 1 ? "" : ", ");
        }
        return out;
    }
};


template <typename L, typename R>
VecAdd<L, R> operator+(const L& lhs, const R& rhs) { return VecAdd<L, R>(lhs, rhs); }

template <typename L, typename R>
VecSub<L, R> operator-(const L& lhs, const R& rhs) { return VecSub<L, R>(lhs, rhs); }

template <typename R>
VecScalarMul<R> operator*(int s, const R& rhs) { return VecScalarMul<R>(s, rhs); }//int * obiekt

template <typename L>
VecScalarMul<L> operator*(const L& lhs, int s) { return VecScalarMul<L>(s, lhs); }//obiekt * int

int main(){
  using V = Vector<10>;
  V v{1,2,3,4,5,6,7,8,9,10};
  V x(v);
  V y{4,4,2,5,3,2,3,4,2,1};

  cout << "Lazy operations :\n";
  // It does not create temporary Vectors
  // It computes resulting vector coordinate by coordinate
  // (evaluating whole expression)
  V z = v + x + 3 * y - 2 * x;//VecSub<VecAdd<VecAdd<V, V>, VecScalarMul<V>>, VecScalarMul<V>>
	//trzyma tylko kilka referencji do oryginalnych wektorow
  cout << z << endl;

  // Computes only one coordinate of Vector
  int e = (z+x+y)[2]; //z[2] + x[2] + y[2]
  cout << " e = " << e << endl;
  V w = v + x + 3 * y - 2 * x;
  cout << w[2] << endl;
  return 0;
}
/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 Default constr
6
 */