#ifndef STRINGSEARCHING_UKKONENALGORITHM_H
#define STRINGSEARCHING_UKKONENALGORITHM_H

//#include "ISuffixTreeBuilder.h"
#include "SuffixTree.h"
#include <limits>

class UkkonenAlgorithm /*: public ISuffixTreeBuilder */{
public:
    SuffixTree buildSuffixTree(const std::string &text);

private:
    Position updateTree(SuffixTree &tree, size_t index, Position activePoint);

    Position findSuffixLink(SuffixTree &tree, Position position);


};


#endif //STRINGSEARCHING_UKKONENALGORITHM_H
