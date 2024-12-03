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

## 二、锁

### std::mutex

```C++
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

int x = 0;
std::mutex mtx;

/*
    real    0m0.008s
    user    0m0.008s
    sys     0m0.001s
*/
void low()
{
    mtx.lock();
    for (int i = 0; i < 1000000; i++)
    {
        x++;
    }
    mtx.unlock();
}

/*
    real    0m0.109s
    user    0m0.093s
    sys     0m0.104s
*/
void high()
{
    for (int i = 0; i < 1000000; i++)
    {
        mtx.lock();

        x++;
        mtx.unlock();
    }
}

int main()
{
    std::thread t1(low);
    std::thread t2(low);
    t1.join();
    t2.join();
    std::cout << x << std::endl;
    return 0;
}
```



### std::lock_guard

```C++
/*
lock_guard:
    当构造函数被调用时，会自动加锁
    当析构函数被调用时，会自动解锁
    lock_guard对象不可复制和移动，只能在局部作用域中使用
*/
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
int shared_data = 0;

void f1()
{
    std::lock_guard<std::mutex> lg(mtx);
    for (int i = 0; i < 1000000; i++)
    {
        shared_data++;
    }
}

void f2()
{
    mtx.lock();

    // 已经加过锁了，无需再次加锁
    std::lock_guard<std::mutex> lg(mtx, std::adopt_lock);
    for (int i = 0; i < 1000000; i++)
    {
        shared_data++;
    }
}

int main()
{
    std::thread t1(f1);
    std::thread t2(f1);
    t1.join();
    t2.join();
    std::cout << "over" << std::endl;
    return 0;
}
```



### std::unique_lock

```C++
/*
std::unique_lock:
    更灵活的锁管理
    具有延时加锁、定时加锁、加锁尝试
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex mtx;
std::timed_mutex tmx;
int shared_data = 0;

void f1()
{
    std::unique_lock<std::mutex> lg(mtx);
    for (int i = 0; i < 1000000; i++)
    {
        shared_data++;
    }
}

void f2()
{
    std::unique_lock<std::timed_mutex> lg(tmx, std::defer_lock);
    // 获取不到锁直接放弃后续执行
    if (!lg.try_lock_for(std::chrono::milliseconds(50))) return;
    
    for (int i = 0; i < 1000000; i++)
    {
        shared_data++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main()
{
    std::thread t1(f2);
    std::thread t2(f2);
    t1.join();
    t2.join();
    std::cout << shared_data << std::endl;
    std::cout << "over" << std::endl;
    return 0;
}
```

### std::call_once

`std::call_once`保证在多线程中只有一个线程能够执行。

`std::call_once`只能在线程下运行，在main中调用会报错。

```C++
#include <iostream>
#include <thread>
#include <mutex>

class Log
{
public:
    Log() {}
    Log(const Log &) = delete;
    Log &operator=(const Log &) = delete;

    // 懒汉单例模式
    static Log &GetInstance()
    {
        static Log log;
        return log;
    }

    void Print(std::string msg)
    {
        std::cout << __TIME__ << ": " << msg << std::endl;
    }
};

void expection()
{
    Log::GetInstance().Print("发生错误");
}

void call() {
    static std::once_flag once;
    std::call_once(once, expection);
}

int main()
{
    std::thread t1(call);
    std::thread t2(call);
    t1.join();
    t2.join();
    return 0;
}
```

### std::condition_variable

生产者-消费者模型：
```C++
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <queue>
#include <condition_variable>
#include <chrono>

using namespace std;

queue<int> tasks;
mutex mtx;
condition_variable mess;

void Product() {
    for (int i = 0; i < 100; i++) {
        unique_lock<mutex> lock(mtx);
        tasks.push(i);
        mess.notify_one();
        cout << "Product: " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Consumer() {
    while(true) {
        unique_lock<mutex> lock(mtx);

        mess.wait(lock, []() -> bool {
            return !tasks.empty();
        });
        int value = tasks.front();
        tasks.pop();
        cout << "Consumer: " << value << endl;
        this_thread::sleep_for(chrono::milliseconds(5));
    }
}

int main() {
    thread t1(Product);
    thread t2(Consumer);
    t1.join();
    t2.join();
    cout << "over" << endl;
    return 0;
}
```



### std::barrier

`std::barrier`是C++20中引入的一项用于同步线程任务的特性。它允许多个线程在同一个特定的同步点上相互等待，简单来说就是在线程任务中设置一个阻塞点，所有到达该点的线程都会被阻塞，直到所有线程都到达该任务点才会继续往下执行。

```C++
#include <barrier>
#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

barrier b(2);

void foo() {
    auto tid = this_thread::get_id();
    cout << "thread " << tid << " enter" <<  << endl;
    b.arrive_and_wait();
    cout << "thread " << tid << " out" <<  << endl;
}

int main() {
    thread t1(foo);
    thread t2(foo);
    cout << "over" << endl;
    return 0;
}
```

