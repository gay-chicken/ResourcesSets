.global AddSum_

AddSum_:
.ifdef LINUX
    mov %rdi, %rax
    add %rsi, %rax
.endif

.ifdef WIN32
    mov %rcx, %rax
    add %rdx, %rax
.endif
    ret
