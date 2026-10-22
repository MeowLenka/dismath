#pragma once

#include <cstddef>
#include <map>
#include <string>

class MultiSet
{
public:
    using Count = std::size_t;
    using Data = std::map<std::string, Count>;
    MultiSet() = default;
    void clear();
    void add(const std::string &value, Count count = 1);
    Count count(const std::string &value) const;
    Count size() const;
    bool empty() const;
    const Data &data() const;

private:
    Data data_;
};
