//Pawel Jandula Zadanie 1
#include <iostream>
#include <cmath>

using namespace std;

/// Computes n-th root of x
double sqrtn(int n, double x) {
	return exp(log(x) / n);
}

double power(double x, double y) {
	return exp(log(x) * y);
}

template <typename F, typename G>
double function_impl(int n, double y, double z, F f, G g) {
	return (f(n, y) > z) ? g(z, y) : g(y, z);
}

typedef double (*SqrtFunc)(int, double);
typedef double (*PowerFunc)(double, double);
typedef double (*ComplexFunc)(int, double, double, SqrtFunc, PowerFunc);

int main() {
	SqrtFunc fp1 = sqrtn;
	PowerFunc fp2 = power;


	ComplexFunc fp3 = &function_impl<SqrtFunc, PowerFunc>;

	cout << fp3(2, 10, 3, fp1, fp2) << endl; // Wynik: 59049
	cout << fp3(3, 10, 3, fp1, fp2) << endl; // Wynik: 1000

	return 0;
}