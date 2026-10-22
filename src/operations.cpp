#include "operations.hpp"
#include "gray_code.hpp"

#include <limits>
#include <stdexcept>
#include <algorithm>

MultiSet setUnion(const MultiSet &a, const MultiSet &b)
{
    MultiSet result = a;

    for (const auto &[value, count] : b.data())
    {
        result.add(value, count > result.count(value) ? count - result.count(value) : 0);
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
        if (count > 0)
        {
            result.add(value, count);
        }
    }

    return result;
}

MultiSet complement(const MultiSet &a, const MultiSet &universe)
{
    MultiSet result;

    for (const auto &[value, countU] : universe.data())
    {
        const auto countA = a.count(value);
        if (countU > countA)
        {
            result.add(value, countU - countA);
        }
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
        const auto sum = result.count(value) + countB; 
        const auto count = std::min(universe.count(value), sum);
        result.add(value, count - result.count(value));
    }
    return result;
}

MultiSet arithmeticDifference(const MultiSet &a, const MultiSet &b)
{
    MultiSet result;
    for (const auto &[value, countA] : a.data())
    {
        const auto countB = b.count(value);
        if (countA > countB)
        {
            result.add(value, countA - countB);
        }
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
        {
            result.add(value, countA / countB);
        }
    }
    return result;
}
