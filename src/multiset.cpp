#include "multiset.hpp"

void MultiSet::clear()
{
    data_.clear();
}

void MultiSet::add(const std::string &value, Count count)
{
    if (count == 0)
    {
        return;
    }
    data_[value] += count;
}

MultiSet::Count MultiSet::count(const std::string &value) const
{
    const auto it = data_.find(value);
    return it == data_.end() ? 0 : it->second;
}

MultiSet::Count MultiSet::size() const
{
    Count result = 0;
    for (const auto &[_, count] : data_)
    {
        result += count;
    }
    return result;
}

bool MultiSet::empty() const
{
    return data_.empty();
}

const MultiSet::Data &MultiSet::data() const
{
    return data_;
}
