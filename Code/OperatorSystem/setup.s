// SYSSEG = 0x1000

// 内存地址 长度    名称
// 0x90000  2       光标位置
// 0x90002  2       扩展内存大小
// 0x9000C  2       显卡参数
// 0x901FC  2       根设备号

start_:
    mov ax, #INITSEG
    mov ds, ax
    mov ah, #0x03
    xor bh, bh
    int 0x10            // 取出光标位置dx
    mov [0], dx         // 取出光标位置（包括其他硬件参数）到0x90000处
    mov ah, #0x88
    int 0x15
    mov [2], ax         // 扩展内存大小, 0x9000:0x2处
    cli                 // 不允许中断
    mov ax, #0x0000
    cld
do_move:
    mov es, ax
    add ax, #0x1000
    cmp ax, #0x9000
    jz end_move
    mov ds, ax
    sub di, di
    sub si, si
    mov cx, #0x9000
    rep movsw           // 将system模块移到0地址
    jmp do_move
end_move:
    mov ax, #SETUPSEG
    mov ds, ax
    lidt idt_48
    lgdt gdt_48

    // 8042是键盘控制器，其输出端口P2用来控制A20地址线
    call empty_8042
    mov al, #0xd1
    out #0x64, al
    call empty_8042
    mov al, #0xdf
    out #0x60, al
    call empty_8042
    // 进入保护模式CR0.PE=1保护模式
    mov ax, #0x0001
    mov cr0, ax
    jmpi 0, 8

empty_8042:
    .word 0x00eb, 0x00eb
    in al, #0x64
    test al, #2
    jnz empty_8042
    ret

idt_48: .word 0
        .word 0, 0
gdt_48: .word 0x800
        .word 512+gdt, 0x9
gdt: .word 0, 0, 0, 0
     .word 0x07FF, 0x0000, 0x9A00, 0x00C0
     .word 0x07FF, 0x0000, 0x9200, 0x00C0

// 保护模式下的地址翻译和中断处理，即GDT(Global Descriptor Table, 全局描述符表)的作用
// 实模式下地址翻译：cs<<4+ip，保护模式下的地址翻译：根据cs查表+ip
// 保护模式下中断处理函数入口，即IDT(Interrupt Descriptor Table, 中断描述符表)的作用
// 通过int n定位IDT里中断处理函数的入口地址。
// GDT表项内容有存放规定，每一位都有特殊的含义。