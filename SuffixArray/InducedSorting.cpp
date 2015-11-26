#include "InducedSorting.h"
#include <limits>

std::vector<size_t> InducedSorting::buildSuffixArray(const std::string text) {
    std::vector<long long> buffer = convertToLongVector(text);
    // Добавляем "символ разделитель", аналог $.
    buffer.push_back(0);
    std::vector<size_t> suffarray = SuffixArrayInducedSorting(buffer);
    // Удаляем элемент соответствующий разделителю.
    suffarray.erase(suffarray.begin());
    return suffarray;
}

std::vector<size_t> InducedSorting::SuffixArrayInducedSorting(const std::vector<long long> &text) {
    // Определить типы суффиксов.
    std::vector<Types> types = classify(text);
    // Найти все LMS-подстроки.
    std::vector<LMS> LMSList = getLMSList(types);
    // Отсортировать LMS-подстроки и сопоставить имена.
    std::vector<LMS> sortedLMS = sortLMSList(LMSList, text, types);
    // Построить сжатую строку.
    std::vector<long long> names;
    bool areNamesUnique = getNames(sortedLMS, text, types, names);
    std::vector<long long> trueNames(names.size(), 0);
    for (size_t i = 0; i < sortedLMS.size(); ++i) {
        trueNames[sortedLMS[i].index] = names[i];
    }
    std::vector<size_t> reducedSuffixArray;
    // Если в сжатой строке все символы различны:
    if (areNamesUnique) {
        // то напрямую посчитать суффиксный массив для нее.
        reducedSuffixArray.resize(trueNames.size() + 1);
        for (size_t i = 0; i < names.size(); ++i) {
            reducedSuffixArray[i + 1] = sortedLMS[i].index;
        }
    } else {
        // иначе, рекурсивное построение суффиксного массива для сжатой строки.
        trueNames.push_back(0);
        reducedSuffixArray = SuffixArrayInducedSorting(trueNames);
    }
    // Построить суффиксный массив для строки по массиву для сжатой.
    std::vector<LMS> inducedLMS;
    for (size_t i = 1; i < reducedSuffixArray.size(); ++i) {
        inducedLMS.push_back(LMSList[reducedSuffixArray[i]]);
    }
    return induceSuffixArray(text, inducedLMS, types);
}

std::vector<InducedSorting::Types> InducedSorting::classify(const std::vector<long long int> &text) {
    std::vector<Types> types(text.size());
    types[text.size() - 1] = S_TYPE;
    for (ssize_t i = text.size() - 2; i >= 0; --i) {
        if (text[i] > text[i + 1] || (text[i] == text[i + 1] && types[i + 1] == L_TYPE)) {
            types[i] = L_TYPE;
        } else {
            types[i] = S_TYPE;
        }
    }
    return types;
}

std::vector<InducedSorting::LMS> InducedSorting::getLMSList(const std::vector<Types> &types) {
    std::vector<LMS> LMSList;
    ssize_t previous = -1;
    size_t count = 0;
    for (size_t i = 1; i < types.size(); ++i) {
        if (types[i] == S_TYPE && (types[i - 1] == L_TYPE)) {
            if (previous != -1) {
                LMSList.push_back(LMS((size_t) previous, i + 1, count));
                count++;
            }
            previous = i;
        }
    }
    // Последний эелемент всегда разделитель и по определению LMS-подстрока.
    LMSList.push_back(LMS(types.size() - 1, types.size(), count));
    return LMSList;
}

std::vector<InducedSorting::Bucket> InducedSorting::separateIntoBuckets(const std::vector<long long> &text,
                                                                        const std::vector<Types> &types) {
    size_t size = std::max(text.size(), (size_t) 256);
    std::vector<size_t> letters(size, 0);
    std::vector<size_t> lTypeLetters(size, 0);
    std::vector<Bucket> buckets(size);
    for (size_t i = 0; i < text.size(); ++i) {
        ++letters[text[i]];
        if (types[i] == L_TYPE) {
            ++lTypeLetters[text[i]];
        }
    }
    size_t position = 0;
    for (long long c = 0; c < buckets.size(); ++c) {
        buckets[c].begin = position;
        buckets[c].position = position;
        buckets[c].sTypeBegin = buckets[c].begin + lTypeLetters[c];
        position += letters[c];
        buckets[c].end = position;
    }
    return buckets;
}

std::vector<size_t> InducedSorting::induceSuffixArray(const std::vector<long long> &text,
                                                      const std::vector<LMS> &LMSIndices,
                                                      const std::vector<Types> &types) {
    std::vector<ssize_t> SuffixArray(text.size(), -1);
    // Находим разбиение на корзины.
    std::vector<Bucket> buckets = separateIntoBuckets(text, types);
    for (auto it = buckets.begin(); it != buckets.end(); ++it) {
        it->position = it->sTypeBegin;
    }
    // Шаг 1. Поместим все LMS-подстроки в нужном порядке.
    for (size_t i = 0; i < LMSIndices.size(); ++i) {
        long long letter = text[LMSIndices[i].begin];
        SuffixArray[buckets[letter].position] = LMSIndices[i].begin;
        ++buckets[letter].position;
    }
    // Шаг 2. Разместим все L-type LMS-префиксы.
    for (auto it = buckets.begin(); it != buckets.end(); ++it) {
        it->position = it->begin;
    }
    for (size_t i = 0; i < SuffixArray.size(); ++i) {
        if (SuffixArray[i] > 0) {
            long long letter = text[SuffixArray[i] - 1];
            if (types[SuffixArray[i] - 1] == L_TYPE) {
                SuffixArray[buckets[letter].position] = SuffixArray[i] - 1;
                ++buckets[letter].position;
            }
        }
    }
    // Шаг 3. Обратный проход для S-type.
    for (auto it = buckets.begin(); it != buckets.end(); ++it) {
        it->position = it->end - 1;
    }
    for (ssize_t i = SuffixArray.size() - 1; i >= 0; --i) {
        if (SuffixArray[i] > 0) {
            long long letter = text[SuffixArray[i] - 1];
            if (types[SuffixArray[i] - 1] == S_TYPE) {
                SuffixArray[buckets[letter].position] = SuffixArray[i] - 1;
                --buckets[letter].position;
            }
        }
    }

    std::vector<size_t> sortedLMSList(SuffixArray.size());
    for (size_t i = 0; i < SuffixArray.size(); ++i) {
        sortedLMSList[i] = (unsigned long) SuffixArray[i];
    }
    return sortedLMSList;
}

