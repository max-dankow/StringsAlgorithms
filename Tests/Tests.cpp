#include <gtest/gtest.h>
#include "../StringUtils.h"
#include "../SuffixTreeUtils/SuffixTree.h"
#include "../SuffixTreeUtils/UkkonenAlgorithm.h"
#include "../SuffixArray/InducedSorting.h"
#include <chrono>

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

// Тесты для поиска максимального палиндрома.
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

// Тесты для алгоритма поиска числа подстрок.

long long stupidCountSubstrings(std::string text) {
    std::set<std::string> set;
    for (auto begin = 0; begin < text.length(); ++begin) {
        for (auto end = begin; end < text.length(); ++end) {
            std::string current(text.begin() + begin, text.begin() + end + 1);
            if (current.empty()) {
                continue;
            }
            if (set.find(current) == set.end()) {
                set.insert(current);
            }
        }
    }
    return (long long int) set.size();
}

TEST(AllSubstringsTests, RandomStringsAZ1000) {
    UkkonenAlgorithm ukkonenAlgorithm;
    for (size_t i = 0; i < 25; ++i) {
        std::string text = generateRandomString(5, 1000, 'a', 'z');
        SuffixTree suffixTree = ukkonenAlgorithm.buildSuffixTree(text);
        ASSERT_EQ(stupidCountSubstrings(text), suffixTree.countSubstrings());
    }
}

TEST(AllSubstringsTests, RandomStringsAC100) {
    UkkonenAlgorithm ukkonenAlgorithm;
    for (size_t i = 0; i < 100; ++i) {
        std::string text = generateRandomString(0, 100, 'a', 'c');
        SuffixTree suffixTree = ukkonenAlgorithm.buildSuffixTree(text);
        ASSERT_EQ(stupidCountSubstrings(text), suffixTree.countSubstrings());
    }
}

TEST(DurationUkkonen, Duration) {
    const int TEST_NUMBER = 10;
    std::chrono::milliseconds averageTime(0);
    for (int i = 0; i < TEST_NUMBER; ++i) {
        std::string text = generateRandomString(100000, 100000, 'a', 'z');
        auto startTime = std::chrono::steady_clock::now();
        UkkonenAlgorithm algorithm;
        SuffixTree tree = algorithm.buildSuffixTree(text);
        auto endTime = std::chrono::steady_clock::now();
        std::chrono::milliseconds workTime = std::chrono::milliseconds(
                std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime));
        averageTime += workTime;
//        std::cerr << "Running time " << workTime.count() << "ms.\n";
    }
    std::cerr << "Average time " << averageTime.count() / TEST_NUMBER << "ms.\n";
}

// Тесты для суффисного массива.
struct Suffix {
    Suffix() { }

    Suffix(std::string text, size_t index) : text(text), index(index) { }

    std::string text;
    size_t index;
//    bool operator<(const Suffix &other) {
//        return this->text < other.text;
//    }
};

bool operator<(const Suffix &a, const Suffix &b) {
    return a.text < b.text;
}


std::vector<size_t> stupidSuffixArray(const std::string text) {
    std::vector<Suffix> suf;
    for (size_t i = 0; i < text.length(); ++i) {
        suf.emplace_back(std::string(text.begin() + i, text.end()), i);
    }
    std::sort(suf.begin(), suf.end());
    std::vector<size_t> answer;
    for (Suffix s : suf) {
        answer.push_back(s.index);
    }
    return answer;
}

