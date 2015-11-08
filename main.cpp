#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "StringUtils.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::string text;
    std::cin >> text;
    std::cout << StringUtils::findLongestPalindrome(text);
    return 0;
}
