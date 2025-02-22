startup_32:
    movl $0x10, %eax
    mov %ax, %ds
    mov %ax, %es
    mov %as, %fs
    mov as, %gs             // 指向gdt的0x10项（数据段
    lss _stack_start, %esp  // 设置栈（系统栈
    call setup_idt
    call setup_gdt
    xorl %eax, %eax
l:  incl %eax
    movl %eax, 0x000000
    cmpl %eax, 0x100000
    je 1b                   // 0地址处和1M地址处相同（A20没开启，就死循环
    jmp after_page_tables   // 页表
setup_idt:
    lea ignore_int, %edx
    movl 0x00080000, %eax
    movw %dx, %ax
    lea _idt, %edi
    movl %eax, (%edi)

after_page_tables:
    pushl $0
    pushl $0
    pushl $0
    pushl $L6
    pushl $_main
    jmp set_paging
L6:
    jmp L6
setup_paging:               // 设置页表
    ret