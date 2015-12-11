#include <assert.h>
#include "SuffixTree.h"
#include <vector>
#include <memory>
#include <limits>

SuffixTree::SuffixTree(const std::string &text) : text(text) {
    // Создаем фиктивную вершину для унификации операций.
    blank = new SuffixTreeNode(nullptr, 0, 0);
    root = new SuffixTreeNode(nullptr, std::numeric_limits<size_t>::max(), 0);
    // Из фиктивной вершины в root ведут ребра со всеми символами алфавита.
    // todo: сделать более универсальное задание алфавита.
    for (char c = 'a'; c <= 'z'; ++c) {
        blank->addLink(root, c);
    }
    root->setSuffixLink(blank);
}

bool SuffixTree::canGo(const Position &position, char letter) const {
    if (position.isExplicit()) {
        return position.finish->canGo(letter);
    } else {
        size_t nextLetterIndex = position.finish->getLabelEnd() - position.distanceToFinish;
        assert(nextLetterIndex < text.length());
        return text[nextLetterIndex] == letter;
    }
}

Position SuffixTree::go(const Position &position, char letter) {
    if (position.isExplicit()) {
        return position.finish->go(letter);
    } else {
        if (canGo(position, letter)) {
            return Position(position.finish, position.distanceToFinish - 1);
        } else {
            throw std::logic_error("Wrong letter.");
        }
    }
}

void SuffixTree::printTree(std::ostream &output) const {
    output << '.';
    root->printNode(output, text, 0);
    output << "-------------------------\n";
}

SuffixTreeNode *SuffixTree::makeExplicit(const Position &position) {
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

    parent->eraseLink(text[newNode->getLabelBegin()]);
    parent->addLink(newNode, text[newNode->getLabelBegin()]);

    newNode->addLink(finishNode, text[finishNode->getLabelBegin()]);
    return newNode;
}

long long int SuffixTree::countSubstrings() const {
    return root->countSubstrings() - 1;
}

SuffixTree::~SuffixTree() {
    delete root;
    // Из blank идут несколько ребер в одну уже удаленную вершину.
    // Очищаем список его детей, что бы не удалять их.
    blank->clearLinks();
    delete blank;
}

