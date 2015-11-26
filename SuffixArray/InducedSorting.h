#ifndef STRINGUTILS_INDUCEDSORTING_H
#define STRINGUTILS_INDUCEDSORTING_H


#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>

// Реализует алгоритм построения суффиксного массива за линейное время Induced Sorting.
// Используется внутреннее предсталвение строки в виде вектора чисел, т.к. при переходе
// индукции, алфавит может значительно увеличиться.
// Все данные передаются, а не хранятся в классе, в силу того, что алгоритм рекурсивен.
class InducedSorting {
public:
    static std::vector<size_t> buildSuffixArray(const std::string text);

    struct LMS {
        LMS(size_t begin, size_t end, size_t index) :
                begin(begin), end(end), index(index) { }

        size_t begin, end, index;
    };

    enum Types {
        L_TYPE,
        S_TYPE
    };
private:
    // Представляет непрерывный блок суффиксов, начинающийся с одной буквы.
    // L-подблок: [begin, sTypeBegin) S-подблок: [sTypeBegin, end).
    // position - текущая позиция, в которую будет проводиться вставка.
    struct Bucket {
        size_t begin, end, position, sTypeBegin;
    };

    // Реализует алгоритм построения суффиксного массива Induced Sorting.
    static std::vector<size_t> SuffixArrayInducedSorting(const std::vector<long long> &text);

    // Определяет типы суффиксов - S или L.
    static std::vector<Types> classify(const std::vector<long long> &text);

    static std::vector<LMS> getLMSList(const std::vector<Types> &types);

    static std::vector<Bucket> separateIntoBuckets(const std::vector<long long> &text,
                                                   const std::vector<Types> &types);

    static std::vector<size_t> induceSuffixArray(const std::vector<long long> &text,
                                                 const std::vector<LMS> &LMSIndices,
                                                 const std::vector<Types> &types);

    static void printBuckets(const std::vector<Bucket> &buckets,
                             const std::vector<ssize_t> &sa,
                             std::ostream &output);

    static std::vector<LMS> sortLMSList(const std::vector<LMS> &LMSIndices,
                                        const std::vector<long long> &text,
                                        const std::vector<Types> types);

    static bool getNames(const std::vector<LMS> &lmsSorted,
                         const std::vector<long long> &text,
                         const std::vector<Types> &types,
                         std::vector<long long> &names);

    static std::vector<long long> convertToLongVector(const std::string &text);
};


#endif //STRINGUTILS_INDUCEDSORTING_H
