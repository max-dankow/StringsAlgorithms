#!/bin/bash
cat SuffixTreeUtils/SuffixTreeNode.h SuffixTreeUtils/SuffixTree.h SuffixTreeUtils/UkkonenAlgorithm.h SuffixTreeUtils/SuffixTree.cpp SuffixTreeUtils/SuffixTreeNode.cpp SuffixTreeUtils/UkkonenAlgorithm.cpp main.cpp | sed '/#include "*"/d' > toSendUkkonen.cpp