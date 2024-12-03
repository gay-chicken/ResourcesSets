# Google Test单元测试框架使用教程

## 下载安装

1. 使用Git下载源代码

    ```text
    git clone https://github.com/google/googletest.git
    ```

2. （推荐）新建一个``build``文件夹，这个文件夹用于存放编译生成的文件而不至于到处散落。
3. 在``build``中生成Makefile文件：

    ```text
    cmake ..
    ```

    然后编译、测试和安装：

    ```text
    make
    make test
    make install
    ```

    如果一切顺利，那么gtest已经安装至您的计算机上了。

## 第一个gtest

```cpp
// gtest.cpp
#include <gtest/gtest.h>

int add(int x, int y) {
    return x + y;
}

TEST(TestCase, add_1) {
    EXPECT_EQ(10, add(2, 8));
    EXPECT_EQ(12, add(6, 6));
    EXPECT_EQ(2, add(1, 1));
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

**分析:**

+ ``TEST(TestCase, add_1)``是gtest中用于声明一个测试用例。其中``TestCase``为测试用例名称，``add_1``是测试用例中的测试case名称，一条测试用例可以包含多个case。
+ ``EXPECT_EQ``是测试方法，用于测试是否符合预期。由开发者调用需要测试的接口，填入预期的返回结果后进行判断。
+ ``testing::InitGoogleTest(&argc, argv)``用于初始化gtest。如果没有``main``函数，则需要在编译时加上链接库``-lgtest_main``

**编译运行:**

```bash
g++ gtest.cpp -o gtest -lpthread -lgtest
./gtest
```

**运行截图:**

![gtest运行截图](image\\第一个gtest运行截图.JPG)

## 第一个gmock

```cpp
// gmock.cpp
#include <iostream>
#include <gmock/gmock.h>

using ::testing::Return;

class Foo {
public:
    virtual ~Foo() {};
    virtual int getSize() const = 0;
};

class MockFoo : public Foo {
public:
    MOCK_CONST_METHOD0(getSize, int());
};


int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);

    MockFoo mockFoo;
    EXPECT_CALL(mockFoo, getSize)
        .Times(1)
        .WillOnce(Return(10));
    std::cout << mockFoo.getSize() << std::endl;
    return EXIT_SUCCESS;
}
```

**分析:**

+ 基类的析构函数一定是虚析构的，否则gmock框架无法释放内存。
+ ``MOCK_CONST_METHOD0``指一个参数为0、const的被模拟的方法，类似的还有``MOCK_METHOD1``、``MOCK_METHOD2``、``MOCK_METHODn``等mock方法。
+ ``::testing::InitGoogleMock(&argc, argv)``用于初始化mock框架，如果没有main函数，可以通过编译时加入链接库``-lgmock_main``作为代替。
+ ``EXPECT_CALL``
+ ``Times(1)``代表期望的运行次数，这里期望运行一次。
+ ``WillOnce``
+ ``Return(10)``
+ 使用mock模拟的方法需要调用才能进行模拟，否则会弹出提示
![未被调用的mock方法](image\\mock方法未被调用提示.JPG)

**运行截图:**

![gmock运行截图](image\\第一个gmock运行截图.JPG)