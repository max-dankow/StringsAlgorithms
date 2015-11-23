#!/bin/bash
cat SuffixArray/InducedSorting.h SuffixArray/SuffixArrayUtils.h SuffixArray/InducedSorting.cpp SuffixArray/SuffixArrayUtils.cpp main.cpp | sed '/#include "*"/d' > toSendIS.cpp