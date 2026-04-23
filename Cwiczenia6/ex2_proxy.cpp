#include <iostream>
#include <typeinfo>
#include <utility>
#include <string>
#include <cstdlib>
#include <cxxabi.h>//musimy zastapic proxy dlatego ja tu uzywam tej biblioteki

using namespace std;

string demangle(const char* name) {
    int status = 0;
    char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);//czytelne nazwy typow
    string result = (status == 0) ? demangled : name; // 0 jesli operacja sie powiodla
    free(demangled);
    return result;
}//odkodowywanie nazw typow

template<typename... Args>
void showNames(Args&&... args) {
    int i = 1;
    ((std::cout << i++ << " > "
                << demangle(typeid(Args).name())
                << " [" << typeid(args).name() << "] = "
                << args << std::endl), ...);
}

template<typename F>
class Proxy {
    F func;
public:
    Proxy(F f) : func(std::forward<F>(f)) {}

    template<typename... Args>
    auto operator()(Args&&... args) {
        std::cout << "Proxy" << std::endl;
        showNames(std::forward<Args>(args)...);
        return func(std::forward<Args>(args)...);
    }
};

template<typename F>
auto make_proxy(F&& f) {
    return Proxy<std::decay_t<F>>(std::forward<F>(f)); //czysci typ f z syfu (referencje, modyfikatory)
}//rozpoznaje typ funktora i zwraca proxy    //perfect forwarding - lvalue i rvalue normalnie przekazany
//zamienia tablice na wskazniki

double f(int x, double y, const int & z, int & w){
    w += 2;
    cout << x << " " << y << " " << z << " " << w << endl;
    return (x*y - z*w);
}

int main(){
    int x = 4;
    const int y = 8;

    showNames(x, 4.5, y, f);
    showNames(1, 1.0f, 1.0, 1LL, &x, &y);

    auto p = make_proxy(f);
    auto result1 = p(12, 5.1, y, x);
    cout << "result1 = " << result1 << endl;
    auto result2 = p(12, 5.1, y, x);
    cout << "result2 = " << result2 << endl;
    auto result3 = p(3, 3, 5, x);
    cout << "result3 = " << result3 << endl;

    auto g = make_proxy([](int &&x, int & y){ y = x; return y; }) ;
    cout << g(5, x) << endl;
    cout << "x = " <<  x << endl;
    return 0;
}