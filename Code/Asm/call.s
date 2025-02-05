.global call
.type call, @function

.extern func
.extern funs

call:               # 参数传递次序: rdi, rsi, rdx, rcx, r8, r9, 栈
    call func       # 调用C函数计算x * 2，返回结果在rax中

    mov %rax, %rdi  # 将rax的值赋给rdi作为funs的第一个参数传递
    call funs       # funs中计算rdi + 1

    ret
