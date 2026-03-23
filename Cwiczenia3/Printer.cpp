//Paweł Janduła Zadanie 3

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
class Printer{
	ostream &wyjscie;
	string prefix;
	string postfix;
public:
	Printer(std::ostream& stream, string pre, string post)
		: wyjscie(stream), prefix(pre), postfix(post){}

	template <typename T>
	void operator()(const T& dzialanie){
		wyjscie << prefix << dzialanie << postfix;
	}

};

int main(){//functor - obiekt ktory mozemy wywolac, udajacy funkcje
	//obiekt ktory ma przeladowane nawiasy
  /// Creates unary functor that takes one argument x (of any type)
  /// and outputs to given stream x surrounded by given prefix na postfix
  /// e.g. in the following  [ x ]
  /// Hint: define function template.
  Printer printer(std::cout,  "[ ", " ] " );
  printer("hello");    // [ hello ]
  std::cout << "\nv = ";
  std::vector<int> v = {1, 2, 3, 4};
  std::for_each(v.begin(), v.end(), printer);  // v = [ 1 ] [ 2 ] [ 3 ] [ 4 ]
	std::cout << std::endl;
  std::ofstream file("myFile.txt");
  Printer filePrinter(file, "- ", "\n");
  filePrinter(5);
  filePrinter("My text");	
	return 0;
}
/** myFile.txt
- 5
- My text
*/
