#include "SuffixTree.h"

void SuffixTreeNode::addLink(std::shared_ptr<SuffixTreeNode> &node, char c) {
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

const std::shared_ptr<SuffixTreeNode> &SuffixTreeNode::getParent() const {
    return parent;
}

void SuffixTreeNode::setParent(const std::shared_ptr<SuffixTreeNode> &parent) {
    SuffixTreeNode::parent = parent;
}

bool SuffixTreeNode::canGo(char letter) {
    return links.find(letter) != links.end();
}

void SuffixTreeNode::setSuffixLink(const std::shared_ptr<SuffixTreeNode> &suffixLink) {
    SuffixTreeNode::suffixLink = suffixLink;
}

const std::shared_ptr<SuffixTreeNode> &SuffixTreeNode::getSuffixLink() const {
    return suffixLink;
}

Position SuffixTreeNode::getPosition() {
    return Position(std::shared_ptr<SuffixTreeNode>(this), 0);
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