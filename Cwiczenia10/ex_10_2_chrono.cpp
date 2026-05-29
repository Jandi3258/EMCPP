#include <iostream>
#include <chrono>
#include <string>

class Timer{
    std::string name;
    std::chrono::time_point<std::chrono::steady_clock> start_time;

public:
    Timer(const std::string& name)
        : name(name), start_time(std::chrono::steady_clock::now()) {
            //Zapisuje nazwę testu oraz aktualny punkt w czasie
    }

    ~Timer() {
        auto end_time = std::chrono::steady_clock::now();

        std::chrono::duration<double, std::milli> elapsed_ms = end_time - start_time;

        std::cout << name << " : " << elapsed_ms.count() << " ms. " << std::endl;
    }

    long long durationInNanoseconds() {
        auto current_time = std::chrono::steady_clock::now();

        auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - start_time);

        return elapsed_ns.count();
    }//Umożliwia sprawdzenie, ile czasu minęło od momentu utworzenia obiektu do chwili obecnej
};

long fibonacci(unsigned n){
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    Timer total("Total time");
    for(auto n : {1, 5, 15, 20, 25, 40, 45}){
        {
            Timer t("fibonacci(" + std::to_string(n) + ")");  // RAII
            fibonacci(n);

        }
    //2
    //3
    }
    std::cout << "Elapsed " << total.durationInNanoseconds() << " ns.\n";
}
/** Expected output similar to:

fibonacci(1) : 0.000619 ms.
fibonacci(5) : 0.000891 ms.
fibonacci(15) : 0.01025 ms.
fibonacci(20) : 0.094905 ms.
fibonacci(25) : 1.04443 ms.
fibonacci(40) : 989.97 ms.
fibonacci(45) : 8537.47 ms.
Elapsed 9528821533 ns.
Total time : 9528.84 ms.
*/