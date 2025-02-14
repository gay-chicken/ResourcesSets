## 引用

介绍：引用的作用是为变量提供一个别名

本质：引用在C++内部的实现是一个指针常量

注意：

1. 引用必须初始化
2. 引用初始化后无法改变指向
3. 引用不消耗内存空间

### 基本使用

```C++
int main() {
    int x = 10;
    int y = 20;
    int& a = x;    // 引用必须被初始化
    // a = y;      // 引用无法改变指向
}
```

### 引用作函数参数

引用可以用作函数的入参，降低函数调用时为函数入参分配内存空间的开销，并且在函数内部对引用入参的修改可以作用到传递进函数的变量中。

```C++
void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

int main() {
    int a = 10;
    int b = 20;
    swap(a, b);
    std::cout << a << std::endl;    // 20
    std::cout << b << std::endl;    // 10
}
```

### 引用作函数的返回值

引用可以作为函数的返回值，需要注意不要将局部变量返回。当函数的返回值是引用时，函数可以作为一个左值使用：

```C++
int& func_01() {
    int a = 10;
    return a;
}

int& func_02() {
    static int a = 20;
    return a;
}

int main() {
    int a_01 = func_01();
    std::cout << a_01 << std::endl;    // 可能是10
    std::cout << a_01 << std::endl;    // 无效数据
    
    int a_02 = func_02();
    std::cout << a_02 << std::endl;    // 输出20
    func_02() = 200;
    std::cout << a_01 << std::endl;    // 输出200
}
```

### 常量引用

```C++
// 1. 错误操作
int main() {
    // 被const修饰后，编译器将代码修改为 int temp = 10;  const int& p = temp;
    const int& p = 10;    // 运行崩溃，引用必须指向一块合法的内存空间
}
```

常量引用一般用作函数形参，防止形参改变实参。

```C++
// 2. 常量引用作形参
void show(const int& x) {
    // x = 123;    // 编译错误 error: assignment of read-only reference 'x'
    std::cout << x std::endl;
}

int main() {
    int x = 10;
    show(x);
}
```

## 函数

### 函数默认参数

在C++中，函数的形参允许拥有默认值，当传入参数缺省时会使用默认值。

注意：

1. 默认值需要从右往左且连续。
2. 函数声明和定义中只能有一处存在默认值，一般存在于声明中。

#### 基本使用

```C++
int show(int x = -1) {
    std::cout << x << std::endl;
}

int main() {
    int x = 20;
    show();    // -1
    show(x);    // 20
}
```

#### 函数的多个默认值

```C++
int add(int a = 10, int b = 20, int c = 30) {
    return a + b + c;
}

int main() {
    int x;
    x = add(1, 2);
    std::cout << x << std::endl;    // 33
    
    x = add();
    std::cout << x << std::endl;    // 60
}
```

#### 函数默认值的声明

```C++
int add(int a = 10, int b = 20, int c = 30);

int add(int a, int b, int c) {
    return a + b + c;
}

int main() {
    int x;
    x = add(1, 2);
    std::cout << x << std::endl;    // 33
    
    x = add();
    std::cout << x << std::endl;    // 60
}
```

#### 一些错误的使用方式

```C++
// 错误1：默认值需要从右往左
int add(int a = 10, int b = 20, int c) {
    return a + b + c;
}

// 错误2：默认值需要连续赋予
int add(int a = 10, int b, int c = 30) {
    return a + b + c;
}

// 错误3.1：声明和定义中只能存在一次默认值赋予
int add(int a = 10, int b = 20, int c = 30);

int add(int a = 10, int b = 20, int c = 30) {
    return a + b + c;
}

// 错误3.2：声明和定义中只能存在一次默认值赋予
int add(int a = 10, int b = 20, int c = 30);

int add(int a, int b, int c = 30) {
    return a + b + c;
}
```

### 函数占位符

在函数的参数列表中，只声明数据类型没有名称的形参被称为占位符。占位符也可以拥有默认值。

```C++
void show(int a, int = 10) {
     std::cout << "hello, world!" << std::endl;
}
```

### 函数重载

C++中允许多个函数名相同，参数列表不同的函数存在。

作用：提供复用性，简化开发流程。

重载条件：

+ 同一作用域下
+ 函数名称相同
+ 函数参数列表不相同，包括顺序不相同、类型不相同和个数不相同。

函数的返回值不作为函数重载的条件。

