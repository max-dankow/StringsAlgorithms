#include "StringUtils.h"

void StringUtils::algorithmKnuthMorrisPratt(const std::string &text,
                                            const std::string &pattern,
                                            std::vector<int> &entry) {
    std::string mergedStrings = pattern + "#" +  text;
    std::vector<int> prefixFunction(pattern.length(), 0);
    int previousValue = prefixFunction[0];
    for (int i = 1; i < mergedStrings.length(); ++i)
    {
        int k = previousValue;
        while (k > 0 && mergedStrings[k] != mergedStrings[i])
        {
            k = prefixFunction[k - 1];
        }
        if (mergedStrings[i] == mergedStrings[k])
        {
            ++k;
        }
        if (i < pattern.length())
        {
            prefixFunction[i] = k;
        }
        previousValue = k;
        if (previousValue == pattern.length())
        {
            entry.push_back(i - 2 * pattern.length());
        }
    }
}

void StringUtils::calculatePrefixFunction(const std::string &s, std::vector<int> &prefixFunction) {
    prefixFunction.resize(s.length());
    prefixFunction[0] = 0;
    for (int i = 1; i < s.length(); ++i)
    {
        int k = prefixFunction[i - 1];
        while (k > 0 && s[k] != s[i])
        {
            k = prefixFunction[k - 1];
        }
        if (s[i] == s[k])
        {
            ++k;
        }
        prefixFunction[i] = k;
    }
}

void StringUtils::algorithmKnuthMorrisPrattStreamInput(const std::string &pattern,
                                                       std::istream &input,
                                                       std::vector<int> &entry) {
    std::vector<int> prefixFunction;
    calculatePrefixFunction(pattern, prefixFunction);
    int previousValue = 0;
    for (int i = pattern.length() + 1; ; ++i)
    {
        char letter;
        if (input.peek() == '\n')
        {
            break;
        }
        else
        {
            input >> letter;
        }
        int k = previousValue;
        while (k > 0 && pattern[k] != letter)
        {
            k = prefixFunction[k - 1];
        }
        if (letter == pattern[k])
        {
            ++k;
        }
        previousValue = k;
        if (previousValue == pattern.length())
        {
            entry.push_back(i - 2 * pattern.length());
        }
    }
}

void StringUtils::calculateZFunction(const std::string &s, std::vector<int> &zFunction) {
    zFunction.resize(s.length());
    zFunction[0] = (int) s.length();
    int left = 0, right = 0;
    for (int i = 1; i < s.length(); ++i)
    {
        if (i > right)
        {
            int j;
            for (j = 0; (i + j < s.length()) && (s[i + j] == s[j]); ++j);
            zFunction[i] = j;
            left = i;
            right = i + zFunction[i] - 1;
        }
        else
        {
            if (zFunction[i - left] + i <= right)
            {
                zFunction[i] = zFunction[i - left];
            }
            else
            {
                int j;
                for (j = 1; (right + j < s.length()) && (s[right + j] == s[right - i + j]); ++j);
                zFunction[i] = right - i + j;
                left = i;
                right = i + zFunction[i] - 1;
            }
        }
    }
}

void StringUtils::zFunctionSearchString(const std::string &pattern, const std::string &text, std::vector<int> &entry) {
    std::vector<int> zFunction;
    calculateZFunction(pattern, zFunction);
    int left = -1, right = -1;
    for (int i = 0; i < text.length(); ++i)
    {
        int currentZValue = 0;
        if (i > right)
        {
            int j;
            for (j = 0; (i + j< text.length()) && (text[i + j] == pattern[j]); ++j);
            currentZValue = j;
            left = i;
            right = i + j - 1;
        }
        else
        {
            if (zFunction[i - left] + i <= right)
            {
                currentZValue = zFunction[i - left];
            }
            else
            {
                int j;
                for (j = 1;
                     (right + j< text.length())
                     && (text[right + j] == pattern[right - i + j]);
                     ++j);
                currentZValue = right - i + j;
                left = i;
                right = right + j - 1;
            }
        }
        if (currentZValue == pattern.length())
        {
            entry.push_back(i);
        }
    }
}

void StringUtils::algorithmManacherOdd(const std::string &text, std::vector<int> &palindrome) {
    palindrome.resize(text.length());
    if (text.empty())
    {
        return;
    }
    palindrome[0] = 1;
    int left = 0, right = -1;
    for (int i = 1; i < text.length(); ++i)
    {
        if (i > right)
        {
            int extend;
            for (extend = 0;
                 (i - extend >= 0)
                 && (i + extend < text.length())
                 && (text[i + extend] == text[i - extend]);
                 ++extend);
            palindrome[i] = extend;
            left = i - extend + 1;
            right = i + extend - 1;
        }
        else
        {
            int mirror = left + (right - i);
            if (palindrome[mirror] + i <= right)
            {
                palindrome[i] = palindrome[mirror];
            }
            else
            {
                int extend;
                for (extend = 1;
                     (i - (right - i) - extend >= 0)
                     && (right + extend < text.length())
                     && (text[right + extend] == text[i - (right - i) - extend]);
                     ++extend);
                palindrome[i] = right - i + extend;
                left = i - palindrome[i] + 1;
                right = i + palindrome[i] - 1;
            }
        }
    }
}

void StringUtils::algorithmManacherEven(const std::string &text, std::vector<int> &palindrome) {
    palindrome.resize(text.length());
    if (text.empty())
    {
        return;
    }
    palindrome[0] = 0;
    int left = 0, right = -1;
    for (int i = 1; i < text.length(); ++i)
    {
        if (i > right)
        {
            int extend;
            for (extend = 1;
                 (i - extend >= 0)
                 && (i + extend - 1 < text.length())
                 && (text[i + extend - 1] == text[i - extend]);
                 ++extend);
            palindrome[i] = extend - 1;
            left = i - palindrome[i];
            right = i + palindrome[i] - 1;
        }
        else
        {
            int mirror = left + right - i + 1;
            if (palindrome[mirror] + i - 1 < right)
            {
                palindrome[i] = palindrome[mirror];
            }
            else
            {
                int extend;
                for (extend = 1;
                     (i - (right - i) - extend >= 0)
                     && (right + extend - 1 < text.length())
                     && (text[right + extend - 1] == text[i - (right - i) - extend]);
                     ++extend);
                palindrome[i] = right - i + extend - 1;
                left = i - palindrome[i];
                right = i + palindrome[i] - 1;
            }
        }
    }
}

std::string StringUtils::findLongestPalindrome(const std::string &text) {
    std::vector<int> palindrome;
    int maxPalStart = 0;
    int maxPalLength = 0;
    // Ищем максимальные нечетные палиндромы:
    algorithmManacherOdd(text, palindrome);
    for (int i = 0; i < palindrome.size(); ++i)
    {
        int currentPalindromeLength = palindrome[i] * 2 - 1;
        if (currentPalindromeLength > maxPalLength)
        {
            maxPalLength = currentPalindromeLength;
            maxPalStart = i - palindrome[i] + 1;
        }
    }
    // Ищем максимальные четные палиндромы:
    algorithmManacherEven(text, palindrome);
    for (int i = 0; i < palindrome.size(); ++i)
    {
        int currentPalindromeLength = (int) (palindrome[i] * 2);
        if (currentPalindromeLength > maxPalLength)
        {
            maxPalLength = currentPalindromeLength;
            maxPalStart = i - palindrome[i];
        }
    }
    return std::string(text.begin() + maxPalStart, text.begin() + maxPalStart + maxPalLength);
}