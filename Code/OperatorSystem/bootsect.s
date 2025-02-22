// BOOTSEG = 0x07c0
// INITSEG = 0x9000
// SETUPSEG = 0x9020
// SYSSIZE = 0x8000         该变量可根据Image大小设定（编译操作系统时）
// SYSSET=0x1000
// ENDSEG = SYSSEG + SYSSIZE

.global begtext, begdata, begbss, endtext, enddata, endbss
.text
begtext:

.data
begdata:

.begbss
begbss:

entry start_
start_:
    mov ax, #BOOTSEG
    mov ds, ax          // ds = 0x7c0
    mov ax, #INITSEG
    mov es, ax          // es = 0x9000
    mov cx, #256
    sub si, si          // si = 0. ds:si = 0x7c00
    sub di, di          // di = 0. es:di = 0x90000
    rep movw            // 将0x7c00处的256个字移动到0x90000处
    jmpi go, INITSEG    // cs:ip = INITSEG:go
go:
    mov ax, cs          // cs = 0x9000
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, #0xff00
load_setup:
    mov dx, #0x0000         // dh=磁头号, dl=驱动器号
    mov cx, #0x0002         // ch=柱面号, cl=开始扇区
    mov bx, #0x0200         // es:bx = 内存地址
    mov ax, #0x0200+SETUPLEN    // ah=0x02-读磁盘, al=扇区数量(SETUPLEN=4)
    int 0x13            // BIOS中断
    jnc ok_load_setup
    mov dx, #0x0000
    mov ax, #0x0000     // 复位
    int 0x13
    j load_setup        // 重读
ok_load_setup:          // 载入setup模块
    mov dl, #0x00
    mov ax, #0x0800     // ah=8获得磁盘参数
    int 0x13
    mov ch, #0x00
    mov sectors, cx
    mov ah, #0x03
    xor bh, bh
    int 0x10            // 读光标
    mov cx, #24         // 要显示的字符数
    mov bx, #0x0007     // 0x0007是显示属性
    mov bp, #msg1       // 字符所在地址
    mov ax, #1301
    int 0x10            // 显示字符
    mov ax, #SYSSEG
    mov es, ax
    call read_it            // 读入system模块
    jmpi 0, SETUPSEG        // 转入x09020:0x0000执行setup.s

read_it:
    mov ax, es
    cmp ax, #ENDSEG
    jb ok1_read

ok1_read:
    mov ax, sectors
    sub ax, sread       // sread是当前磁道已读扇区数，ax未读扇区数
    call read_track     // 读磁道...


sectors: .word 0        // 磁道扇区数
msg1: .byte 13, 10
      .ascii "Loading system.."
      .byte 13, 10, 13, 10

.org 510
    .word 0xAA55        // 扇区的最后两个字节