#### 基本使用

```C++
// 重载1
void show() {}

// 重载2
void show(int) {}

// 重载3
void show(char) {}

// 重载4
void show(int, char) {}

// 重载5
void show(char, int) {}
```

#### 使用注意

引用可以作为重载条件

```C++
void show(int&) {
     std::cout << "int&" << std::endl;
}

void show(int) {
    std::cout << "int" << std::endl;
}

int main() {
    show(0);    // int
}
```

当函数重载遇上默认值容易造成重载冲突。

```C++
void show() {}

void show(int = 0) {}

int main() {
    show();    // 编译报错，二义性
    show(0);    // 正确
}
```

### 函数修饰符

- **`= delete`**：禁用函数（如拷贝构造函数、移动构造函数等）。
- **`= default`**：显式请求编译器生成默认函数。
- **`explicit`**：禁止隐式类型转换。
- **`inline`**：建议函数内联以优化性能。
- **`constexpr`**：标记为常量表达式函数，返回值可在编译时计算。
- **`noexcept`**：声明函数不会抛出异常。
- **`virtual`**：声明虚函数，实现多态。
- **`override`**：确保函数重写基类的虚函数。
- **`final`**：防止函数重写或类继承。
- **`static`**：声明静态成员函数。
- **`friend`**：允许其他类或函数访问私有成员

### 函数尾返回

```C++
auto func() -> int {
    return 42;
}
```

### std::function<>与std::bind()

`std::bind()`将参数与函数绑定，返回一个`std::function<>`函数对象。

```C++
#include <functional>

int add(int x, int y) {
    return x + y;
}

int main() {
    std::function<int()> f1 = std::bind(add, 1, 2);
    int rs1 = f1(); // 3

    std::function<int(int, int)> f2 = add;
    int rs2 = f2(3, 5); // 8

    std::function<int(int, int)> f3 = std::bind(add, std::placeholders::_1,
                                                std::placeholders::_2);
    int rs3 = f3(4, 8); // 12

    std::function<int(int)> f4 = std::bind([](int x, int y) -> int
                                                { return x + y; },
                                                4,
                                                std::placeholders::_1);
    int rs4 = f4(1); // 5

    std::function<int(int)> f5 = std::bind(add, 7, std::placeholders::_1);
    int rs4 = f5(2); // 9
}
```

## 类和对象

C++面向对象三大特性：封装、继承、多态。

### 封装、继承和多态

#### 封装

封装是将数据（属性）和操作数据的方法（函数）组合在一起，形成一个独立的单元（通常称为类）。通过封装，可以隐藏内部实现细节，只暴露必要的接口给外部使用。

意义：

+ 数据保护：通过访问控制（如私有、保护和公共），可以防止外部代码直接修改对象的内部状态
+ 简化使用：用户只需理解公开的接口，而无需了解内部复杂性。
+ 抽象整体：将属性和行为看做一个整体，表现事物的多样性。

```C++
class Cricle {
    // 权限控制
    private:
    protected:
    public:
    // 行为
    void show() {}
    
    // 属性
    int m_radius;

}
```



#### 继承

继承是通过创建一个新类（子类）来扩展或修改已有类（父类）的功能。子类可以继承父类的属性和方法，也可以增加新的属性和方法。

意义：

+ 代码重用：可以重用父类的代码，减少重复。
+ 层次结构：建立类的层次关系，有助于组织代码。

#### 多态

多态允许不同类的对象通过相同的接口进行调用。它可以分为编译时多态（如函数重载和运算符重载）和运行时多态（如虚函数和继承）。

意义：

+ 灵活性：可以用统一的方式处理不同类型的对象，提高代码的灵活性和可扩展性。
+ 易于维护：可以在不修改客户端代码的情况下添加新类型。

### 对象的初始化和清理

#### 构造函数

构造函数主要作用是创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无需手动调用。

+ 构造函数没有返回值，也不需要void
+ 构造函数名称与类名相同
+ 构造函数可以有参数，因此可以发生重载
+ 程序在调用对象时候会自动调用构造，无需手动调用，而且只会在创建对象时调用一次。

