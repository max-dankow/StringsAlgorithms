#include <assert.h>
#include <iostream>
#include "UkkonenAlgorithm.h"

SuffixTree UkkonenAlgorithm::buildSuffixTree(const std::string &text) {
    SuffixTree suffixTree(text);
    Position activePoint = suffixTree.getRoot()->getPosition();
    for (size_t i = 0; i < text.length(); ++i) {
        updateTree(suffixTree, i, activePoint);
    }
    return suffixTree;
}

// Добавляет новый символ в дерево, соттветствунно алгоритму.
// Возвращает новый Active Point.
Position UkkonenAlgorithm::updateTree(SuffixTree &tree, size_t index, Position activePoint) {
    // Мы в явной вершине.
    assert(activePoint.distanceToFinish == 0);
    char letter = tree.text[index];
    // Пока нет ребра но текущему символу, добавляем и переходим по суффиксным ссылкам.
    while (!activePoint.finish->canGo(letter)) {
        std::shared_ptr<SuffixTreeNode> currentNode = testAndSplit(activePoint, index);
        std::shared_ptr<SuffixTreeNode> newChild(new SuffixTreeNode(currentNode, index, INFINITY));
        currentNode->addLink(newChild, letter);
        // Проходим по неявной суффиксной ссылке.
        activePoint = findSuffixLink(tree, activePoint);
        // Обновляем суффиксную ссылку для предыдущего суффикса.
        currentNode->setSuffixLink(activePoint.finish);
    }
}

Position UkkonenAlgorithm::findSuffixLink(SuffixTree &tree,
                                          Position position) {
    // Находим ближайшего явного предка.
    std::shared_ptr<SuffixTreeNode> parent = position.finish->getParent();
    // Запоминаем, по какой строке придется спускаться после перехода.
    auto stringBegin = tree.text.begin() + position.finish->getLabelBegin();
    auto stringEnd = tree.text.begin()
                     + position.finish->getLabelEnd()
                     - position.distanceToFinish;

    std::string debug(stringBegin, stringEnd);
    std::cerr << debug;

    // Осуществляем переход по суффиксной ссылке.
//    position = parent->getSuffixLink()->getPosition();
    std::shared_ptr<SuffixTreeNode> currentNode = parent->getSuffixLink();
    // Спускаемся на соответствующую подстроку вниз.
    auto iterator = stringBegin;
    while (iterator != stringEnd) {
        size_t length = stringEnd - iterator;
        Position newPosition;
        // Пытаемся найти ребро соответсвующее текущему символу.
        try {
            newPosition = currentNode->go(*iterator);
        } catch (std::logic_error &error) {
            assert(true);
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

std::shared_ptr<SuffixTreeNode> UkkonenAlgorithm::testAndSplit(Position position, size_t index) {
    std::shared_ptr<SuffixTreeNode> finishNode = position.finish;
    if (position.isExplicit()) {
        return finishNode;
    }
    std::shared_ptr<SuffixTreeNode> parent = finishNode->getParent();
    std::shared_ptr<SuffixTreeNode> newNode(
            new SuffixTreeNode(parent, finishNode->getLabelBegin(), index + 1));
    finishNode->setLabelBegin(index);
    finishNode->setParent(newNode);
    return newNode;
}
