#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>
#include <ctime>
#include <thread>
#include <utility>
#include <thread>
#include <chrono>
using namespace std;

template <int N>
struct Array{
    int a[N];
    int i  = 0;
    int value = 1;
	long long sum = 0;

	int f(int x){
		int y = x%11;
		return (y*y+1);
	}

	void generateArray(){
		while(i<N){
		    a[i++] = rand();
		}
		i = 0;
		while(i<N){
			a[i] = f(a[i]);
			i++;
		}
	}
	
	long long computeSum(){
	    sum = 0;
		for(int x : a){
		}
		return sum;
	}
};

int main(){
	srand(2019);
	using A = Array<1000>;
	A array;
	std::thread t1(&A::generateArray, &array);
//  What happens if you uncomment this line?
//  std::thread t2(&A::generateArray, &array);
//	t2.join();
	t1.join();
	for(int i=0; i<40; i++){
		cout << array.a[0+i] << "  ";
	}
	long long sum = array.computeSum();
	cout << "\n sum = " << sum << endl;	
}
