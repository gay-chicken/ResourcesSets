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