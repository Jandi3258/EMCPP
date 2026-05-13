#include <iostream>
#include <fstream>
#include <vector>
#include<map>
using namespace std;
/**
 * Trie structure
 *
 * HINT: use std::map to implement it!
 *       My implementation adds less than 25 lines of code. 
 */
class Trie{
  	struct Node{
		std::map<std::string, Node*> children;
  	    //klucz - slowo wartosci - wskazniki do kolejnego wezla
	};
	Node* root;
//drzewo slow

    // funkcja rekurencyjna, która odwiedza wszystkie możliwe odgałęzienia od danego miejsca

	void printAllPaths(Node* node, string aktualna){
		if(node->children.empty()){
			cout << " > " << aktualna << endl;
            return;
		}
		for (auto const& [word, child] : node->children) {
	string nextPath;

	if (aktualna.empty()) {
    	nextPath = word;
	}
	else {
    	nextPath = aktualna + " " + word;
	}
            printAllPaths(child, nextPath);
        }
	}
public:
	Trie() {
        root = new Node();
    }
    static void printSentence(const std::vector<std::string>  & sentence ){
        for(const auto & w : sentence)
            cout << w << " ";
    }
    //bierze wektor slow przechodzi przez drzewo i jesli
    void add(const std::vector<std::string>  & sentence ){
       cout << "Adding : ";
       printSentence(sentence);
       cout << "\n";
       Node* current = root;
        for (const string& word : sentence) {
            if (current->children.find(word) == current->children.end()) {
                current->children[word] = new Node();
            }
            current = current->children[word];
        }
    }


    //funkcja, która działa jak autouzupełnianie w wyszukiwarce
    void printPossibleEndings(const std::vector<std::string>  & beginningOfSentence ){
        cout << "Endings for \"";
        printSentence(beginningOfSentence);
        cout << "\" are :\n";
        Node* current = root;
        for (const string& word : beginningOfSentence) {
            if (current->children.find(word) != current->children.end()) {
                current = current->children[word];
            } else {
                return;
            }
        }

        for (auto const& [word, child] : current->children) {
            printAllPaths(child, word);
        }
        cout << endl;
    }
    void load(const std::string & fileName){
        ifstream file(fileName);
        if(!file){
            cerr << "Error when openning file " << fileName << endl;
            return;
        }
        string word;
        vector<string> sentence;
        while( file >> word) {
            sentence.push_back(word);
            // is it end of the sentence?
            if(word.find_last_of('.') != string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }
};


int main(){
    Trie dictionary;
    dictionary.load("sample.txt");
    //dictionary.load("hamletEN.txt");

    dictionary.printPossibleEndings({"Curiosity"});
    dictionary.printPossibleEndings({"Curiosity", "killed"});
    dictionary.printPossibleEndings({"The", "mouse","was","killed"});

    /* cout << "Beginning of sentence (ended with single .): ";
    string word;
    vector<string> sentence;
    while(true){
        cin >> word;
        if(word == ".")
            break;
        sentence.push_back(word);
        dictionary.printPossibleEndings(sentence);
    }*/
    return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */

////g++ -std=c++17 ex_9_3_Trie.cpp -o program
