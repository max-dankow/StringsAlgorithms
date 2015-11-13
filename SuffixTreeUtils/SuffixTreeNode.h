#ifndef STRINGSEARCHING_SUFFIXTREENODE_H
#define STRINGSEARCHING_SUFFIXTREENODE_H

#include "SuffixTree.h"
#include <vector>
#include <map>
#include <stdlib.h>
#include <memory>

class SuffixTreeNode;

// Кодирует положение при обходе сжатого суффиксного дерева:
// вершина, в которую ведет ребро и длинна оставшейся подстроки.
class Position {
public:
    Position(std::shared_ptr<SuffixTreeNode> finish, size_t distance) :
            finish(finish), distanceToFinish(distance) { }

private:
    std::shared_ptr<SuffixTreeNode> finish;
    size_t distanceToFinish;
};

class SuffixTreeNode {
public:

    SuffixTreeNode(std::shared_ptr<SuffixTreeNode> parent, size_t labelBegin, size_t labelEnd) :
            parent(parent), labelBegin(labelBegin), labelEnd(labelEnd) { }

private:
    std::shared_ptr<SuffixTreeNode> parent;
    std::shared_ptr<SuffixTreeNode> suffixLink;
    size_t labelBegin, labelEnd;
    std::map<char, Position> links;
};


#endif //STRINGSEARCHING_SUFFIXTREENODE_H
