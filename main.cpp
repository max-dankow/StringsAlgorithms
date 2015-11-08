#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "StringUtils.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
//    std::ifstream input("input.txt");
    std::string text;
    std::cin >> text;
//    input >> text;
    std::cout << StringUtils::findLongestPalindrome(text);
//    input.close();
    return 0;
}
