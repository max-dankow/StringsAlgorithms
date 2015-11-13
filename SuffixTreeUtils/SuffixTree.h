#ifndef STRINGSEARCHING_SUFFIXTREE_H
#define STRINGSEARCHING_SUFFIXTREE_H

#include "SuffixTreeNode.h"
#include <string>
#include <vector>
#include <memory>

class SuffixTree {
public:

    SuffixTree();

private:
    std::shared_ptr<SuffixTreeNode> root;
};

#endif //STRINGSEARCHING_SUFFIXTREE_H
