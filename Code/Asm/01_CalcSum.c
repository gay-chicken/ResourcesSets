#include <stdio.h>

// 汇编过程
extern int CalcSum_(int a, int b, int c);

int main() {
    int a = 17, b = 11, c = 14;
    int sum = CalcSum_(a, b, c);

    printf("a: %d, b: %d, c: %d, sum = %d\n", a, b, c, sum);
}