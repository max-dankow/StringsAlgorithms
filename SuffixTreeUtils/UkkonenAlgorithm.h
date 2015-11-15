#ifndef STRINGSEARCHING_UKKONENALGORITHM_H
#define STRINGSEARCHING_UKKONENALGORITHM_H

#include "ISuffixTreeBuilder.h"
#include <limits>

class UkkonenAlgorithm : public ISuffixTreeBuilder {
public:
    static const size_t INFINITY = std::numeric_limits::infinity();
    virtual SuffixTree buildSuffixTree(const std::string &text);

private:
    Position updateTree(SuffixTree &tree, size_t index, Position activePoint);

    Position findSuffixLink(SuffixTree &tree, Position position);

    std::shared_ptr<SuffixTreeNode> testAndSplit(Position position, size_t index);
};


#endif //STRINGSEARCHING_UKKONENALGORITHM_H
