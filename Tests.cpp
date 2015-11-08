#include <gtest/gtest.h>
#include "StringUtils.h"
#include <random>

bool isPalindrome(const std::string text) {
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
    for (auto i = text.begin(); i != text.end(); ++i)
    {
        for (auto j = i; j != text.end(); ++j)
        {
            std::string current = std::string(i, j + 1);
            if (isPalindrome(current) && (j - i + 1 > maxPalLength)) {
                maxPalindrome = current;
                maxPalLength = maxPalindrome.length();
            }
        }
    }
    return maxPalindrome;
}

TEST(ManualTests, TestABACABABA) {
    ASSERT_EQ(StringUtils::findLongestPalindrome("abacababa"), "abacaba");
}

TEST(CheckerTesting, isPalindromeTests) {
    ASSERT_EQ(false, isPalindrome("abc"));
    ASSERT_EQ(true, isPalindrome("abababa"));
    ASSERT_EQ(false, isPalindrome("abccb"));
    ASSERT_EQ(true, isPalindrome("abccba"));
    ASSERT_EQ(true, isPalindrome(""));
    ASSERT_EQ(true, isPalindrome("a"));
    ASSERT_EQ(true, isPalindrome(")))))"));
}

TEST(SmallForceChecked, ManualStrings) {
    ASSERT_EQ(stupidMaxPalindrome("abacababcbabcbababa"), StringUtils::findLongestPalindrome("abacababcbabcbababa"));
    ASSERT_EQ(stupidMaxPalindrome(""), StringUtils::findLongestPalindrome(""));
    ASSERT_EQ(stupidMaxPalindrome("aba"), StringUtils::findLongestPalindrome("aba"));
    ASSERT_EQ(stupidMaxPalindrome("aaaabb"), StringUtils::findLongestPalindrome("aaaabb"));
}

std::default_random_engine generator;
std::string generateRandomString(size_t minLength, size_t maxLength,
                                 char minLetter, char maxLetter) {
    // todo: refactor
    assert(minLength <= maxLength);
    std::uniform_int_distribution<char> ValuesChar(minLetter, maxLetter);
    std::uniform_int_distribution<size_t> Lengths(minLength, maxLength);
    size_t lengthStr = Lengths(generator);

    std::string element;
    element.reserve(lengthStr);

    for (int i = 0; i <= lengthStr; i++)
        element += ValuesChar(generator);

    return element;
}

TEST(SmallForceChecked, RandomStrings20) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(10, 20, 'a', 'z');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }

}

TEST(SmallForceChecked, RandomStrings200) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(100, 200, 'a', 'z');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }

}

//TEST(SmallForceChecked, RandomStrings2000) {
//    for (int i = 0; i < 100; ++i) {
//        std::string randomString = generateRandomString(1000, 2000);
//        ASSERT_EQ(stupidMaxPalindrome(randomString),
//                  StringUtils::findLongestPalindrome(randomString));
//    }
//
//}

TEST(SmallForceChecked, RandomStringsAny) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(0, 1000, 'a', 'z');
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }

}

TEST(SmallForceChecked, RandomStringsABC) {
    for (int i = 0; i < 100; ++i) {
        std::string randomString = generateRandomString(100, 200, 'a', 'c');
        std::cerr << randomString << "\n";
        ASSERT_EQ(stupidMaxPalindrome(randomString),
                  StringUtils::findLongestPalindrome(randomString));
    }

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}