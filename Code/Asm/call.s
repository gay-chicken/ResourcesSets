.global call
.type call, @function

.extern func
.extern funs

call:
    call func       # x * 2，返回结果在rax中

    mov %rax, %rdi  # 将C函数的返回结果作为参数传递给funs
    call funs       # rdi + 1, 读取rdi参数，返回rax

    ret
