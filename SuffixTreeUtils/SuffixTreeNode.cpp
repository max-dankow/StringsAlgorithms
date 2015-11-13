#include "SuffixTreeNode.h"

NodeIndex SuffixTreeNode::getSuffixLink() const {
    return suffixLink;
}

void SuffixTreeNode::setSuffixLink(NodeIndex suffixLink) {
    SuffixTreeNode::suffixLink = suffixLink;
}

size_t SuffixTreeNode::getLabelStart() const {
    return labelStart;
}

void SuffixTreeNode::setLabelStart(size_t labelStart) {
    SuffixTreeNode::labelStart = labelStart;
}

size_t SuffixTreeNode::getLabelLength() const {
    return labelLength;
}

void SuffixTreeNode::setLabelLength(size_t labelLength) {
    SuffixTreeNode::labelLength = labelLength;
}