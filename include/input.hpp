#pragma once

#include "multiset.hpp"

#include <cstddef>
#include <string>
#include <vector>

int readInt(const std::string &prompt, int minValue, int maxValue);
MultiSet readManualMultiset(const std::string &name, const MultiSet &universe,
                            const std::vector<std::string> &order, std::size_t power);

MultiSet generateAutomaticMultiset(const MultiSet &universe, std::size_t power);

void printUniverse(const MultiSet &universe, const std::vector<std::string> &order);

void printMultiset(const std::string &name, const MultiSet &set);