```C++
class A {
  public:
    A(){}    // (默认)构造函数
    A(int) {}    // 有参构造函数
    A(const A& a) {}    // 拷贝构造函数
};

int main() {
    // 1.括号法
    Person a1(10);
    
    // 2.显示法
    Person a2 = Person(10);
    Person(10);    // 这是一个匿名对象，当前行执行结束后系统会立即回收该对象
    
    // 3.隐式转换法
    Person a3 = 10;    // 等价Person a4 = Person(10);
}
```

**注意事项**：

调用默认构造函数时不要使用括号调用法，因为编译器会认为这是一个声明。

```C++
int main() {
    A a4();    // 无法创建对象，编译器识别为一个函数声明
}
```

不要使用拷贝构造函数去初始化一个匿名对象

```C++
int main() {
    Person(a5);    // 重定义。编译器会认为他们是等价的Person(a3) === Person a3;
}
```

##### 拷贝构造的调用时机

+ 使用一个已经创建完毕的对象来初始化一个新对象
+ 值传递的方式给函数传值
+ 以值方式返回局部对象

```C++
class Person {
    public:
    
    Person() {
        std::cout << "Person()" << std::endl;
    }
    Person(const Person& p) {
        std::cout << "Person(const Person&)" << std::endl;
    }
};

void func01(const Person p) {}
Person func02() {
    return Person();
}

int main() {
    Person p1;    // Person()
    
    Person p2 = p1;    // 用现有对象进行初始化，调用拷贝构造
    func01(p1);    // 以值传递参数，调用拷贝构造
    func02();    // 返回局部对象的值，调用拷贝构造
}
```

##### 构造函数调用规则

在默认情况下，C++编译器至少给一个类添加3个函数：

+ 默认构造函数(无参、函数体为空)
+ 默认析构函数(无参、函数体为空)
+ 默认拷贝构造函数，对属性进行值拷贝



构造函数调用规则如下：

+ 如果用户定义有参构造函数，C++编译器不再提供默认无参构造，但会提供默认拷贝构造

+ 如果用户定义拷贝构造函数，C++编译器不再提供其他构造函数

```C++
class Step1{
    public:
    Step1(int x) {
        m_age = x;
    }
    
    int m_age;
};

class Step2{
    public:
    Step2(const Step2& s) {}
    
    int m_age;
};

int main() {
    Step1 s1(21);
    Step1 st = s1;
    std::cout << st.m_age << std::endl;    // 21
    
    Step2 s2();    // 编译错误，找不到Step2()构造函数
}
```

#####   深拷贝和浅拷贝

编译器默认提供的拷贝构造函数是值拷贝，当需要拷贝在堆区的数据时，会将堆区地址一并拷贝，造成了在析构函数释放堆区内存时的二次释放，造成程序崩溃。

```C++
#include <iostream>
#include <string>

class Apple {
    public:
    Apple(int c = 0, int b = 0) {
        count = c;
        brand = new int(b);
    }
    Apple(const Apple& p) {    // 深拷贝
        count = p.count;
        brand = new int(*p.brand);
    }
    ~Apple() {
        if (brand != nullptr) {
            delete brand;
            brand = nullptr;
        }
    }

    int count;
    int* brand;
};

void test() {
    Apple app1(10, 4);
    Apple app2 = app1;

    std::cout << app1.count << "    " << app1.brand << std::endl;
    std::cout << app2.count << "    " << app2.brand << std::endl;
}

int main() {
    test();
}
```

##### 初始化列表

```C++
class Person {
    public:
    Person() : x(10), y(20), z(30) {}
    Person(int a, int b, int c) : x(a), y(b), z(c) {}
    
    int x;
    int y;
    int z;
};

int main() {
    Person p;
}
```

#### 析构函数

析构函数主要作用在于对象销毁前系统自动调用，执行一些清理操作。

+ 析构函数没有返回值，也不需要void
+ 函数名称与类名相同，且在名称前加 ``~`` 
+ 析构函数不可以有参数，因此不可以重载
+ 程序在对象销毁前会自动调用析构函数，

```C++
class A {
  public:
    ~A() {}    // 析构函数  
}
```

### 类对象作为类成员

```C++
#include <iostream>
#include <string>

using namespace std;

class Teather {
    public:
    Teather(string n) : name(n) {
        cout << "Teather" << endl;
    }
    string name;
};

class Student {
    public:
    Student(string n) : name(n) {
        cout << "Student" << endl;
    }
    string name;
    int age;
};

class Class {
    public:
    Class(string t_name, string s_name) : teather(t_name), student(s_name) {
        cout << "Class" << endl;
    }
    Teather teather;
    Student student;
};

int main() {
    Class c("老刘", "张三");    // 调用顺序：先 Teather, Student 后 Class
    cout << c.teather.name << c.student.name << endl;
}
```

