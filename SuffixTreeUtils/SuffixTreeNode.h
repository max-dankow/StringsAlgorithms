#ifndef STRINGSEARCHING_SUFFIXTREENODE_H
#define STRINGSEARCHING_SUFFIXTREENODE_H

#include "SuffixTree.h"
#include <vector>
#include <map>
#include <stdlib.h>
#include <memory>
#include <stdexcept>

class SuffixTreeNode;

// Кодирует положение при обходе сжатого суффиксного дерева:
// вершина, в которую ведет ребро и длинна оставшейся подстроки.
struct Position {
    Position();

    Position(SuffixTreeNode *finish, size_t distance) :
            finish(finish), distanceToFinish(distance) { }

    bool isExplicit();

    SuffixTreeNode *finish;
    size_t distanceToFinish;
};

// Представляет явную вершину в суффиксном дереве.
class SuffixTreeNode {
public:

    SuffixTreeNode(SuffixTreeNode *parent, size_t labelBegin, size_t labelEnd) :
            parent(parent), labelBegin(labelBegin), labelEnd(labelEnd) {
        suffixLink = nullptr;
    }

    void printNode(std::ostream &output, const std::string &text, size_t offset);

    // Добавляет переход из вершины в сторону другой вершины node по символу c.
    void addLink(SuffixTreeNode *node, char c);

    // Индекс первого символа метки ребра, ведущего из предка.
    size_t getLabelBegin() const;

    void setLabelBegin(size_t labelBegin);

    // Индекс символа за последним символом метки ребра, ведущего из предка.
    size_t getLabelEnd() const;

    void setLabelEnd(size_t labelEnd);

    bool canGo(char letter);

    Position go(char letter);

    // Указатель на предка.
    SuffixTreeNode * getParent() const;

    void setParent(SuffixTreeNode *parent);

    SuffixTreeNode * getSuffixLink() const;

    void setSuffixLink(SuffixTreeNode *suffixLink);

    Position getPosition();

    std::map<char, Position> links;

private:
    SuffixTreeNode *parent;
    SuffixTreeNode *suffixLink;
    size_t labelBegin, labelEnd;
};


#endif //STRINGSEARCHING_SUFFIXTREENODE_H
