#include "SuffixTreeNode.h"

NodeIndex SuffixTreeNode::getSuffixLink() const {
    return suffixLink;
}

void SuffixTreeNode::setSuffixLink(NodeIndex suffixLink) {
    SuffixTreeNode::suffixLink = suffixLink;
}

size_t SuffixTreeNode::getStart() const {
    return start;
}

void SuffixTreeNode::setStart(size_t start) {
    SuffixTreeNode::start = start;
}

size_t SuffixTreeNode::getEnd() const {
    return end;
}

void SuffixTreeNode::setEnd(size_t end) {
    SuffixTreeNode::end = end;
}