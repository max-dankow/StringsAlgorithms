#include <iostream>
#include "SuffixTreeUtils/UkkonenAlgorithm.h"

int main()
{
//    std::ios_base::sync_with_stdio(false);
//    std::string text;
//    std::cin >> text;
//    std::cout << StringUtils::findLongestPalindrome(text);
    UkkonenAlgorithm algorithm;
    algorithm.buildSuffixTree("abababa");
    return 0;
}
