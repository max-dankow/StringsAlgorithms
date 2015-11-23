#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "SuffixTreeUtils/UkkonenAlgorithm.h"
#include "SuffixArray/SuffixArrayUtils.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    long keyLength;
    std::string text;
    std::cin >> keyLength;
    std::cin >> text;
    std::string doubledText = text + text;
    SuffixArrayUtils utils;
    for (size_t i = 0; i < text.length(); ++i) {
        std::string current(doubledText.begin() + i, doubledText.begin() + i + keyLength);
        std::cout << utils.countSubstrings(current) << " ";
    }
//    std::cout << '\n';
    return 0;
}
