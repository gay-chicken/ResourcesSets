#include <iostream>

using namespace std;

float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );    // most number: 0x5f375a86
    y = * ( float * ) &i;
    y = y * ( threehalfs - ( x2 * y * y ) );    // 1st iteration
    y = y * ( threehalfs - ( x2 * y * y ) );    // 2nd iteration, this can be removed


    return y;
}

float InvSqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int *)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float *)&i;
    x = x * (1.5f - xhalf * x * x); // one Neuton iteration.
    return x;
}

int main() {
    float i = 16;
    cout << Q_rsqrt(i) << endl;
}