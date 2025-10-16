#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>

namespace Utils {
    // inline để tăng tốc độ thực hiện, và biến hàm trong file header .h thành hợp lệ
    // tạo ra ngẫu nhiên 1 hoặc 2 để làm chỉ số gọi ra map ngẫu nhiên
    inline int RandomInt(int min, int max) {
        if (min > max) return min;
        return min + rand() % ((max - min) + 1);
    }

    // kẹp lại giá trị của biến value đưa vào và ghan ở khoảng [min,max]
    inline float Clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
}

#endif // UTILS_H
