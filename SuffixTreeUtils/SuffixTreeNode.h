#ifndef STRINGSEARCHING_SUFFIXTREENODE_H
#define STRINGSEARCHING_SUFFIXTREENODE_H

#include "SuffixTree.h"
#include <stdlib.h>
#include <iostream>
#include <map>

class SuffixTreeNode;

// Кодирует положение при обходе сжатого суффиксного дерева:
// вершина, в которую ведет ребро и длинна оставшейся подстроки.
struct Position {
    Position();

    Position(SuffixTreeNode *finish, size_t distance) :
            finish(finish), distanceToFinish(distance) { }

    // Проверяет, является ли соответствующая вершина явной.
    bool isExplicit() const;

    // Указывает на явную вершину, в которой закачивается ребро, на котором мы находимся.
    SuffixTreeNode *finish;
    // Длинна строки оставшейся до конца ребра, начиная с текущего положения.
    size_t distanceToFinish;
};

// Представляет явную вершину в суффиксном дереве.
class SuffixTreeNode {
public:

    SuffixTreeNode(SuffixTreeNode *parent, size_t labelBegin, size_t labelEnd) :
            parent(parent), labelBegin(labelBegin), labelEnd(labelEnd) {
        suffixLink = nullptr;
    }

    virtual ~SuffixTreeNode();

    // Печатает подстроку, соответствующую ребру из родителя.
    void printNode(std::ostream &output, const std::string &text, size_t offset);

    // Добавляет переход из вершины в сторону другой вершины node по заданому символу.
    void addLink(SuffixTreeNode *node, char letter);

    void eraseLink(char letter);

    void clearLinks();

    // Индекс первого символа метки ребра, ведущего из предка.
    size_t getLabelBegin() const;

    void setLabelBegin(size_t labelBegin);

    // Индекс символа за последним символом метки ребра, ведущего из предка.
    size_t getLabelEnd() const;

    void setLabelEnd(size_t labelEnd);

    // Проверяем, существует ли ребро из данной вершины по заданной букве.
    bool canGo(char letter);

    // Если возможно, возвращает позицию в дереве,
    // соответствующую переходу из данной вершины по заданой букве.
    Position go(char letter);

    // Возвращает позицию в дереве, соответствующую данной явной вершине.
    Position getPosition();

    // Указатель на предка.
    SuffixTreeNode * getParent() const;

    void setParent(SuffixTreeNode *parent);

    SuffixTreeNode * getSuffixLink() const;

    void setSuffixLink(SuffixTreeNode *suffixLink);

    long long int getEdgeLength() const;

    long long int countSubstrings() const;

private:
    std::map<char, Position> links;
    SuffixTreeNode *parent;
    SuffixTreeNode *suffixLink;
    size_t labelBegin, labelEnd;
};


#endif //STRINGSEARCHING_SUFFIXTREENODE_H
