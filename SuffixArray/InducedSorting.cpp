#include "InducedSorting.h"

std::vector<size_t> InducedSorting::buildSuffixArray(const std::string inputText) {
    std::string text = inputText + "$";
    std::vector<size_t> suffixArray(text.length());
    // Определить типы суффиксов.
    std::vector<Types> types = classify(text);
    // Найти все индексы LMS-подстрок.
    std::vector<size_t> LMSIndices = getLMSIndices(types);
    // Разбить по корзинам.
    // Получить имена всех LMS-подстрок, а по ним сжатую строку.
    // Если в сжатой строке все символы различны:
    // то напрямую посчитать суффиксный массив для нее.
    // иначе, рекурсивное построение суффиксного массива для сжатой строки.
    // Построить суффиксный массив для строки по массиву для сжатой.
    return suffixArray;
}

std::vector<InducedSorting::Types> InducedSorting::classify(const std::string text) const {
    std::vector<Types> types(text.length());
    types[text.length() - 1] = S_TYPE;
    for (size_t i = text.length() - 2; i >= 0; --i) {
        if (text[i] > text[i + 1] || (text[i] == text[i + 1] && types[i + 1] == L_TYPE)) {
            types[i] = L_TYPE;
        }
        if (text[i] < text[i + 1] || (text[i] == text[i + 1] && types[i + 1] == S_TYPE)) {
            types[i] = S_TYPE;
        }
    }
    return types;
}

std::vector<size_t> InducedSorting::getLMSIndices(const std::vector<Types> &types) const {
    std::vector<size_t> indices;
    for (size_t i = 0; i < types.size(); ++i) {
        if (types[i] == S_TYPE && (types[i - 1] == L_TYPE || i == 0)) {
            indices.push_back(i);
        }
    }
    return indices;
}

std::vector<InducedSorting::Bucket> InducedSorting::separateIntoBuckets() {
    std::vector<Bucket> buckets(0xFF);
    return std::vector<Bucket>();
}

std::vector<size_t> InducedSorting::induceSuffixArray(const std::vector<size_t> &reducedSuffixArray) {
//    std::vector<size_t> inducedSuffixArray();
//    std::vector<char> bucketsStart;
//    std::vector<char> bucketsCurrent;
}

std::vector<size_t> InducedSorting::inducedSorting(const std::vector<size_t> &LMSIndices) {
    std::vector<size_t> answer;
    // Находим разбиение на корзины.
    std::vector<Bucket> buckets = separateIntoBuckets();
    // Шаг 1. Поместим все LMS-подстроки в соответствии с их первой буквой.
    for (size_t i = 0; i < LMSIndices.size(); ++i) {

    }
}
