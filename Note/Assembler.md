# GNU汇编语言（GNU Assembler, GAS)

## 寻址方式

x86-32指令集支持最多使用四个部分来指定内存操作数，这四个部分分别是：偏移量、基址寄存器、索引寄存器和缩放因子。当处理器取到一条使用内存操作数的指令后，他会计算实际地址以决定操作数的最终内存地址。实际地址是这样计算的：
$$
实际地址 = 基址寄存器 + 索引寄存器 * 缩放因子 + 偏移量
$$
缩放因子必须是整数，有效的缩放因子包括1、2、4、8。最终计算得到的实际地址总是32位大小的。x86-32指令集支持8中不同的内存操作数寻址方式，如下表所示：

| 寻址方式      | 英文名称                   | 示例                          | 说明                                                         |
| :------------ | :------------------------- | :---------------------------- | :----------------------------------------------------------- |
| 立即寻址      | Immediate Addressing       | ``mov $10, %eax``             | 将10赋值到eax寄存器中                                        |
| 寄存器寻址    | Register Addressing        | ``mov %eax, %ebx``            | 将eax寄存器的值赋给ebx                                       |
| 直接寻址      | Direct Addressing          | ``mov data, %eax``            | 将data标签对应的内容加载到eax寄存器                          |
| 间接寻址      | Indirect Addressing        | ``mov (%eax), %ebx``          | 从eax指向的内存地址加载数据进ebx                             |
| 基址寻址      | Base Addressing            | ``mov 4(%ebx), %eax``         | 从ebx寄存器地址偏移4字节的内存加载到eax寄存器中              |
| 变址寻址      | Indexed Addressing         | ``mov (%ebx, %ecx, 4), %eax`` | 从基址为ebx寄存器，索引为ecx寄存器，并以4为缩放因子访问内存数据 |
| 基址+变址寻址 | Base + Index Addressing    | ``mov (%eax, %ebx), %ecx``    | 从eax和ebx组合指向的内存地址加载数据到ecx寄存器              |
| 栈寻址        | Stack Addressing           | ``mov (%esp), %eax``          | 从栈顶位置加载数据到eax寄存器                                |
| 符号偏移寻址  | Symbolic Offset Addressing | ``mov data + 4, %eax``        | 访问data标签之后4个字节的数据                                |

## EFLAGS寄存器

| 位      | 名称             | 符号 | 说明                                                         |
| ------- | ---------------- | ---- | ------------------------------------------------------------ |
| 0       | 进位标志         | CF   | 指示算术运算中的进位或借位情况                               |
| 1       | 保留             |      |                                                              |
| 2       | 奇偶校验位       | PF   | 结果的低 8 位中 1 的个数的奇偶性                             |
| 3       | 保留             |      |                                                              |
| 4       | 辅助进位标志     | AF   | 处理 BCD（十进制编码的二进制）加法时用于指示第 4 位是否发生进位。 |
| 5       | 保留             |      |                                                              |
| 6       | 零标志           | ZF   | 运算结果为 0，则 `ZF = 1`                                    |
| 7       | 符号标志         | SF   | 表示运算结果的符号。                                         |
| 8       | 陷阱标志         | TF   | 当 `TF = 1` 时，处理器会在执行每一条指令后引发单步中断。     |
| 9       | 中断启用标志     | IF   | 控制外部中断的响应。                                         |
| 10      | 方向标志         | DF   | 控制字符串操作指令（如 `MOVS`、`CMPS` 等）中的方向           |
| 11      | 溢出标志         | OF   | 有符号整数加法或减法操作是否发生溢出。                       |
| 12      | I/O特权级别位0   | IOPL | 用于控制输入输出指令（如 `IN`、`OUT`）的特权级别。           |
| 13      | I/O特权级别位1   | IOPL | 用于控制输入输出指令（如 `IN`、`OUT`）的特权级别。           |
| 14      | 任务嵌套         | NT   | 用于支持任务切换。该标志在任务切换时被设置和清除，用于管理任务状态。 |
| 15      | 保留             |      |                                                              |
| 16      | 恢复标志         | RF   | 当发生调试异常时，设置该标志后，处理器继续执行指令。         |
| 17      | 虚拟8086模式     | VM   | 在虚拟 8086 模式下设置，该模式允许在 32 位保护模式中运行 16 位程序。 |
| 18      | 对齐检查         | AC   | 如果内存访问不按规定的对齐方式进行（例如，访问未对齐的 4 字节数据），则设置该标志。 |
| 19      | 虚拟中断标志     | VIF  | 虚拟化环境中的中断标志，用于管理虚拟机中的中断               |
| 20      | 虚拟中断悬而未决 | VIP  | 虚拟中断是否待处理                                           |
| 21      | ID标志           | ID   | 启用或禁用指令的 `CPUID` 指令功能。`CPUID` 指令是用来查询处理器的各种特性（如支持的指令集、处理器型号等）的标准指令。 |
| 22 ~ 31 | 保留             |      |                                                              |

