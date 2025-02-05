.global funs
.type funs, @function

funs:
    inc %rdi
    mov %rdi, %rax
    ret             # 返回值在rax
