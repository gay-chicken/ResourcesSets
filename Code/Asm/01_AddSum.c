#include <stdio.h>

// Linux: RDI, RSI, RDX, RCX, R8, R9
// Win32: RCX, RDX, R8, R9, R10, R11
extern int AddSum_(int, int);

int main() {
    int sum = AddSum_(10, 20);
    printf("sum = %d\n", sum);
}