#ifndef STRINGSEARCHING_SUFFIXTREE_H
#define STRINGSEARCHING_SUFFIXTREE_H

#include "SuffixTreeNode.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class SuffixTree {
public:

    SuffixTree(std::string text);

    SuffixTreeNode * getRoot() const;

    void printTree(std::ostream &output);

//    Position go(Position from, char letter);

    std::string text;
    SuffixTreeNode *blank;
private:
//    bool tryGetNextLetter(Position position, char nextLetter);
    SuffixTreeNode *root;
};

#endif //STRINGSEARCHING_SUFFIXTREE_H
