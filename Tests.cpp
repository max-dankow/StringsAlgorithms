#include <gtest/gtest.h>
#include "StringUtils.h"
#include <random>

bool isPalindrome(const std::string &text) {
    auto begin = text.begin();
    auto end = --text.end();
    while (begin < end && *begin == *end) {
        ++begin;
        --end;
    }
    return begin >= end;
}

std::string stupidMaxPalindrome(const std::string &text) {
    std::string maxPalindrome = "";
    size_t maxPalLength = 0;
    for (auto i = text.begin(); i != text.end(); ++i) {
        for (auto j = i; j != text.end(); ++j) {
            std::string current = std::string(i, j + 1);
            if (isPalindrome(current) && (j - i + 1 > maxPalLength)) {
                maxPalindrome = current;
                maxPalLength = maxPalindrome.length();
            }
        }
    }
    return maxPalindrome;
}

TEST(CheckerTesting, isPalindromeTests) {
    ASSERT_EQ(false, isPalindrome("abc"));
    ASSERT_EQ(false, isPalindrome("aab"));
    ASSERT_EQ(true, isPalindrome("abababa"));
    ASSERT_EQ(false, isPalindrome("abccb"));
    ASSERT_EQ(true, isPalindrome("abccba"));
    ASSERT_EQ(true, isPalindrome(""));
    ASSERT_EQ(true, isPalindrome("a"));
    ASSERT_EQ(true, isPalindrome("aa"));
    ASSERT_EQ(true, isPalindrome(")))))"));
}

TEST(ForceChecked, ManualStrings) {
    ASSERT_EQ(stupidMaxPalindrome("abacababcbabcbababa"), StringUtils::findLongestPalindrome("abacababcbabcbababa"));
    ASSERT_EQ(stupidMaxPalindrome(""), StringUtils::findLongestPalindrome(""));
    ASSERT_EQ(stupidMaxPalindrome("aaaaaaaaaa"), StringUtils::findLongestPalindrome("aaaaaaaaaa"));
    ASSERT_EQ(stupidMaxPalindrome("aba"), StringUtils::findLongestPalindrome("aba"));
    ASSERT_EQ(stupidMaxPalindrome("aaaabb"), StringUtils::findLongestPalindrome("aaaabb"));
    ASSERT_EQ(stupidMaxPalindrome(
            "baaaccacaaaaaacaaaaaccbaaacbbcbcacccacccbabacacabbcbaaabbabbcbacccbacaabbcaaccaacccaabbbabacbaabbcabbbabcaacbcab"),
              StringUtils::findLongestPalindrome(
                      "baaaccacaaaaaacaaaaaccbaaacbbcbcacccacccbabacacabbcbaaabbabbcbacccbacaabbcaaccaacccaabbbabacbaabbcabbbabcaacbcab"));
    ASSERT_EQ(stupidMaxPalindrome(
            "caabccbccacbcbabacccabcaacbabcbccbbccbbccbbacaaabcacaacbabccacbbcbbaabcbbcbabacbaababbcbcaacaccabccbabcacabbcbbabbbbcbabbccaccaaaccaacabbcbbabaacaccabbacabaccbbccbcbcaccccbacbbcaaccccbccabccbba"),
              StringUtils::findLongestPalindrome(
                      "caabccbccacbcbabacccabcaacbabcbccbbccbbccbbacaaabcacaacbabccacbbcbbaabcbbcbabacbaababbcbcaacaccabccbabcacabbcbbabbbbcbabbccaccaaaccaacabbcbbabaacaccabbacabaccbbccbcbcaccccbacbbcaaccccbccabccbba"));
}

static std::default_random_engine randomGenerator;

std::string generateRandomString(size_t minLength, size_t maxLength,
                                 char minLetter, char maxLetter) {
    assert(minLength <= maxLength && minLetter <= maxLetter);
    std::uniform_int_distribution<char> randomLetter(minLetter, maxLetter);
    std::uniform_int_distribution<size_t> randomLength(minLength, maxLength);
    size_t length = randomLength(randomGenerator);

    std::string randomString;
    randomString.reserve(length);

    for (int i = 0; i < length; i++)
        randomString += randomLetter(randomGenerator);

    return randomString;
}

TEST(ForceChecked, RandomStrings10) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(7, 13, 'a', 'z');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }

}

TEST(ForceChecked, RandomStrings100) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(90, 110, 'a', 'z');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }

}

TEST(ForceChecked, RandomStrings2000) {
    for (int i = 0; i < 25; ++i) {
        std::string randomString = generateRandomString(1000, 2000, 'a', 'z');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }
}

TEST(ForceChecked, RandomStringsAny) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(0, 1000, 'a', 'z');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }
}

TEST(ForceChecked, RandomStringsABC) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(100, 200, 'a', 'c');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }
}

TEST(ForceChecked, RandomStringsAB) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(500, 900, 'a', 'b');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}