#pragma once

#include "multiset.hpp"

#include <string>
#include <vector>


MultiSet setUnion(const MultiSet& a, const MultiSet& b); // A ∪ B
MultiSet intersection(const MultiSet& a, const MultiSet& b); // A ∩ B
MultiSet difference(const MultiSet& a, const MultiSet& b, const MultiSet& universe); // A \ B 
MultiSet symmetricDifference(const MultiSet& a, const MultiSet& b, const MultiSet& universe); // A △ B

MultiSet complement(const MultiSet& a, const MultiSet& universe);

MultiSet arithmeticSum(const MultiSet& a, const MultiSet& b, const MultiSet& universe);
MultiSet arithmeticDifference(const MultiSet& a, const MultiSet& b);
MultiSet arithmeticProduct(const MultiSet& a, const MultiSet& b, const MultiSet& universe);
MultiSet arithmeticDivision(const MultiSet& a, const MultiSet& b);