## 宏定义

**注意1：**GAS 宏是全局的，需避免命名冲突。

**注意2：**宏是文本替换，不会增加运行时开销。

#### 1. 基本宏定义

**语法：**

```asm
.macro 宏名称 [参数1, 参数2, ...]
    ; 宏体代码
.endm
```

**示例：**

```asm
.macro print_str str
    mov $4, %eax        ; sys_write 系统调用号
    mov $1, %ebx        ; 标准输出文件描述符
    mov \str, %ecx      ; 字符串地址
    mov $13, %edx       ; 字符串长度
    int $0x80
.endm

; 使用宏
print_str $message
```

#### 2. 带参数的宏

**默认参数：**

```asm
.macro add a, b=1
    mov \a, %eax
    add $\b, %eax
.endm

; 使用
add $10      ; 等效于 add $10, $1
add $10, 5   ; 显式指定第二个参数
```

**可变参数：**

用 `\@` 表示参数个数，`\n` 表示第 n 个参数：

```asm
.macro push_all reg1, reg2, reg3
    .if \@ > 0
        push \reg1
    .endif
    .if \@ > 1
        push \reg2
    .endif
    .if \@ > 2
        push \reg3
    .endif
.endm

; 使用
push_all %eax, %ebx  ; 推入两个寄存器
```

#### 3. 局部标签 (Local Labels)

在宏内部定义局部标签，避免多次展开时的标签冲突：

```asm
.macro delay count
    mov $\count, %ecx
1:  ; 局部标签（自动编号）
    dec %ecx
    jnz 1b  ; 跳转到前一个标签 1
.endm
```

或使用 `.L` 前缀（汇编器自动隐藏局部标签）：

```asm
.macro delay count
    mov $\count, %ecx
.Ldelay_loop:
    dec %ecx
    jnz .Ldelay_loop
.endm
```

#### 4. 条件汇编

结合 `.if`、`.else` 和 `.endif` 实现条件逻辑：

```asm
.macro debug_msg msg
    .ifdef DEBUG
        print_str "\msg"
    .endif
.endm
```

#### 5. 循环展开

通过 `.rept` 和 `.irp` 实现代码重复：

**固定次数循环：**

```asm
.macro push_regs times
    .rept \times
        push %eax
    .endr
.endm
```

**遍历列表：**

```asm
.macro pop_regs reg1, reg2, reg3
    .irp reg, \reg1, \reg2, \reg3
        pop \reg
    .endr
.endm

; 使用
pop_regs %eax, %ebx, %ecx
```

#### 6. 字符串操作

通过 `\()` 拼接参数：

```asm
.macro define_var name, value
    .data
\name:
    .long \value
.endm

; 使用
define_var counter, 0x1000  ; 生成标签 counter: .long 0x1000
```

#### 7. 嵌套宏

宏内部调用其他宏：

```asm
.macro syscall num
    mov $\num, %eax
    int $0x80
.endm

.macro exit code
    syscall 1         ; 调用 syscall 宏
    mov \code, %ebx
.endm
```

#### 8. 宏参数转字符串

将参数转换为字符串字面量：

```asm
.macro debug_print reg
    .ascii "Register \reg: %d\n"
    ; 输出时会替换 \reg 为实际寄存器名
.endm
```

#### 9. 保存和恢复寄存器

自动化保存/恢复寄存器：

```asm
.macro save_registers
    push %eax
    push %ebx
    push %ecx
.endm

.macro restore_registers
    pop %ecx
    pop %ebx
    pop %eax
.endm

; 使用
save_registers
; ... 代码 ...
restore_registers
```

#### 10. 宏与调试信息

结合 `.altmacro` 启用高级宏模式（支持更复杂的表达式）：

```asm
.altmacro
.macro assert_eq a, b
    .if \a != \b
        .error "Assertion failed: \a != \b"
    .endif
.endm
```



