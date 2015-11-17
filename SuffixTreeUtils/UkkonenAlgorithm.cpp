#include <assert.h>
#include <iostream>
#include "UkkonenAlgorithm.h"

SuffixTree UkkonenAlgorithm::buildSuffixTree(const std::string &text) {
    SuffixTree suffixTree(text);
    Position activePoint = suffixTree.getRoot()->getPosition();
    for (size_t i = 0; i < text.length(); ++i) {
        updateTree(suffixTree, i, activePoint);
//        suffixTree.printTree(std::cout);
    }
    return suffixTree;
}

// Добавляет новый символ в дерево, соттветствунно алгоритму.
// Возвращает новый Active Point.
Position UkkonenAlgorithm::updateTree(SuffixTree &tree, size_t index, Position activePoint) {
    // Мы в явной вершине.
    assert(activePoint.distanceToFinish == 0);
    char letter = tree.text[index];
    SuffixTreeNode *lastNode = activePoint.finish;
    // Пока нет ребра но текущему символу, добавляем и переходим по суффиксным ссылкам.
    while (!activePoint.finish->canGo(letter)) {
//        auto l = activePoint.finish->links;
//        auto l2 = tree.blank->links;
//        std::cout << "fuck you\n";
//        assert(activePoint.finish != tree.blank);
        SuffixTreeNode *currentNode = testAndSplit(activePoint, index);
        // Подвешиваем новую вершину-букву.
        SuffixTreeNode *newChild(new SuffixTreeNode(currentNode, index, INFINITY_));
        currentNode->addLink(newChild, letter);
        lastNode = currentNode;
        assert(currentNode->canGo(letter));
        // Проходим по неявной суффиксной ссылке.
        activePoint = findSuffixLink(tree, activePoint);
        // Устанавливаем найденую суффиксную ссылку.
        if (currentNode->getSuffixLink() == nullptr) {
            currentNode->setSuffixLink(activePoint.finish);
        }
    }
    try {
        activePoint = lastNode->go(letter);
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
                Position finalPosition = position;
                finalPosition.distanceToFinish -= length - 1;
                return finalPosition;
            }
        }
    }
}

SuffixTreeNode *UkkonenAlgorithm::testAndSplit(Position position, size_t index) {
    SuffixTreeNode *finishNode = position.finish;
    if (position.isExplicit()) {
        return finishNode;
    }
    SuffixTreeNode *parent = finishNode->getParent();
    SuffixTreeNode *newNode(
            new SuffixTreeNode(parent, finishNode->getLabelBegin(), index + 1));
    finishNode->setLabelBegin(index);
    finishNode->setParent(newNode);
    return newNode;
}
