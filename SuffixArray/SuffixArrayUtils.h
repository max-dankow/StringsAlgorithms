#ifndef STRINGUTILS_SUFFIXARRAYUTILS_H
#define STRINGUTILS_SUFFIXARRAYUTILS_H

#include <vector>
#include <string>
#include "InducedSorting.h"


class SuffixArrayUtils {
public:
    static std::vector<long long> computeLCP(const std::string text, const std::vector<size_t> suffixArray);

    static long long countSubstrings(const std::string &text);
};


#endif //STRINGUTILS_SUFFIXARRAYUTILS_H
