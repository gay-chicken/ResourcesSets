# Godot教程

GDScript 是一种高级、面向对象、命令式和渐进类型的编程语言，专为 Godot 而设计。它使用基于缩进的语法，类似于 Python 等语言。其目标是针对 Godot 引擎进行优化并与之紧密集成，从而为内容创建和集成提供极大的灵活性。

GDScript 完全独立于 Python，并非基于 Python。

## 基本语法

### 语法示例

```text
# 可以通过'#'进行注释
# 一个文件就是一个类!

# (optional) 显示在编辑器节点窗口中的图标:
@icon("res://path/to/optional/icon.svg")

# (optional) 类定义:
class_name MyClass

# 类继承:
extends BaseClass


# 变量.
var a = 5
var s = "Hello"
var arr = [1, 2, 3]
var dict = {"key": "value", 2: 3}
var other_dict = {key = "value", other_key = 2}
var typed_var: int
var inferred_type := "String"

# 常量.
const ANSWER = 42
const THE_NAME = "Charly"

# 枚举.
enum {UNIT_NEUTRAL, UNIT_ENEMY, UNIT_ALLY}
enum Named {THING_1, THING_2, ANOTHER_THING = -1}

# 内置向量类型.
var v2 = Vector2(1, 2)
var v3 = Vector3(1, 2, 3)


# 函数.
func some_function(param1, param2, param3):
    const local_const = 5

    if param1 < local_const:
        print(param1)
    elif param2 > 5:
        print(param2)
    else:
        print("Fail!")

    for i in range(20):
        print(i)

    while param2 != 0:
        param2 -= 1

    match param3:
        3:
            print("param3 is 3!")
        _:
            print("param3 is not 3!")

    var local_var = param1 + 3
    return local_var


# 函数重写基类/超类上的同名函数.
# 如果想要调用它们，可以使用"super":
func something(p1, p2):
    super(p1, p2)


# 也可以调用父类中的另一个函数:
func other_something(p1, p2):
    super.something(p1, p2)


# 内部类
class Something:
    var a = 10


# 构造函数
func _init():
    print("Constructed!")
    var lv = Something.new()
    print(lv.a)
```

### 关键字

略

### 运算符

略

1. 如果 ``/`` 运算符的两个操作数都是 int，那么执行的是整除而不是小数除法。例如，``5 / 2 == 2`` ，而不是 ``2.5`` 。如果不希望出现这种情况，请至少使用一个浮点数字面形式(如 ``x / 2.0`` )、显式声明(如 ``float(x) / y`` )或乘以一个浮点数(如 ``x * 1.0`` )。
2. ``%`` 操作符仅适用于 ``int`` ，对于浮点数，请使用 ``fmod()`` 函数。
3. 对于负值，``%`` 运算符和 ``fmod()`` 使用截断而不是向负无穷舍入。这意味着余数带有符号。如果需要数学意义上的余数，请使用 ``posmod()`` 和 ``fposmod()`` 函数。
4. ``**`` 运算符是左关联运算。这意味着 ``2 ** 2 ** 3`` 等于 ``(2 ** 2) ** 3`` 。 使用括号明确指定所需的优先级，例如 ``2 ** (2 ** 3)`` 。
5. 运算符 ``==`` 和 ``!=`` 有时可以比较不同类型的值（例如，``1 == 1.0`` 为真），但在其他情况下会导致运行时错误。如果不确定操作数的类型，可以安全地使用 ``is_same()`` 函数（但要注意，它对类型和引用的要求更严格）。要比较浮点数，请使用 ``is_equal_approx()`` 和 ``is_zero_approx()`` 函数。

### 注解

GDScript 中有一些特殊的标记，它们的作用类似关键字，但不是关键字，而是注解。每个注解都以 ``@`` 字符开头，并由名称指定。

注解会影响外部工具处理脚本的方式，但通常不会改变脚本的行为。

例如，可以使用注解将值导出到编辑器中：

```text
@export_range(1, 100, 1, "or_greater")
var ranged_var: int = 50
```