std::vector<InducedSorting::LMS> InducedSorting::sortLMSList(const std::vector<InducedSorting::LMS> &LMSIndices,
                                                             const std::vector<long long> &text,
                                                             const std::vector<Types> types) {
    std::vector<ssize_t> sa(text.size(), -1);
    std::vector<LMS> lms(text.size(), LMS(0, 0, 0));
    std::vector<LMS> lmsSorted(lms);
    for (size_t i = 0; i < LMSIndices.size(); ++i) {
        lms[LMSIndices[i].begin] = LMSIndices[i];
    }
    // Находим разбиение на корзины.
    std::vector<Bucket> buckets = separateIntoBuckets(text, types);
//    printBuckets(buckets, sa, std::cerr);
    for (auto it = buckets.begin(); it != buckets.end(); ++it) {
        it->position = it->end - 1;
    }
    // Шаг 1. Поместим все LMS-подстроки в нужном порядке.
    for (size_t i = 0; i < LMSIndices.size(); ++i) {
        long long letter = text[LMSIndices[i].begin];
        sa[buckets[letter].position] = LMSIndices[i].begin;
        lmsSorted[buckets[letter].position] = LMSIndices[i];
        --buckets[letter].position;
    }
    // Шаг 2. Разместим все L-type LMS-префиксы.
    for (auto it = buckets.begin(); it != buckets.end(); ++it) {
        it->position = it->begin;
    }
    for (size_t i = 0; i < sa.size(); ++i) {
        if (sa[i] > 0) {
            long long letter = text[sa[i] - 1];
            if (types[sa[i] - 1] == L_TYPE) {
                sa[buckets[letter].position] = sa[i] - 1;
                lmsSorted[buckets[letter].position] = lms[sa[i] - 1];
                ++buckets[letter].position;
            }
        }
    }
    // Шаг 3. Обратный проход.
    for (auto it = buckets.begin(); it != buckets.end(); ++it) {
        it->position = it->end - 1;
    }
    for (ssize_t i = sa.size() - 1; i >= 0; --i) {
        if (sa[i] > 0) {
            long long letter = text[sa[i] - 1];
            if (types[sa[i] - 1] == S_TYPE) {
                sa[buckets[letter].position] = sa[i] - 1;
                lmsSorted[buckets[letter].position] = lms[sa[i] - 1];
                --buckets[letter].position;
            }
        }
    }

    std::vector<LMS> answer;
    for (size_t i = 0; i < lmsSorted.size(); ++i) {
        if (lmsSorted[i].end - lmsSorted[i].begin > 0) {
            answer.push_back(lmsSorted[i]);
        }
    }
    return answer;
}

bool areLMSEqual(const InducedSorting::LMS &left,
                 const InducedSorting::LMS &right,
                 const std::vector<long long> &text,
                 const std::vector<InducedSorting::Types> &types) {
    if (left.end - left.begin != right.end - right.begin) {
        return false;
    }
    for (size_t i = 0; i < left.end - left.begin; ++i) {
        if (text[left.begin + i] != text[right.begin + i]
            || types[left.begin + i] != types[right.begin + i]) {
            return false;
        }
    }
    return true;
}

bool InducedSorting::getNames(const std::vector<InducedSorting::LMS> &lmsSorted,
                              const std::vector<long long> &text,
                              const std::vector<InducedSorting::Types> &types,
                              std::vector<long long> &names) {
    long long name = 1;
    names.assign(lmsSorted.size(), 0);
    bool allUnique = true;
    for (size_t i = 0; i < lmsSorted.size(); ++i) {
        if (i != 0) {
            if (!areLMSEqual(lmsSorted[i], lmsSorted[i - 1], text, types)) {
                name++;
            } else {
                allUnique = false;
            }
        }
        names[i] = name;
    }
    return allUnique;
}

std::vector<long long> InducedSorting::convertToLongVector(const std::string &text) {
    std::vector<long long> converted(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        converted[i] = (long long) text[i];
    }
    return converted;
}

void InducedSorting::printBuckets(const std::vector<Bucket> &buckets,
                                  const std::vector<ssize_t> &sa,
                                  std::ostream &output) {
    for (long long c = 0; c < buckets.size(); ++c) {
        if (buckets[c].end - buckets[c].begin > 0) {
            output << c << ": ";
            for (size_t i = buckets[c].begin; i < buckets[c].end; ++i) {
                output << sa[i] << ' ';
            }
        }
    }
    output << '\n';
}