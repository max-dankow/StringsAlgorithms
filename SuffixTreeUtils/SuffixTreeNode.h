#ifndef STRINGSEARCHING_SUFFIXTREENODE_H
#define STRINGSEARCHING_SUFFIXTREENODE_H

#include "SuffixTree.h"
#include <vector>
#include <map>
#include <stdlib.h>

typedef std::ptrdiff_t NodeIndex;

class SuffixTreeNode {
public:
    static const NodeIndex NO_LINK = -1;

    NodeIndex getSuffixLink() const;

    void setSuffixLink(NodeIndex suffixLink);

    // Метка ребра представлена индексом начала и конца
    // соответсующей подстроки в исходном тексте.


    size_t getLabelStart() const;

    void setLabelStart(size_t labelStart);

    size_t getLabelLength() const;

    void setLabelLength(size_t labelLength);

private:
    NodeIndex suffixLink;
    NodeIndex parentNode;
//    std::vector<NodeIndex> links;
    std::map<char, NodeIndex> links;
    // Метка ребра - индексы начала и конца подстроки.
    size_t labelStart, labelLength;
private:

};


#endif //STRINGSEARCHING_SUFFIXTREENODE_H
