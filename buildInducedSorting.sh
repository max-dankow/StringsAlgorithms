#!/bin/bash
cat SuffixArray/InducedSorting.h SuffixArray/InducedSorting.cpp main.cpp | sed '/#include "*"/d' > toSendIS.cpp