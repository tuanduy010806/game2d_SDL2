#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

namespace Utils {
    // random 1 hoặc 2 để gọi  map ngẫu nhiên
    inline int RandomInt(int min, int max) {
        if (min > max) return min;
        return min + rand() % ((max - min) + 1);
    }

    //  ghan gtri trong khoảng [min,max]
    inline float Clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
}

#endif // UTILS_H
