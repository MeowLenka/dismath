#include "gray_code.hpp"
#include "input.hpp"
#include "operations.hpp"

#include <random>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <chrono>

void printOperations(const MultiSet &a, const MultiSet &b, const MultiSet &universe)

{
    std::cout << "\nОПЕРАЦИИ НАД МУЛЬТИМНОЖЕСТВАМИ:\n\n";
    printMultiset("A ∪ B", setUnion(a, b));
    printMultiset("A ∩ B", intersection(a, b));
    printMultiset("A \\ B", difference(a, b, universe));
    printMultiset("B \\ A", difference(b, a, universe));
    printMultiset("A △ B", symmetricDifference(a, b, universe));
    printMultiset("Ā", complement(a, universe));
    printMultiset("B̄", complement(b, universe));
    std::cout << "\n";
    printMultiset("A + B", arithmeticSum(a, b, universe));
    printMultiset("A - B", arithmeticDifference(a, b));
    printMultiset("B - A", arithmeticDifference(b, a));
    printMultiset("A * B", arithmeticProduct(a, b, universe));
    printMultiset("A / B", arithmeticDivision(a, b));
    printMultiset("B / A", arithmeticDivision(b, a));
}

bool createMultisets(std::size_t &bits, MultiSet &universe, std::vector<std::string> &universeOrder, MultiSet &a, MultiSet &b)
{
    const auto t0 = std::chrono::steady_clock::now();
    std::vector<std::string> codes;
    codes = generateGrayCode(bits);
    const auto t1 = std::chrono::steady_clock::now(); //
    universe.clear();
    universeOrder.clear();
    if (bits == 0)
    {
        a.clear();
        b.clear();
        std::cout << "\nРазрядность равна 0.\n";
        printMultiset("U", universe);   
        printMultiset("A", a);
        printMultiset("B", b);
        return true;
    }

    // случайное распределение кратностей элементов универсума
    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::uniform_int_distribution<std::size_t> dist(1, 7);

    for (const auto &code : codes)
    {
        universe.add(code, dist(generator));
        universeOrder.push_back(code);
    }

    const auto t2 = std::chrono::steady_clock::now(); //
    printUniverse(universe, universeOrder);
    const auto t3 = std::chrono::steady_clock::now(); //
    const auto genMs = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count(); //
    const auto fillMs = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count(); //
    const auto printMs = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count(); //

    std::cout << "generateGrayCode: " << genMs << " ms\n"; //
    std::cout << "заполнение MultiSet: " << fillMs << " ms\n"; // 
    std::cout << "печать MultiSet: " << printMs << " ms\n"; //

    const std::size_t maxPower = universe.size();
    const std::size_t powerA = readInt("\nВведите мощность мультимножества A: ", 0, maxPower);
    const std::size_t powerB = readInt("Введите мощность мультимножества B: ", 0, maxPower);

    const int modeA = readInt("\nСпособ заполнения A (1 - вручную, 2 - автоматически): ", 1, 2);

    const int modeB = readInt("Способ заполнения B (1 - вручную, 2 - автоматически): ", 1, 2);

    if (modeA == 1)
        a = readManualMultiset("A", universe, universeOrder, powerA);
    else
        a = generateAutomaticMultiset(universe, powerA);

    if (modeB == 1)
        b = readManualMultiset("B", universe, universeOrder, powerB);
    else
        b = generateAutomaticMultiset(universe, powerB);

    std::cout << "\nСОЗДАННЫЕ МНОЖЕСТВА:\n";
    printMultiset("A", a);
    printMultiset("B", b);
    return true;
}

int main()
{
    constexpr std::size_t MAX_BITS = 20;
    std::size_t bits = 0;
    MultiSet universe;
    std::vector<std::string> universeOrder;
    MultiSet a;
    MultiSet b;
    while (true)
    {
        std::cout << "\n1. Создать новые мультимножества\n";
        std::cout << "2. Показать универсум и мультимножества\n";
        std::cout << "3. Выполнить операции над мультимножествами\n";
        std::cout << "0. Выход\n";
        const int choice = readInt("Выберите пункт: ", 0, 3);
        switch (choice)
        {
        case 1:
            bits = readInt("\nВведите разрядность бинарного кода Грея: ", 0, MAX_BITS);
            createMultisets(bits, universe, universeOrder, a, b);
            break;
        case 2:
            std::cout << '\n';
            printUniverse(universe, universeOrder);
            printMultiset("A", a);
            printMultiset("B", b);
            break;
        case 3:
            printMultiset("A", a);
            printMultiset("B", b);
            printOperations(a, b, universe);
            break;
        case 0:
            return 0;
        }
    }
}