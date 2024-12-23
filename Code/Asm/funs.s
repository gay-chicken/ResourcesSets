.global funs
.type funs, @function

funs:               # 参数传递: rdi, rsi, rdx, rcx, r8, r9, 栈
    add $1, %rdi
    mov %rdi, %rax
    ret             # 返回值在rax
