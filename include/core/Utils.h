#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

namespace Utils {
    // Generates a random integer within a [min, max] range
    inline int RandomInt(int min, int max) {
        if (min > max) return min;
        return min + rand() % ((max - min) + 1);
    }

    // Clamps a value between a minimum and maximum
    inline float Clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
}

#endif // UTILS_H
