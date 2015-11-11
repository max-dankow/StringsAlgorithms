#ifndef STRINGSEARCHING_SUFFIXTREENODE_H
#define STRINGSEARCHING_SUFFIXTREENODE_H

#include "SuffixTree.h"
#include <vector>
//#include <stdlib.h>

class SuffixTreeNode {
public:
    static const NodeIndex NO_LINK = -1;

    NodeIndex getSuffixLink() const;

    void setSuffixLink(NodeIndex suffixLink);

    // Метка ребра представлена индексом начала и конца
    // соответсующей подстроки в исходном тексте.
    size_t getStart() const;

    void setStart(size_t start);

    size_t getEnd() const;

    void setEnd(size_t end);

private:
    NodeIndex suffixLink;
    std::vector<NodeIndex> links;
//    std::map<std::string, SuffixTree::NodeIndex> links;
    // Метка ребра - индексы начала и конца подстроки.
    size_t start, end;
private:

};


#endif //STRINGSEARCHING_SUFFIXTREENODE_H