### 静态成员

静态成员变量：

+ 所有对象共享同一份数据
+ 编译阶段分配内存
+ 类内声明，类外初始化

静态成员函数：

+ 所有对象共享一个函数
+ 静态成员函数只能访问静态成员变量

```C++
#include <iostream>

using namespace std;

class Person {
    public:

    static int total;
    static void handle(int x = total) {
        total = x;
        cout << total << endl;
    }
};

int Person::total = 100;

int main() {
    Person::handle();
    Person::handle(20);
}
```

### this指针

可用于记录类对象，示例：
```C++
#include <iostream>
#include <list>

using namespace std;

class Person {
    public:
    Person() {
        objs.push_back(this);
    }
    ~Person() {
        objs.remove(this);
    }
    static void show() {
        cout << "size: " << objs.size() << endl;
        for(auto& x : objs) {
            cout << x << "\n";
        }
    }
    static list<Person*> objs;
};

list<Person*> Person::objs;

int main() {
    Person p1;
    Person::show();

    {
        Person p2, p3, p4, p5;
        Person::show();
    }

    Person p6;
    Person::show();
}
```

输出:

```
size: 1
0x61ff1f
size: 5
0x61ff1f
0x61ff1d
0x61ff1c
0x61ff1b
0x61ff1a
size: 2
0x61ff1f
0x61ff1e
```

利用this指针返回引用可以实现链式调用：

```C++
#include <iostream>
#include <list>

using namespace std;

class Person {
    public:
    Person& PersonAddToSelf(const Person& p) {
        this->total += p.total;
        return *this;
    }

    int total;
};

int main() {

    Person p1, p2;
    p1.total = 10;
    p2.total = 4;

    p2.PersonAddToSelf(p1).PersonAddToSelf(p2).PersonAddToSelf(p1);

    cout << p2.total << endl;
}
```



### 空指针调用成员函数

```C++
#include <iostream>

using namespace std;

class Person {
    public:

    void show() {
        cout << "hello, world" << endl;
    }

    void print() {
        if (this == nullptr) {
            cout << "nullptr" << endl;
            return;
        }
        // 错误，this为空指针，无法访问成员属性
        cout << m_age << endl;
    }

    int m_age;
};

int main() {
    Person *p = nullptr;

    p->show();
    p->print();
}
```

### 常对象和常函数

在类中被const修饰的成员函数称之为常函数，常函数的特点如下：

+ 常函数内不可修改成员属性
+ 成员属性声明时添加了mutable后，在常函数中可以被修改

在类前加const，这个类为常对象。常对象只能调用常函数。

```C++
#include <iostream>

using namespace std;

class Person {
    public:
    void show() const {
        cout << "hello, " << m_sum << endl;
    }
    void show() {
        cout << "hello, " << m_age << endl;
    }

    int m_age;
    int mutable m_sum;
};

int main() {
    Person p1;
    p1.m_age = 100;
    p1.m_sum = 200;
    p1.show();

    const Person p2 = Person();
    // p2.m_age = 100;    // 不允许
    p2.m_sum = 200;
    p2.show();
}
```

## 右值

### 右值引用

使用移动语义`std::move`和右值引用能够避免一些不必要的拷贝，从而提高性能和节省资源。

```C++
#include <vector>
#include <iostream>

// 使用左值引用
void process_left(std::vector<int>& v) {
    // 对 v 进行处理，但并未避免拷贝
    std::cout << "Processing vector of size: " << v.size() << std::endl;
}

// 使用右值引用
void process_right(std::vector<int>&& v) {
    // 直接使用 v，避免了拷贝
    std::cout << "Processing vector of size: " << v.size() << std::endl;
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // 传递左值（拷贝）
    process_left(vec);
    
    // 传递右值（移动）
    process_right(std::move(vec));  // 使用 std::move 让 vec 成为右值
    
    return 0;
}
```

### 完美转发

确保在参数传递的过程中不会丢失参数的左值/右值特性

```C++
#include <iostream>
#include <utility>  // std::forward

template <typename T>
void forward_example(T&& arg) {
    // 完美转发
    process(std::forward<T>(arg));
}

int main() {
    std::vector<int> vec = {1, 2, 3};
    forward_example(vec);  // 传递左值
    forward_example(std::vector<int>{4, 5, 6});  // 传递右值
    return 0;
}
```

