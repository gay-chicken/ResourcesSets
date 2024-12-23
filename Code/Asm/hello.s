.section .rodata                # 定义一个只读数据段
msg: .ascii "Hello, world\n"    # 定义一个ASCII字符串

.set msglen, (. - msg)          # 计算msg的长度

.section .text                  # 定义一个文本节，包含了程序代码
.global main                    # 声明main为全局函数，对外可见

main:                           # 定义main函数(程序入口点)
    # write(1, msg, msglen)
    mov $1, %rax                # 将系统调用号1(write调用)作为调用码复制到rax
    mov $1, %rdi                # 将文件符1(标准输出)作为参数传递复制到rdi
    lea msg(%rip), %rsi         # 加载msg字符串的地址到rsi中
    mov $msglen, %rdx           # 将字符串长度复制到rdx中
    syscall                     # 读取rax的调用码执行write调用, 获取文件描述符、数据地址和数据长度(rdi, rsi, rdx, ...)

    # exit(0)
    mov $60, %rax               # 将系统调用号60(exit调用)复制到rax中
    mov $0, %rdi                # 将退出状态0复制到rdi中
    syscall                     # 读取rax的调用码执行系统调用，再接收传递的参数
