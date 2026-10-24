#include "input.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>

int readInt(const std::string &prompt, int minValue, int maxValue)
{
    while (true)
    {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        long long value;
        char extra;
        if ((ss >> value) && !(ss >> extra) && value >= minValue && value <= maxValue)
            return static_cast<int>(value);
        std::cout << "Ошибка: введите целое число от " << minValue << " до " << maxValue << ".\n";
    }
}

MultiSet readManualMultiset(const std::string &name, const MultiSet &universe,
                            const std::vector<std::string> &order, std::size_t power)
{
    MultiSet result;
    if (power == 0 || universe.empty())
        return result;
    std::cout << "\nРучное заполнение мультимножества " << name << ".\n";
    std::cout << "Введите номер элемента универсума для каждого вхождения.\n";
    for (std::size_t i = 0; i < power; ++i)
    {
        const std::size_t index = readInt(
            "Элемент " + std::to_string(i + 1) + ": ", 1,
            order.size());
        const std::string &chosen = order[index - 1];
        if (result.count(chosen) >= universe.count(chosen))
        {
            std::cout << "Ошибка: элемент " << chosen
                      << " уже использован максимальное число раз ("
                      << universe.count(chosen) << ").\n";
            --i;
            continue;
        }
        result.add(chosen);
    }
    return result;
}

MultiSet generateAutomaticMultiset(const MultiSet &universe,
                                   std::size_t power)
{
    MultiSet result;
    if (power == 0 || universe.empty()) return result;
    std::vector<std::string> pool;
    pool.reserve(universe.size());
    for (const auto &[value, count] : universe.data())
    {
        for (std::size_t i = 0; i < count; ++i)
            pool.push_back(value);
    }
    std::random_device rd;
    std::mt19937_64 generator(rd());
    const std::size_t actualPower = std::min(power, pool.size());
    std::shuffle(pool.begin(), pool.end(), generator);
    for (std::size_t i = 0; i < actualPower; ++i)
        result.add(pool[i]);
    return result;
}

void printUniverse(const MultiSet &universe,
                   const std::vector<std::string> &order)
{
    std::cout << "\nУниверсум (" << order.size()
              << " уникальных элементов, общая мощность "
              << universe.size() << "):\n";
    if (order.empty())
    {
        std::cout << "∅\n";
        return;
    }
    std::size_t i = 1;
    for (const auto &value : order)
        std::cout << i++ << ": " << value
                  << " (кратность " << universe.count(value) << ")\n";
}

void printMultiset(const std::string &name, const MultiSet &set)
{
    std::cout << name << " = ";

    if (set.empty()) std::cout << "∅";
    else
    {
        std::cout << "{ ";
        bool first = true;
        for (const auto &[value, count] : set.data())
        {
            if (!first) std::cout << ", ";
            std::cout << value << " (" << count << ")";
            first = false;
        }
        std::cout << " }";
    }
    std::cout << "  |" << name << "| = " << set.size() << '\n';
}
