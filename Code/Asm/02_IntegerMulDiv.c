#include <stdio.h>

extern int IntegerMulDiv_(int a, int b, int *prod, int *quo, int *rem);

int main() {
    int a = 21, b = 9;
    int prod, quo, rem;
    int rc;

    rc = IntegerMulDiv_(a, b, &prod, &quo, &rem);
    printf("Input - a: %d, b: %d\n", a, b);
    printf("Output - rc: %d, prod: %d, quo: %d, rem: %d\n", rc, prod, quo, rem);
}