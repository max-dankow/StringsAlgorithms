#ifndef STRINGSEARCHING_SUFFIXTREE_H
#define STRINGSEARCHING_SUFFIXTREE_H

#include "SuffixTreeNode.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <limits>
#include <stdexcept>

class SuffixTree {
public:

    static const size_t INFINITY_ = std::numeric_limits<size_t>::max();

    SuffixTree(std::string text);

    SuffixTreeNode * getRoot() const;

    void printTree(std::ostream &output);

    bool canGo(Position from, char letter);

    Position go(Position from, char letter);


    std::string text;
    SuffixTreeNode *blank;

    SuffixTreeNode *testAndSplit(Position position);

private:
//    bool tryGetNextLetter(Position position, char nextLetter);
    SuffixTreeNode *root;

};

#endif //STRINGSEARCHING_SUFFIXTREE_H
