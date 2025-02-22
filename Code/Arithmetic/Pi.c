#include <stdio.h>

inline static float Basel(int num) {   // 巴塞尔问题 = pi^2 / 6
    float sum = 0;
    for (int i = 1; i <= num; ++i) {
        sum += 1.0 / (i * i);
    }
    return sum;
}

inline static float LeibnizSeries(int num) {    // 莱布尼兹级数计算Pi
    float sum = 0;
    int flag = -1;
    int BaseNum = 1;
    for (int i = 1; i <= num; ++i) {
        sum += -1* flag * 1.0 / BaseNum;
        BaseNum += 2;
        flag *= -1;
    }
    return  4 * sum;
}

inline static float SeriesExpansion(int num) { // 级数展开计算e
    long LastNum = 1;
    float sum = 1;
    for (int i = 1; i <= num; ++i) {
        LastNum *= i;
        sum += 1.0 / LastNum;
    }
    return sum;
}

int main() {
    printf("%f\n", SeriesExpansion(25));
}