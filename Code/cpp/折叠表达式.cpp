// -std=c++17
// C++17增加了折叠表达式的特性，通过使用逻辑与的短路规则进行条件判断并调用函数
#include <iostream>

template <typename T>
bool func(T t) { return t == 3; }

template <typename ...Ts>
void forbreak(Ts ...ts) {
    ((func(ts) ? false : true) && ...);
}

template <typename ...Ts>
void forbreak_2(Ts ...ts) {
    auto do_something = [](auto t) { std::cout << t << std::endl; };
    ((func(ts) ? false : (do_something(ts), true)) && ...);
}

// int main() {
//     forbreak(1, 2, 3, 4, 5);
// }

int main() {
    forbreak_2(1, 2, 3, 4, 5);
}
