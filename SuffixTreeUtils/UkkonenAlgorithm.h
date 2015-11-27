#ifndef STRINGSEARCHING_UKKONENALGORITHM_H
#define STRINGSEARCHING_UKKONENALGORITHM_H

#include "SuffixTree.h"
#include <limits>

class UkkonenAlgorithm {
public:
    static SuffixTree buildSuffixTree(const std::string &text);

private:
    static Position updateTree(SuffixTree &tree, size_t index, const Position &activePoint);

    static Position findSuffixLink(SuffixTree &tree, const Position &position);
};


#endif //STRINGSEARCHING_UKKONENALGORITHM_H
