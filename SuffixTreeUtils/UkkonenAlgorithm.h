#ifndef STRINGSEARCHING_UKKONENALGORITHM_H
#define STRINGSEARCHING_UKKONENALGORITHM_H

#include "ISuffixTreeBuilder.h"

class UkkonenAlgorithm : public ISuffixTreeBuilder {
public:
    virtual SuffixTree buildSuffixTree(const std::string &text);

private:
    Position activePoint;

    void updateTree(SuffixTree &tree, char c);
};


#endif //STRINGSEARCHING_UKKONENALGORITHM_H
