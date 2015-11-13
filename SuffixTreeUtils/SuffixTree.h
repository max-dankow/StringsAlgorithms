#ifndef STRINGSEARCHING_SUFFIXTREE_H
#define STRINGSEARCHING_SUFFIXTREE_H

#include "SuffixTreeNode.h"
#include <string>
#include <vector>

typedef std::ptrdiff_t NodeIndex;

class SuffixTree {
public:
    SuffixTree();

private:
    std::vector<SuffixTreeNode> nodes;
};

#endif //STRINGSEARCHING_SUFFIXTREE_H
