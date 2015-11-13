#include "UkkonenAlgorithm.h"

SuffixTree UkkonenAlgorithm::buildSuffixTree(const std::string &text) {
    SuffixTree suffixTree;
    for (size_t i = 0; i < text.length(); ++i) {
        updateTree(suffixTree, text[i]);
    }
    return SuffixTree();
}

void UkkonenAlgorithm::updateTree(SuffixTree &tree, char c) {

}
