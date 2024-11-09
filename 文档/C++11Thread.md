# C++11 线程池

## 一、线程库的基本使用

### thread()

**示例代码**

```C++
#include <iostream>
#include <thread>
#include <string>

void f1(std::string s) {
    std::cout << s << std::endl;
}

int main() {
    std::thread t1(f1, "thread");
    
    // wait thread finished.
    t1.join();
    
    return 0;
}
```

thread对象通过`thread (Fn&& fn, Args&&... args)`创建出一个新的线程，通过传递执行的函数`fn`及其fn的参数`args`即可成功开辟新线程。

此时的程序还不能运行，因为线程与主进程的执行顺序不同步，有可能主进程已经运行结束了，线程还在运行，这就导致了**Aborted (core dumped)**报错。要解决该问题，需要使用`join()`阻塞主进程，等待线程执行完毕后再进行退出。

### joinable()

```C++
bool joinable() const noexcept;
```

检测线程能否调用`join()`

**示例代码**

```C++
#include <iostream>       // std::cout
#include <thread>         // std::thread

void mythread()
{
  // do stuff...
}

int main()
{
  std::thread foo;
  std::thread bar(mythread);

  std::cout << "joinable() ==> :\n" << std::boolalpha;
  std::cout << "foo: " << foo.joinable() << '\n';
  std::cout << "bar: " << bar.joinable() << '\n';

  if (foo.joinable()) foo.join();
  if (bar.joinable()) bar.join();

  std::cout << "joinable() ==> :\n" << std::boolalpha;
  std::cout << "foo: " << foo.joinable() << '\n';
  std::cout << "bar: " << bar.joinable() << '\n';

  return 0;
}
```

**运行结果**

```
joinable() ==> :
foo: false
bar: true
joinable() ==> :
foo: false
bar: false
```



### detach()

```C++
void detach();
```

将该对象表示的线程从调用线程分离，使得它们可以独立执行。

两个线程继续运行，彼此之间不进行阻塞或同步。请注意，当任意一个线程结束执行时，它的资源将被释放。

调用此函数后，线程对象变为不可连接（non-joinable），并且可以安全地销毁。

**示例代码**

```C++
#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

void pause_thread(int n)
{
  std::this_thread::sleep_for (std::chrono::seconds(n));
  std::cout << "暂停 " << n << " 秒结束.\n";
}

int main()
{
  std::cout << "创建并分离3个线程...\n";
  std::thread (pause_thread,1).detach();
  std::thread (pause_thread,2).detach();
  std::thread (pause_thread,3).detach();
  std::cout << "线程创建完毕.\n";

  std::cout << "(主线程等待5秒)\n";
  // 给予分离的线程运行结束的时间 (并不能保证!):
  pause_thread(5);
  return 0;
}
```

**运行结果**

```
创建并分离3个线程...
线程创建完毕.
(主线程等待5秒)
暂停 1 秒结束.
暂停 2 秒结束.
暂停 3 秒结束.
暂停 5 秒结束.
```

### 常见线程错误

#### 1、传递临时变量问题

**示例代码**

```C++
#include <iostream>
#include <thread>

void addition_thread(int &n)
{
    n += 1;
}

int main()
{
    int x = 0;
    std::thread t1(addition_thread, x);
    t1.join();
    return 0;
}
```

**问题情况**

```
/usr/include/c++/10/thread: In instantiation of ‘std::thread::thread(_Callable&&, _Args&& ...) [with _Callable = void (&)(int&); _Args = {int}; <template-parameter-1-3> = void]’:
0_test.cpp:11:38:   required from here
/usr/include/c++/10/thread:136:44: error: static assertion failed: std::thread arguments must be invocable after conversion to rvalues
  136 |           typename decay<_Args>::type...>::value,
      |  
```

**问题原因**

`std::thread` 需要确保传递给线程函数的所有参数在转化为右值后仍然可以正确调用，而引用类型的参数不能直接按值传递，因为它期望传递的是可复制的对象。`x` 是一个局部变量，它被传递给一个引用类型的函数，这导致了线程无法处理这个参数。

**解决方案**

将代码

```c++
std::thread t1(addition_thread, x);
```

修改为

```C++
std::thread t1(addition_thread, std::ref(x));
```

即可正确运行

#### 2、传递指针或引用指向局部变量问题

**示例代码**

```C++
#include <iostream>
#include <thread>
#include <chrono>

std::thread t1;
void foo(int &n)
{
    n += 1;
}

void test()
{
    int x = 3;
    t1 = std::thread(foo, std::ref(x));
}

int main()
{
    test();
    t1.join();
    return 0;
}
```

**问题情况**

该程序编译正确，在运行时可能会报错。

**问题原因**

`test` 函数结束后，局部变量 `x` 会被销毁。线程 `t1` 仍然会在后台执行，但它可能会尝试访问已被销毁的 `x`，这会导致未定义行为。

由于线程是异步执行的，`t1` 可能在 `test` 函数返回后还没有结束，这样就会尝试访问一个已经销毁的局部变量 `x`，这会导致访问非法内存。

**解决方案**

方法1、将 `x` 作为全局或局部静态变量，确保 `x` 在 `t1` 执行期间仍然有效。

方法2、将 x 传递给线程，并确保线程在 main 函数结束前执行完毕

```C++
#include <iostream>
#include <thread>
#include <chrono>

void foo(int &n)
{
    n += 1;
}

void test(int &x)
{
    std::thread t1(foo, std::ref(x));  // 将 x 作为引用传递给线程
    t1.join();  // 等待线程执行完毕
}

int main()
{
    int x = 3;
    test(x);  // 在 test 函数中传递 x
    std::cout << "x = " << x << std::endl;  // 输出修改后的 x
    return 0;
}
```

#### 3、悬挂指针问题

**示例代码**

```C++
#include <iostream>
#include <thread>
#include <chrono>

void foo(int *n)
{
    std::cout << *n << std::endl;
}

int main()
{
    int *x = new int(100);
    std::thread t1(foo, x);
    delete x;
    t1.join();
    return 0;
}
```

**问题情况**

预期输出：
```
100
```

运行输出：
```
0
```

**问题原因**

在线程 `t1` 还在运行的时候，就释放了 `x` 所指向的内存，这样线程访问这个内存时会导致未定义行为，常见的表现就是程序崩溃或者输出垃圾数据。因为 `delete x` 会销毁 `x` 指向的内存，但 `t1` 仍然在访问这个已经被销毁的内存位置。

**解决方案**

方案1、不要在删除指针之前让线程访问它

```C++
#include <iostream>
#include <thread>
#include <chrono>

void foo(int *n)
{
    std::cout << *n << std::endl;
}

int main()
{
    int *x = new int(100);
    std::thread t1(foo, x);
    t1.join();  // 等待线程完成
    delete x;  // 删除内存，确保线程使用完毕后再释放
    return 0;
}
```

方案2、使用 `std::shared_ptr` 或 `std::unique_ptr` 来自动管理内存

```C++
#include <iostream>
#include <thread>
#include <memory>

void foo(std::shared_ptr<int> n)
{
    std::cout << *n << std::endl;
}

int main()
{
    std::shared_ptr<int> x = std::make_shared<int>(100);
    std::thread t1(foo, x);
    t1.join();  // 等待线程完成，内存会在 x 离开作用域后自动释放
    return 0;
}
```

