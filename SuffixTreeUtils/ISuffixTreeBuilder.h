#ifndef STRINGSEARCHING_ISUFFIXBUILDER_H
#define STRINGSEARCHING_ISUFFIXBUILDER_H

#include "SuffixTree.h"
#include <string>

class ISuffixTreeBuilder {
    virtual SuffixTree buildSuffixTree(const std::string &text) = 0;
};

#endif //STRINGSEARCHING_ISUFFIXBUILDER_H
