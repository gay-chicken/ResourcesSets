.global CalcSum_

/*
    extern "C" int CalcSum_(int a, int b, int c);

    这个函数演示了如何在C++和汇编中传递参数.
    返回值：a + b + c

    ps1: Linux/Unix (System V ABI)前6个整数参数传递为%rdi, %rsi, %rdx, %rcx, %r8, %r9
    ps2: Windows x64 ABI前4个整数参数传递为%rcx, %rdx, %r8, %r9
*/
CalcSum_:

.ifdef LINUX
    mov %rdi, %rax
    add %rsi, %rax
    add %rdx, %rax
.endif

.ifndef LINUX
    mov %rcx, %rax
    add %rdx, %rax
    add %r8, %rax
.endif
    ret
