#ifndef MATH_CPP
#define MATH_CPP 1

#include "../../include/utils/math.h"

namespace Math{
    
    template<class T=int, class U=int>
    std::vector<T> range(T start, T stop, U step){
        std::vector<T> v;

        while(1) {
            if (start > stop) {
                break;
            }
            v.push_back(start);
            start += step;
        }
        return v;
    }

} // namespace Math


#endif // MATH_CPP
