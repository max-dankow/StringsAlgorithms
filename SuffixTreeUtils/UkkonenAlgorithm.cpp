#include <assert.h>
#include <iostream>
#include "UkkonenAlgorithm.h"

SuffixTree UkkonenAlgorithm::buildSuffixTree(const std::string &text) {
    SuffixTree suffixTree(text);
    Position activePoint = suffixTree.getRoot()->getPosition();
    for (size_t i = 0; i < text.length(); ++i) {
        activePoint = updateTree(suffixTree, i, activePoint);
//        suffixTree.printTree(std::cout);
    }
    return suffixTree;
}

// Добавляет новый символ в дерево, соттветствунно алгоритму.
// Возвращает новый Active Point.
Position UkkonenAlgorithm::updateTree(SuffixTree &tree, size_t index, Position activePoint) {
//    // Мы в явной вершине.
//    assert(activePoint.distanceToFinish == 0);
    char letter = tree.text[index];
    SuffixTreeNode *currentNode = activePoint.finish;// todo: = nullptr.
    // Пока нет ребра но текущему символу, добавляем и переходим по суффиксным ссылкам.
    while (!tree.canGo(activePoint, letter)) {
        currentNode = tree.testAndSplit(activePoint);
        activePoint = currentNode->getPosition();
        // Подвешиваем новую вершину-букву.
        SuffixTreeNode *newChild = new SuffixTreeNode(currentNode, index, tree.text.length());
        currentNode->addLink(newChild, letter);
        assert(currentNode->canGo(letter));
        // Проходим по неявной суффиксной ссылке.
        activePoint = findSuffixLink(tree, activePoint);
        SuffixTreeNode *explicitSuffixLink = tree.testAndSplit(activePoint);
        activePoint = explicitSuffixLink->getPosition();
        // Устанавливаем найденую суффиксную ссылку.
        if (currentNode->getSuffixLink() == nullptr) {
            currentNode->setSuffixLink(explicitSuffixLink);
        }
//        tree.printTree(std::cerr);
    }
    try {
        activePoint = tree.go(activePoint, letter);
    } catch (std::logic_error &error) {
        assert(false);
    }
    return activePoint;
}

Position UkkonenAlgorithm::findSuffixLink(SuffixTree &tree, Position position) {
    // Если суффиксная ссылка уже известна, то просто вернем ее.
    if (position.isExplicit() && (position.finish->getSuffixLink() != nullptr)) {
//        parent = position.finish;
        return position.finish->getSuffixLink()->getPosition();
    }
    // Находим ближайшего явного предка.
    SuffixTreeNode *parent = position.finish->getParent();
    // Запоминаем, по какой строке придется спускаться после перехода.
    auto stringBegin = tree.text.begin() + position.finish->getLabelBegin();
    auto stringEnd = tree.text.begin()
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
}
