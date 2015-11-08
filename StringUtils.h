#ifndef STRINGSEARCHING_STRINGUTILS_H
#define STRINGSEARCHING_STRINGUTILS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class StringUtils {
public:
    static std::string findLongestPalindrome(const std::string &text);

    static void algorithmKnuthMorrisPratt(const std::string &text,
                                   const std::string &pattern,
                                   std::vector<int> &entry);

    static void calculatePrefixFunction(const std::string &s, std::vector<int> &prefixFunction);

    static void algorithmKnuthMorrisPrattStreamInput(const std::string &pattern,
                                              std::istream &input,
                                              std::vector<int> &entry);

    static void calculateZFunction(const std::string &s, std::vector<int> &zFunction);

    static void zFunctionSearchString(const std::string &pattern, const std::string &text, std::vector<int> &entry);

private:

    static void algorithmManacherOdd(const std::string &text, std::vector<int> &palindromeByCenter);

    static void algorithmManacherEven(const std::string &text, std::vector<int> &palindrome);

//void algorithmManacher(const std::string &text, std::vector<int> &palindromeByCenter, int d)
//{
//    palindromeByCenter.resize(text.length());
//    palindromeByCenter[0] = 1;
//    int left = 0, right = -1;
//    for (int i = 0/*1*/; i < text.length(); ++i)
//    {
//        if (i > right)
//        {
//            int extend;
//            for (extend = 1;
//                 (i - extend >= 0)
//                    && (i + extend - d < text.length())
//                    && (text[i + extend - d] == text[i - extend]);
//                 ++extend);
//            palindromeByCenter[i] = extend - 1;//extend;
//            left = i - extend + 1;
//            right = i + extend - 1;
//        }
//        else
//        {
//            int mirror = left + (right - i + d);
//            if (palindromeByCenter[mirror] + i - d <= right)
//            {
//                palindromeByCenter[i] = palindromeByCenter[mirror];
//            }
//            else
//            {
//                int extend;
//                for (extend = 1;
//                     (i - (right - i) - extend >= 0)
//                        && (right + extend - d < text.length())
//                        && (text[right + extend - d] == text[i - (right - i) - extend]);
//                     ++extend);
//                palindromeByCenter[i] = right - i + extend;
//                left = i - palindromeByCenter[i] /*+ 1*/;
//                right = i + palindromeByCenter[i] - 1;
//            }
//        }
//    }
//}
};


#endif //STRINGSEARCHING_STRINGUTILS_H
