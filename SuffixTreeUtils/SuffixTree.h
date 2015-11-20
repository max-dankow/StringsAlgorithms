#ifndef STRINGSEARCHING_SUFFIXTREE_H
#define STRINGSEARCHING_SUFFIXTREE_H

#include "SuffixTreeNode.h"

// Представляет сжатое суффиксное дерево.
class SuffixTree {
public:

    explicit SuffixTree(std::string text);

    virtual ~SuffixTree();

    SuffixTreeNode *getRoot() const;

    // Печатает дерево в выходной поток output.
    void printTree(std::ostream &output) const;

    // Проверяет возможен ли в дереве переход из позиции по заданой букве.
    bool canGo(const Position &position, char letter);

    // Если возможно, возвращает позицию в дереве,
    // соответствующую переходу из заданой позиции по заданой букве.
    Position go(const Position &position, char letter);

    // Делает вершину, соотвестующую позиции, явной.
    // Если она была неявная, то разрезает ребро и создает новую явную вершину.
    // Иначе просто возвращает эту явную вершину.
    SuffixTreeNode *makeExplicit(Position position);

    // Считает количество различных подстрок в дереве.
    long long int countSubstrings();

    std::string text;
private:
    SuffixTreeNode *root;
    SuffixTreeNode *blank;
};

#endif //STRINGSEARCHING_SUFFIXTREE_H
