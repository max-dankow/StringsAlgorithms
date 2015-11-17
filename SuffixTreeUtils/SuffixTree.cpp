#include <assert.h>
#include "SuffixTree.h"

SuffixTree::SuffixTree(std::string text) : text(text) {
    // Создаем фиктивную вершину для унификации операций.
    // Т.к. root.parent будет ссылаться на newBlank, то он не удалится при завершении функции.
    blank = new SuffixTreeNode(nullptr, 0, 0);
    root = new SuffixTreeNode(nullptr, std::numeric_limits<size_t>::max(), 0);
    // Из фиктивной вершины в root ведут ребра со всеми символами алфавита.
    // todo: сделать более универсальное задание алфавита.
    for (char c = 'a'; c <= 'z'; ++c) {
        blank->addLink(root, c);
    }
    root->setSuffixLink(blank);
}

SuffixTreeNode * SuffixTree::getRoot() const {
    return root;
}

bool SuffixTree::canGo(Position from, char letter) {
    if (from.isExplicit()) {
        return from.finish->canGo(letter);
    } else {
        size_t nextLetterIndex = from.finish->getLabelEnd() - from.distanceToFinish;
        assert(nextLetterIndex < text.length());
        return text[nextLetterIndex] == letter;
    }
}

Position SuffixTree::go(Position from, char letter) {
    if (from.isExplicit()) {
        return from.finish->go(letter);
    } else {
        if (canGo(from, letter)) {
            return Position(from.finish, from.distanceToFinish - 1);
        } else {
            throw std::logic_error("Wrong letter.");
        }
    }
}

void SuffixTree::printTree(std::ostream &output) {
    output << '.';
    root->printNode(output, text, 0);
    output << "-------------------------\n";
}

SuffixTreeNode *SuffixTree::testAndSplit(Position position) {
    SuffixTreeNode *finishNode = position.finish;
    if (position.isExplicit()) {
        return finishNode;
    }
    size_t currentLetterIndex = finishNode->getLabelEnd() - position.distanceToFinish;
    SuffixTreeNode *parent = finishNode->getParent();
    SuffixTreeNode *newNode = new SuffixTreeNode(parent,
                                                 finishNode->getLabelBegin(),
                                                 currentLetterIndex);
    finishNode->setLabelBegin(currentLetterIndex);
    finishNode->setParent(newNode);
    finishNode->setParent(newNode);
    parent->links.erase(text[newNode->getLabelBegin()]);
    parent->addLink(newNode, text[newNode->getLabelBegin()]);
    newNode->addLink(finishNode, text[finishNode->getLabelBegin()]);
    return newNode;
}

long long int SuffixTree::countSubstrings() {
    return root->countSubstrings() - 1;
}
