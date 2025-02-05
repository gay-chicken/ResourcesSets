#include <stdio.h>

typedef union {
    unsigned char mask;
    struct {
        unsigned char bit0:1;  // 第 0 位
        unsigned char bit1:1;  // 第 1 位
        unsigned char bit2:1;  // 第 2 位
        unsigned char bit3:1;  // 第 3 位
        unsigned char bit4:1;  // 第 4 位
        unsigned char bit5:1;  // 第 5 位
        unsigned char bit6:1;  // 第 6 位
        unsigned char bit7:1;  // 第 7 位
    };
} BitField;

int main() {
    BitField field;
    const size_t size = sizeof(BitField);

    field.mask = 0xaa;
    printf("size: %ld, value: %u\n", size, field.mask);
    printf("%d%d%d%d%d%d%d%d\n",
           field.bit7, field.bit6, field.bit5, field.bit4,
           field.bit3, field.bit2, field.bit1, field.bit0);
}