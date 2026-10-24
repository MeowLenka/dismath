#include "operations.hpp"

#include <algorithm>

MultiSet setUnion(const MultiSet &a, const MultiSet &b)
{
    MultiSet result = a;
    for (const auto &[value, countB] : b.data())
    {
        const auto countA = result.count(value);
        if (countB > countA)
            result.add(value, countB - countA);
    }
    return result;
}

MultiSet intersection(const MultiSet &a, const MultiSet &b)
{
    MultiSet result;
    for (const auto &[value, countA] : a.data())
    {
        const auto countB = b.count(value);
        const auto count = std::min(countA, countB);
        result.add(value, count);
    }
    return result;
}

MultiSet complement(const MultiSet &a, const MultiSet &universe)
{
    MultiSet result;
    for (const auto &[value, countU] : universe.data())
    {
        const auto countA = a.count(value);
        result.add(value, countU - countA);
    }
    return result;
}

MultiSet difference(const MultiSet &a, const MultiSet &b, const MultiSet &universe)
{
    return intersection(a, complement(b, universe));
}

MultiSet symmetricDifference(const MultiSet &a, const MultiSet &b, const MultiSet &universe)
{
    return difference(setUnion(a, b), intersection(a, b), universe);
}

MultiSet arithmeticSum(const MultiSet &a, const MultiSet &b, const MultiSet &universe)
{
    MultiSet result = a;
    for (const auto &[value, countB] : b.data())
    {
        const auto current = result.count(value);
        const auto maxAllowed = universe.count(value);
        const auto target = std::min(current + countB, maxAllowed);
        result.add(value, target - current);
    }
    return result;
}

MultiSet arithmeticDifference(const MultiSet &a, const MultiSet &b)
{
    MultiSet result;
    for (const auto &[value, countA] : a.data())
    {
        const auto countB = b.count(value);
        if (countA > countB) result.add(value, countA - countB);
    }
    return result;
}

MultiSet arithmeticProduct(const MultiSet &a, const MultiSet &b, const MultiSet &universe)
{
    MultiSet result;
    for (const auto &[value, countA] : a.data())
    {
        const auto countB = b.count(value);
        if (countB > 0)
        {
            const auto count = std::min(countA * countB, universe.count(value));
            result.add(value, count);
        }
    }
    return result;
}

MultiSet arithmeticDivision(const MultiSet &a, const MultiSet &b)
{
    MultiSet result;
    for (const auto &[value, countA] : a.data())
    {
        const auto countB = b.count(value);
        if (countB > 0 && countA >= countB)
            result.add(value, countA / countB);
    }
    return result;
}
