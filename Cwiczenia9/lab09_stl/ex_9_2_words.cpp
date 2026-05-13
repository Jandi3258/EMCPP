#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cctype>
using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string & s) {
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c) {
        return !std::isalnum(c);
    }), s.end());

    //przechodzi przez cały napis i "przesuwa" wszystkie znaki spełniające warunek na sam koniec. - remove_if
    //odcina" końcówkę napisu, zaczynając od miejsca wskazanego przez remove_if aż do samego końca (s.end()). - erase

    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}

int main(){
    int count = 0;
    string word;
    std::map<string, int> counts;

    while (cin >> word) {
        toLowerAlpha(word);
        if (!word.empty()) {
            counts[word]++;
        }
    }



    cout << "Number of distinct words : " << count << endl;


    vector<pair<string, int>> sorted_words(counts.begin(), counts.end());


    sort(sorted_words.begin(), sorted_words.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });


    cout << "\nThe top 20 most popular words: \n";


    int limit = min((int)sorted_words.size(), 20);
    for (int i = 0; i < limit; ++i) {
        cout << sorted_words[i].first << " : " << sorted_words[i].second << endl;
    }
    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4725

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248

 */
//g++ ex_9_2_words.cpp -o words
//  ./words < hamletEN.txt