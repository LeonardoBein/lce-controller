#ifndef MATH_H
#define MATH_H 1

#include <vector>
#include <numeric>
#include <algorithm>

namespace Math{

    template<class T=int, class U=int>
    std::vector<T> range(T start, T stop, U step=1);





} // namespace Math

#include "../../src/utils/math.cpp"

#endif // MATH_H

