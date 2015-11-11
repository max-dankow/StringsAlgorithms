#ifndef STRINGSEARCHING_UKKONENALGORITHM_H
#define STRINGSEARCHING_UKKONENALGORITHM_H

#include "ISuffixTreeBuilder.h"

class UkkonenAlgorithm : public ISuffixTreeBuilder {
    virtual SuffixTree buildSuffixTree(std::string);
};


#endif //STRINGSEARCHING_UKKONENALGORITHM_H
