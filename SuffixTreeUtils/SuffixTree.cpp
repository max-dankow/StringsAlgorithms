#include <assert.h>
#include "SuffixTree.h"

SuffixTree::SuffixTree(std::string text) : text(text) {
    // Создаем фиктивную вершину для унификации операций.
    // Т.к. root.parent будет ссылаться на newBlank, то он не удалится при завершении функции.
    std::shared_ptr<SuffixTreeNode> newBlank(new SuffixTreeNode(nullptr, 0, 0));
    root.reset(new SuffixTreeNode(newBlank, 0, 0));
    // Из фиктивной вершины в root ведут ребра со всеми символами алфавита.
    // todo: сделать более универсальное задание алфавита.
    for (char c = 'a'; c < 'z'; ++c) {
        newBlank->addLink(root, c);
    }
}

const std::shared_ptr<SuffixTreeNode> &SuffixTree::getRoot() const {
    return root;
}

//Position SuffixTree::go(Position from, char letter) {
//    Position destination(from.finish, from.distanceToFinish);
//    // Пробуем продвигаться дальше по ребру.
//    if (from.distanceToFinish > 0) {
//        char nextLetter = 0;
//        assert(tryGetNextLetter(from, nextLetter));
//        if (nextLetter == letter) {
//            destination.distanceToFinish--;
//            return destination;
//        } else {
//            // Создать вершину и перейти.
//        }
//    } else {
//        // Иначе пытаемся пройти по нужному ребру из явной вершины.
//        auto edgeToGo = from.finish->links.find(letter);
//        if (edgeToGo != from.finish->links.end()) {
//            return edgeToGo->second;
//        } else {
//            // Создать вершину и перейти.
//        }
//    }
////    return Position(std::shared_ptr<SuffixTreeNode>(), 0);
//}

bool SuffixTree::tryGetNextLetter(Position position, char nextLetter) {
    if (position.distanceToFinish == 0) {
    }
    size_t index = position.finish->getLabelEnd() - position.distanceToFinish;
    assert(index >= 0 && index < text.length());
    return text[index];
}
