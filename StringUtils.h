#ifndef STRINGSEARCHING_STRINGUTILS_H
#define STRINGSEARCHING_STRINGUTILS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


// Класс StringUtils реализует некоторые полезные строковые алгоритмы, такие как:
// поиск подстроки, поиск макимального палиндрома.
class StringUtils {
public:
    // Ищет палиндром максимальной длины, являющийся подстрокой в строке text.
    static std::string findLongestPalindrome(const std::string &text);

    // Находит все индексы вхождения подстроки pattern в текст text.
    // Использует префикс функцию.
    static void algorithmKnuthMorrisPratt(const std::string &text,
                                          const std::string &pattern,
                                          std::vector<int> &entry);

    // Находит все индексы вхождения подстроки pattern во входном потоке input.
    // Использует префикс функцию.
    static void algorithmKnuthMorrisPrattStreamInput(const std::string &pattern,
                                                     std::istream &input,
                                                     std::vector<int> &entry);

    // Находит все индексы вхождения подстроки pattern в текст text.
    // Использует z-функцию.
    static void zFunctionSearchString(const std::string &pattern,
                                      const std::string &text,
                                      std::vector<int> &entry);

    // Вычисляет префикс функцию строки s за O(s.length).
    static void calculatePrefixFunction(const std::string &s, std::vector<int> &prefixFunction);

    // Вычисляет z-функцию строки s за O(s.length).
    static void calculateZFunction(const std::string &s, std::vector<int> &zFunction);

private:

    static void algorithmManacherOdd(const std::string &text, std::vector<int> &palindrome);

    static void algorithmManacherEven(const std::string &text, std::vector<int> &palindrome);
};


#endif //STRINGSEARCHING_STRINGUTILS_H
