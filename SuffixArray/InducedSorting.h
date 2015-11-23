#ifndef STRINGUTILS_INDUCEDSORTING_H
#define STRINGUTILS_INDUCEDSORTING_H


#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>

class InducedSorting {
public:
    std::vector<size_t> buildSuffixArray(const std::string text);

    struct LMS {
        LMS(size_t begin, size_t end, size_t index) :
                begin(begin), end(end), index(index) { }

        size_t begin, end, index;
    };

    enum Types {
        L_TYPE,
        S_TYPE
    };
private:
    struct Bucket {
        size_t begin, end, position, sBegin;
    };

    std::vector<size_t> SuffixArrayInducedSorting(const std::vector<long long> &text);

    std::vector<Types> classify(const std::vector<long long> text) const;

    std::vector<LMS> getLMSIndices(const std::vector<Types> &types) const;

    std::vector<InducedSorting::Bucket> separateIntoBuckets(const std::vector<long long> &text,
                                                            const std::vector<Types> &types);

    std::vector<size_t> induceSuffixArray(const std::vector<long long> &text,
                                          const std::vector<LMS> &LMSIndices,
                                          const std::vector<Types> &types);

    void printBuckets(const std::vector<Bucket> &buckets,
                      const std::vector<ssize_t> &sa,
                      std::ostream &output);

    std::vector<LMS> sortLMS(const std::vector<LMS> &LMSIndices,
                             const std::vector<long long> &text,
                             const std::vector<Types> types);

    bool getNames(const std::vector<InducedSorting::LMS> &lmsSorted, const std::vector<long long> &text,
                  const std::vector<InducedSorting::Types> &types, std::vector<long long> &names);

    std::vector<long long> convertToLongVector(const std::string &text);
};


#endif //STRINGUTILS_INDUCEDSORTING_H