### 万能引用

在C++11中，使用`T&&`类型的形参既能绑定左值，又能绑定右值。注意，**只有发生类型推导的时候，T&&才表示万能引用（如模板函数传参就会经过类型推导的过程）**；否则，表示右值引用

```C++
template<typename T>
void func(T&& param) {
    cout << param << endl;
}

int main() {
    int num = 2019;
    // 左值引用
    func(num);
    // 右值引用
    func(2019);
    return 0;
}
```

### 引用折叠

引用折叠是C++11中引入的一个重要特性，主要解决在模板中使用引用时出现的引用类型混乱问题。引用折叠会将多个引用类型合并为一个有效的引用类型。

引用折叠规则如下：

- 左值-左值 T& &
- 左值-右值 T& &&
- 右值-左值 T&& &
- 右值-右值 T&& &&

示例代码（有误）：

```C++
#include <iostream>
#include <type_traits>  // std::is_lvalue_reference

template <typename T>
void check_reference(T&& arg) {
    // 使用 std::is_lvalue_reference 判断是否为左值引用
    std::cout << "Is lvalue reference? " << std::is_lvalue_reference<T>::value << std::endl;
    std::cout << "Is rvalue reference? " << std::is_rvalue_reference<T>::value << std::endl;
}

int main() {
    int x = 10;
    int y = 20;

    // 传递左值
    std::cout << "Passing lvalue:" << std::endl;
    check_reference(x);  // x 是左值

    // 传递右值
    std::cout << "Passing rvalue:" << std::endl;
    check_reference(30);  // 临时数值30是右值

    // 传递右值引用
    std::cout << "Passing rvalue reference:" << std::endl;
    int&& rvalue_ref = 40;
    check_reference(std::move(rvalue_ref));  // std::move() 使 rvalue_ref 成为右值

    return 0;
}
```

输出结果：
```C++
传入左值:
是左值? 1
是右值? 0

传入右值:
是左值? 0
是右值? 0

传入右值引用:
是左值? 0
是右值? 0
```

## 运算符重载

```C++
// operator.h
#include <iostream>

#ifndef _OPERATOR_H_
#define _OPERATOR_H_

class Base
{
    friend std::ostream &operator<<(std::ostream &os, const Base &base);
    friend std::istream &operator>>(std::istream &is, Base &base);

public:
    explicit Base(int i = 0) : m_i(i) {}

    Base &operator=(const Base &base);          // TIPS:只能作为类成员函数进行重载
    void operator()();                          // TIPS:只能作为类成员函数进行重载
    Base &operator[](size_t index);             // TIPS:只能作为类成员函数进行重载
    const Base &operator[](size_t index) const; // TIPS:只能作为类成员函数进行重载
    Base *operator->();                         // TIPS:只能作为类成员函数进行重载
    const Base *operator->() const;             // TIPS:只能作为类成员函数进行重载

    Base &operator++();   // 前自增
    Base &operator--();   // 前自减
    Base operator++(int); // 后自增
    Base operator--(int); // 后自减
    Base operator+(const Base &base);
    Base operator-(const Base &base);
    // Base operator*(const Base &base); // 以下重载大同小异
    // Base operator/(const Base &base);
    // Base operator^(const Base &base);
    // Base operator%(const Base &base);
    // Base operator&(const Base &base);
    // Base operator|(const Base &base);

    explicit operator bool() const;
    bool operator!() const;
    bool operator==(const Base &base) const;
    // bool operator!=(const Base &base) const; // 以下重载大同小异
    // bool operator<(const Base &base) const;
    // bool operator>(const Base &base) const;
    // bool operator&&(const Base &base) const;
    // bool operator||(const Base &base) const;
    // bool operator<=(const Base &base) const;
    // bool operator>=(const Base &base) const;

    Base &operator+=(const Base &base);
    Base &operator-=(const Base &base);
    // Base &operator*=(const Base &base); // 以下重载大同小异
    // Base &operator/=(const Base &base);
    // Base &operator%=(const Base &base);
    // Base &operator^=(const Base &base);
    // Base &operator&=(const Base &base);
    // Base &operator|=(const Base &base);
    // Base &operator>>=(const Base &base);
    // Base &operator<<=(const Base &base);

    Base &operator~();
    Base &operator,(Base &base) const;
    // int operator->*(int Base::*fn)(int, int); // TIPS:用法复杂,用途狭隘

    void *operator new(std::size_t size);
    void *operator new[](std::size_t size);
    void operator delete(void *ptr);
    void operator delete[](void *ptr);

private:
    int m_i;
};
#endif // _OPERATOR_H_
```

