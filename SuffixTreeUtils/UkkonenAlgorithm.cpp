#include <assert.h>
#include <iostream>
#include "UkkonenAlgorithm.h"

SuffixTree UkkonenAlgorithm::buildSuffixTree(const std::string &text) {
    SuffixTree suffixTree(text);
    Position activePoint = suffixTree.getRoot()->getPosition();
    for (size_t i = 0; i < text.length(); ++i) {
        activePoint = updateTree(suffixTree, i, activePoint);
    }
    return suffixTree;
}

// Добавляет новый символ в дерево, соответственно алгоритму.
// Возвращает новый Active Point.
Position UkkonenAlgorithm::updateTree(SuffixTree &tree, size_t index, const Position &activePoint) {
    const std::string &text = tree.getText();
    char letter = text[index];
    SuffixTreeNode *currentNode = nullptr;
    auto currentPosition = activePoint;
    // Пока нет ребра но текущему символу, добавляем и переходим по суффиксным ссылкам.
    while (!tree.canGo(currentPosition, letter)) {
        currentNode = tree.makeExplicit(currentPosition);
        currentPosition = currentNode->getPosition();
        // Подвешиваем новую вершину-букву.
        SuffixTreeNode *newChild = new SuffixTreeNode(currentNode, index, text.length());
        currentNode->addLink(newChild, letter);
        assert(currentNode->canGo(letter));
        // Проходим по неявной суффиксной ссылке.
        currentPosition = findSuffixLink(tree, currentPosition);
        SuffixTreeNode *explicitSuffixLink = tree.makeExplicit(currentPosition);
        currentPosition = explicitSuffixLink->getPosition();
        // Устанавливаем найденую суффиксную ссылку.
        if (currentNode->getSuffixLink() == nullptr) {
            currentNode->setSuffixLink(explicitSuffixLink);
        }
    }
    try {
        currentPosition = tree.go(currentPosition, letter);
    } catch (std::logic_error &error) {
        assert(false);
    }
    return currentPosition;
}

Position UkkonenAlgorithm::findSuffixLink(SuffixTree &tree, const Position &position) {
    // Если суффиксная ссылка уже известна, то просто вернем ее.
    if (position.isExplicit() && (position.finish->getSuffixLink() != nullptr)) {
        return position.finish->getSuffixLink()->getPosition();
    }
    // Находим ближайшего явного предка.
    SuffixTreeNode *parent = position.finish->getParent();

    // Запоминаем, по какой строке придется спускаться после перехода.
    const std::string &text = tree.getText();
    auto stringBegin = text.begin() + position.finish->getLabelBegin();
    auto stringEnd = text.begin()
                     + position.finish->getLabelEnd()
                     - position.distanceToFinish;

    // Осуществляем переход по суффиксной ссылке.
    assert(parent->getSuffixLink() != nullptr);
    SuffixTreeNode *currentNode = parent->getSuffixLink();

    // Спускаемся на соответствующую подстроку вниз.
    auto iterator = stringBegin;
    while (iterator != stringEnd) {
        size_t length = stringEnd - iterator;
        Position newPosition;
        // Пытаемся найти ребро соответсвующее текущему символу.
        try {
            newPosition = currentNode->go(*iterator);
        } catch (std::logic_error &error) {
            assert(false);
        }
        size_t edgeLength = newPosition.distanceToFinish + 1;
        if (length == edgeLength) {
            return newPosition.finish->getPosition();
        } else {
            if (length > edgeLength) {
                // Продвигаемся по нужному ребру на его длину.
                iterator += edgeLength;
                currentNode = newPosition.finish;
            } else {
                // Попадаем на неявную вершину на ребре.
                Position finalPosition = newPosition;
                // -1 т.к. newPosition это уже со смещением на 1 символ по ребру.
                finalPosition.distanceToFinish -= length - 1;
                return finalPosition;
            }
        }
    }
    assert(false);
}
