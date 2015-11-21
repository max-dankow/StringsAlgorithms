#ifndef STRINGUTILS_INDUCEDSORTING_H
#define STRINGUTILS_INDUCEDSORTING_H


#include <vector>
#include <string>
#include <stdlib.h>

class InducedSorting {
public:
    std::vector<size_t> buildSuffixArray(const std::string inputText);

private:
    enum Types {
        L_TYPE,
        S_TYPE
    };
    struct Bucket {
        size_t start, end, position;
    };

    std::vector<Types> classify(const std::string text) const;

    std::vector<size_t> getLMSIndices(const std::vector<Types> &types) const;

    std::vector<Bucket> separateIntoBuckets();

    std::vector<size_t> induceSuffixArray(const std::vector<size_t> &reducedSuffixArray);

    std::vector<size_t> inducedSorting(const std::vector<size_t> &LMSIndices);
};


#endif //STRINGUTILS_INDUCEDSORTING_H