```C++
// operator.cpp
#include "operator.h"

std::ostream &operator<<(std::ostream &os, const Base &base)
{
    os << base.m_i;
    return os;
}

std::istream &operator>>(std::istream &is, Base &base)
{
    is >> base.m_i;
    return is;
}

Base &Base::operator=(const Base &base)
{
    if (this == &base)
        return *this;

    this->m_i = base.m_i;
    return *this;
}

void Base::operator()()
{
    std::cout << "自定义函数调用运算符，包括返回值和参数" << std::endl;
}

Base &Base::operator[](size_t index)
{
    return (*this)[index];
}

const Base &Base::operator[](size_t index) const
{
    return (*this)[index];
}

Base *Base::operator->()
{
    return this;
}

const Base *Base::operator->() const
{
    return this;
}

Base &Base::operator++()
{
    this->m_i = this->m_i + 1;
    return *this;
}

Base &Base::operator--()
{
    this->m_i = this->m_i - 1;
    return *this;
}

Base Base::operator++(int)
{
    int tmp = this->m_i;
    this->m_i = this->m_i + 1;
    return Base(tmp);
}

Base Base::operator--(int)
{
    int tmp = this->m_i;
    this->m_i = this->m_i - 1;
    return Base(tmp);
}

Base Base::operator+(const Base &base)
{
    return Base(this->m_i + base.m_i);
}

Base Base::operator-(const Base &base)
{
    return Base(this->m_i - base.m_i);
}

bool Base::operator!() const
{
    return !this->m_i;
}

Base::operator bool() const
{
    return this->m_i != 0 ? 1 : 0;
}

bool Base::operator==(const Base &base) const
{
    return this->m_i == base.m_i;
}

Base &Base::operator+=(const Base &base)
{
    this->m_i += base.m_i;
    return *this;
}

Base &Base::operator-=(const Base &base)
{
    this->m_i -= base.m_i;
    return *this;
}

Base &Base::operator~()
{
    this->m_i = ~this->m_i;
    return *this;
}

Base &Base::operator,(Base &base) const
{
    return base;
}

void *Base::operator new(std::size_t size)
{
    void *ptr = std::malloc(size);
    if (!ptr)
    {
        throw std::bad_alloc();
    }
    return ptr;
}

void *Base::operator new[](std::size_t size)
{
    void *ptr = std::malloc(size);
    if (!ptr)
    {
        throw std::bad_alloc();
    }
    return ptr;
}

void Base::operator delete(void *ptr)
{
    std::free(ptr);
}

void Base::operator delete[](void *ptr)
{
    std::free(ptr);
}

int main()
{
}
```



#### C++20 三路运算符<=>



## 无锁算法和结构，CAS原子操作

**CAS原子操作**

```C++
bool compare_exchange_weak(); // 可能出现伪失败
bool compare_exchange_strong();
```

**乘法计算**

```C++
int fetch_multiply(std::atomic<int> &value, int multiplier) {
	int oldValue = value.load();
	int desired;
	do {
		desired = oldValue * multipiler;
	} while(!value.compare_exchange_strong(oldValue, desired));
	return oldValue;
}
```

在该函数中，如果``oldValue == value``说明``value``没有被修改过，可以将``value``更新为``desired``；如果``oldValue != value``，令``oldValue``的值更新为``value``当前值，重新进行乘法计算。

**无锁堆栈**

```C++
// push
std::shared_ptr<Node> newNode = std::make_shared<Node>(val);
newNode->next = head.load();
while (!head.compare_exchange_strong(newNode->next, newNode));

// pop
std::shared_ptr<Node> oldHead = head.load();
while (oldHead && !head.compare_exchange_strong(oldHead, oldHead->next));
```



## 其他

合取和析取

std::disjunction: 使用 std::disjunction 检查类型

concept和requires

ios::sync_with_stdio(false)

CAS(Compare And Swap): 

````C++
std::atomic<int> value;
int tmp = value.load();  // ?
````

