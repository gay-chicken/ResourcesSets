#include <stdio.h>

extern int call(int);
extern void scall();
int main() {
    // printf("%d\n", call(5));
    scall();
    printf("Calling scall\n");
}