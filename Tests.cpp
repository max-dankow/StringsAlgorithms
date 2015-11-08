#include <gtest/gtest.h>
#include "StringUtils.h"

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
            if (isPalindrome(current) && (j - i > maxPalLength)) {
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

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}