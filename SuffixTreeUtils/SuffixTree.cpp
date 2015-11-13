#include "SuffixTree.h"

SuffixTree::SuffixTree() {
    // Т.к. root.parent будет ссылаться на newDummy, то он не удалится при завершении функции.
    std::shared_ptr<SuffixTreeNode> newDummy(new SuffixTreeNode(nullptr, 0, 0));
    root.reset(new SuffixTreeNode(newDummy, 0, 0));
}