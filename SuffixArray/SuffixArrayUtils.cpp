#include "SuffixArrayUtils.h"

std::vector<long long> SuffixArrayUtils::computeLCP(const std::string text,
                                                    const std::vector<size_t> suffixArray) {
    std::vector<size_t> pos(text.length());
    std::vector<long long> lcp(text.length());
    for (size_t i = 0; i < text.length(); ++i) {
        pos[suffixArray[i]] = i;
    }
    long long k = 0;
    for (long long i = 0; i < text.length(); ++i) {
        if (k > 0) {
            --k;
        }
        if (pos[i] == text.length() - 1) {
            lcp[text.length() - 1] = -1;
            k = 0;
        } else {
            long long j = (int) suffixArray[pos[i] + 1];
            while ((std::max(i + k, j + k) < text.length()) && (text[i + k] == text[j + k])) {
                ++k;
            }
        }
        lcp[pos[i]] = k;
    }
    return lcp;
}

long long SuffixArrayUtils::countSubstrings(const std::string &text) {
    std::string extendedText = text + "&";
    InducedSorting algorithm;
    std::vector<size_t> suffixArray = algorithm.buildSuffixArray(extendedText);
    std::vector<long long> lcp = computeLCP(extendedText, suffixArray);
    long long count = 0;
    for (size_t i = 0; i < extendedText.length(); ++i) {
        count += text.length() - suffixArray[i];
        if (i > 0) {
            count -= lcp[i];
        }
    }
    return count;
}