TEST(SuffixArrayTests, ManualTexts) {
    InducedSorting algorithm;
    std::string text = "immissiissippi";
    std::vector<size_t> suffixArray = {13, 6, 0, 10, 3, 7, 2, 1, 12, 11, 5, 9, 4, 8};
    ASSERT_EQ(suffixArray, algorithm.buildSuffixArray(text));
    ASSERT_EQ(stupidSuffixArray("caacabccba"), algorithm.buildSuffixArray("caacabccba"));
    ASSERT_EQ(stupidSuffixArray(
            "yngjoqdizwqbavpazpgdralvbjgkjngehyjpyldplbjumixyvdkmdgkhsiwgigafwfricwyggqqsjqwjugcjbnnmsfietnatduewdipleuzxlvhqkjjnratgftmenoecpwwcxbmdcxejjungyacbggyfdbwkpfldyikmmpadepatppzwfipztjgmnjwpbmtajgdxxcahpblpdxkmkqakbuczcjpvjbdeofkfimrmbkrfoubjrubbwvsvmmehucjutrcfpgofpfamtfxspcftxzsaizpsieaznavwcvcvyppcwbubafihcuubhgjiijsvjniujyazuyxqwuuawtavsaducrmegvctmsavyorhhinvqrqcqfxbzxulzqlzzogizllomcnahdjluoukcrltshxcwsfnrzwvmcewiexefzevjudvbrdvllhypwyhhanochwvztxdalehsqtsbycpskvjgwxqfpiiidgtkegtdfbetqhcqohtxswlyiahhiyxgczcirtlharewwfohxexddmznbumhxxeyyxsukrdbwuptptmobpypsbrlamdbiiwhvwoywaycxgtgdrrvhlzgyjodqwwquawkwpjuullxfxccjyejppauauqdjrzflhbaadzjjljtbiuxlpyaenguafmlppxrlmzrehoreepusitqazmqhmnlirrecyjelxklnfpjhmklryvetqcfujddxnqhgkmiopscejmqwjzwyolukxhowoorijuvhunipksigpgwunbbthjxrmgniaptdljszjrxphsrxfeodehexfsixbtlqroyttauubmeulkzlfjjfhbpoqejdvhruzphrtdsrheyxttmvybwydmkczstwtrqpgsvhrjzzqyk"),
              algorithm.buildSuffixArray(
                      "yngjoqdizwqbavpazpgdralvbjgkjngehyjpyldplbjumixyvdkmdgkhsiwgigafwfricwyggqqsjqwjugcjbnnmsfietnatduewdipleuzxlvhqkjjnratgftmenoecpwwcxbmdcxejjungyacbggyfdbwkpfldyikmmpadepatppzwfipztjgmnjwpbmtajgdxxcahpblpdxkmkqakbuczcjpvjbdeofkfimrmbkrfoubjrubbwvsvmmehucjutrcfpgofpfamtfxspcftxzsaizpsieaznavwcvcvyppcwbubafihcuubhgjiijsvjniujyazuyxqwuuawtavsaducrmegvctmsavyorhhinvqrqcqfxbzxulzqlzzogizllomcnahdjluoukcrltshxcwsfnrzwvmcewiexefzevjudvbrdvllhypwyhhanochwvztxdalehsqtsbycpskvjgwxqfpiiidgtkegtdfbetqhcqohtxswlyiahhiyxgczcirtlharewwfohxexddmznbumhxxeyyxsukrdbwuptptmobpypsbrlamdbiiwhvwoywaycxgtgdrrvhlzgyjodqwwquawkwpjuullxfxccjyejppauauqdjrzflhbaadzjjljtbiuxlpyaenguafmlppxrlmzrehoreepusitqazmqhmnlirrecyjelxklnfpjhmklryvetqcfujddxnqhgkmiopscejmqwjzwyolukxhowoorijuvhunipksigpgwunbbthjxrmgniaptdljszjrxphsrxfeodehexfsixbtlqroyttauubmeulkzlfjjfhbpoqejdvhruzphrtdsrheyxttmvybwydmkczstwtrqpgsvhrjzzqyk"));

}

long long isSuffixArrayEqual(std::vector<size_t> expected, std::vector<size_t> actual) {
    if (expected.size() != actual.size()) {
        return 0;
    }
    for (size_t i = 0; i < expected.size(); ++i) {
        if (expected[i] != actual[i]) {
            return i;
        }
    }
    return -1;
}

TEST(SuffixArrayTests, RandomTexts) {
    InducedSorting algorithm;
    for (size_t i = 0; i < 1000; ++i) {
        std::string text = generateRandomString(1, 10000, 'a', 'z');
//        std::cerr << text << "\n\n";
        std::vector<size_t> suffixArray = stupidSuffixArray(text);
        std::vector<size_t> suffixArray2 = algorithm.buildSuffixArray(text);
//        int start = isSuffixArrayEqual(suffixArray, suffixArray2);
//        for (size_t j = start; j <suffixArray.size();++j) {
//            std::cerr << suffixArray[j] << ' ' << suffixArray2[j]<<"\n";
//        }
//        std::cerr << '\n';
//        std::cerr << '\n';
//        std::cerr<< isSuffixArrayEqual(suffixArray, suffixArray2) << "\n\n";
        ASSERT_EQ(suffixArray, suffixArray2);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}