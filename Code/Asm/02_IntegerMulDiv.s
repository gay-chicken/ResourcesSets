.global IntegerMulDiv_

/*
    int IntegerMulDiv_(int a, int b, int *prod, int *quo, int *rem);

    计算：
        *prod = a * b
        *quo = a / b
        *rem = a % b

    返回值: 0 Scuess
            1 Error
*/
# %rcx, %rdx, %r8, %r9, %r10, %r11

IntegerMulDiv_:
    push %rbx

    mov $0, %rbx
    imul %rbx, %rcx, %rdx    # %ebx = %ecx * %edx
    mov %rbx, (%r8)

    pop %rbx

    mov $0, %rax
    ret
