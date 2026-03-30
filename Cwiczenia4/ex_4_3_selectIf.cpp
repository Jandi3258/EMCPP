//Pawel Jandula Zadanie 3
#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

bool biggerThan5(int x){ return x>5; }

template <
	template <typename, typename> class OutContainer, // Kontener wyjściowy
	template <typename, typename> class InContainer,  // Kontener wejściowy
	typename T,                                       // Typ elementów
	typename Alloc,                                   // Typ alokatora
	typename Predicate                                // Typ predykatu
>
OutContainer<T, Alloc> selectIf(const InContainer<T, Alloc>& c, Predicate p) {
	OutContainer<T, Alloc> result;
	for (const auto& elem : c) {
		if (p(elem)) {
			result.push_back(elem);
		}
	}

	return result;
}

int main(){
	auto print = [](auto v) { 
		for(auto x: v) cout << x << " ";
		cout << endl;
	};
	
	std::vector<int> v={1, 2, 13, 4, 5, 54};
  std::list<int> result = selectIf<std::list>(v, biggerThan5);
  print(result);  //  13 54
  
  auto result2 = selectIf<std::deque>(v, [](int x)->bool{ return x%2; } );
  print(result2); //  1 13 5
  
	auto result3 = selectIf<std::vector>(result2, biggerThan5);
	print(result3); //  13
	return 0;
}
