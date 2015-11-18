#include "SuffixTree.h"

void SuffixTreeNode::addLink(SuffixTreeNode *node, char c) {
    size_t distance = node->getLabelEnd() - node->getLabelBegin();
    links.insert(std::make_pair(c, Position(node, distance - 1)));
}

void SuffixTreeNode::setLabelBegin(size_t labelBegin) {
    SuffixTreeNode::labelBegin = labelBegin;
}

size_t SuffixTreeNode::getLabelBegin() const {
    return labelBegin;
}

void SuffixTreeNode::setLabelEnd(size_t labelEnd) {
    SuffixTreeNode::labelEnd = labelEnd;
}

size_t SuffixTreeNode::getLabelEnd() const {
    return labelEnd;
}

SuffixTreeNode * SuffixTreeNode::getParent() const {
    return parent;
}

void SuffixTreeNode::setParent(SuffixTreeNode *parent) {
    this->parent = parent;
}

bool SuffixTreeNode::canGo(char letter) {
//    auto l = links;
//    auto search = links.find(letter);
//    std::cerr << search->first << '\n';
    return links.find(letter) != links.end();
}

void SuffixTreeNode::setSuffixLink(SuffixTreeNode *suffixLink) {
    SuffixTreeNode::suffixLink = suffixLink;
}

SuffixTreeNode * SuffixTreeNode::getSuffixLink() const {
    return suffixLink;
}

Position SuffixTreeNode::getPosition() {
    return Position(this, 0);
}

Position SuffixTreeNode::go(char letter) {
    if (!canGo(letter)) {
        throw std::logic_error("No such link.");
    }
    else {
        return links.find(letter)->second;
    }
}

Position::Position() {
    finish = nullptr;
    distanceToFinish = 0;
}

bool Position::isExplicit() {
    return distanceToFinish == 0;
}

void SuffixTreeNode::printNode(std::ostream &output, const std::string &text, size_t offset) {
    for (size_t i = 0; i < offset; ++i) {
        output << '|';
    }
    for (size_t i = labelBegin; i < std::min(labelEnd, text.length()); ++i) {
        output << text[i];
    }
    output << "\n";
    for (auto pair : links) {
        pair.second.finish->printNode(output, text, offset + 1);
    }
}

long long SuffixTreeNode::countSubstrings() {
    long long sum = getEdgeLength();
    for (auto pair : links) {
        sum += pair.second.finish->countSubstrings();
    }
    return sum;
}

long long int SuffixTreeNode::getEdgeLength() {
    return (long long int) (getLabelEnd() - getLabelBegin());
}

SuffixTreeNode::~SuffixTreeNode() {
    for (auto pair : links) {
        // Рекурсивно удаляем потомков.
        if (pair.second.finish != nullptr) {
            delete pair.second.finish;
        }
        pair.second.finish = nullptr;
    }
}
