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

    const std::shared_ptr<SuffixTreeNode> &getRoot() const;

    void printTree(std::ostream &output);

//    Position go(Position from, char letter);

    std::string text;
    std::shared_ptr<SuffixTreeNode> blank;
private:
//    bool tryGetNextLetter(Position position, char nextLetter);
    std::shared_ptr<SuffixTreeNode> root;
};

#endif //STRINGSEARCHING_SUFFIXTREE_H
