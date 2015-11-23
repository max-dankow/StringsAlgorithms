#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "SuffixTreeUtils/UkkonenAlgorithm.h"
#include "SuffixArray/InducedSorting.h"
#include "SuffixArray/SuffixArrayUtils.h"

int main()
{
    InducedSorting algorithm;
    std::ios_base::sync_with_stdio(false);
    std::string text;
//    std::cin >> text;
    text = "aba";
    SuffixArrayUtils utils;
    std::cout << utils.countSubstrings(text) << "\n";
//    std::cout << '\n';

//    long keyLength;
//    std::string text;
//    std::cin >> keyLength;
//    std::cin >> text;
//    std::string doubledText = text + text;
//    UkkonenAlgorithm algorithm;
//    for (size_t i = 0; i < text.length(); ++i) {
//        std::string current(doubledText.begin() + i, doubledText.begin() + i + keyLength);
//        SuffixTree tree = algorithm.buildSuffixTree(current);
//        std::cout << tree.countSubstrings() << " ";
//    }
//    std::cout << '\n';
    return 0;
}
