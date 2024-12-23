.global scall
.type scall, @function

scall:
    mov $-1, %rdi   # 传入exit值
    mov $60, %rax   # 将exit的系统调用号存入rax
    syscall         # 系统调用
