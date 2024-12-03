#include <iostream>

using namespace std;

// 1.递归方式展开变参列表
// 1.1 模板优于无参
void show() {
    cout << "end";
}

// 1.2 具体优于模板
void show(int) {
    cout << "int";
}

// 1.3 模板优于类型转换
void show(float) {
    cout << "float";
}

template<class T>
void show(const T& value) {
    cout << "template";
}

template<class T, class... Args>
void show(const Args& ...values) {
    cout << sizeof...(values) << "\t";
    cout << first << endl;
    show(values...);
}

int main() {
    int* p = new int(10);
    show(1,"hi",3.14,'a',3.4);
}