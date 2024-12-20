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