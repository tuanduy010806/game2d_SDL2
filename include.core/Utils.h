#ifndef UTILS_H
#define UTILS_H
#include <cstdlib>

namespace Utils {
    inline int RandomInt(int min, int max) {
        return min + rand() % ((max - min) + 1);
    }

    inline float Clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
}
#endif
