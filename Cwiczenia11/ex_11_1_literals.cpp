//Pawel Jandula
#include <iostream>
using namespace std;



constexpr double operator""_m(long double val) { return val; }
constexpr double operator""_m(unsigned long long val) { return static_cast<double>(val); }

constexpr double operator""_km(long double val) { return val * 1000.0; }
constexpr double operator""_km(unsigned long long val) { return val * 1000.0; }

constexpr double operator""_cm(long double val) { return val / 100.0; }
constexpr double operator""_cm(unsigned long long val) { return val / 100.0; }


constexpr double operator""_s(long double val) { return val; }
constexpr double operator""_s(unsigned long long val) { return static_cast<double>(val); }

constexpr double operator""_ms(long double val) { return val / 1000.0; }
constexpr double operator""_ms(unsigned long long val) { return val / 1000.0; }

constexpr double operator""_h(long double val) { return val * 3600.0; }
constexpr double operator""_h(unsigned long long val) { return val * 3600.0; }


double computeVelocity(double distance, double time){

    return distance/time;
}

int main(){
    cout << computeVelocity(100_m, 5_s) << endl;     //20
    cout << computeVelocity(360_km, 2.0_h) << endl;  //50
    cout << computeVelocity(3.6_km, 0.02_h) << endl; //50
    cout << computeVelocity(250_cm, 2.5_ms) << endl; //1000
    return 0;
}
