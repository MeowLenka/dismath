#include "gray_code.hpp"

#include <limits>
#include <stdexcept>
#include <bitset>

std::vector<std::string> generateGrayCode(std::size_t bits)
{
    std::vector<std::string> result;
    if (bits == 0) return result;
    const std::size_t count = 1 << bits;
    result.reserve(count);
    for (std::size_t i = 0; i < count; ++i)
    {
        unsigned long gray = i ^ (i >> 1);
        result.push_back(decimalToBinary(gray, bits));
    }
    return result;
}


std::string decimalToBinary(unsigned long long value, std::size_t width)
{
    std::string result(width, '0');

    for (std::size_t i = 0; i < width; ++i)
    {
        const std::size_t shift = width - 1 - i;
        result[i] = ((value >> shift) & 1ULL) ? '1' : '0';
    }

    return result;
}

