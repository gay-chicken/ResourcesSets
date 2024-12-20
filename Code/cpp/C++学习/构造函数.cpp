#include <iostream>

class Person {
    public:
    Person() {
        std::cout << "Person()" << std::endl;
    }
    Person(int) {
        std::cout << "Person(int)" << std::endl;
    }
    Person(const Person& p) {
        std::cout << "Person(const Person&)" << std::endl;
    }
};

int main() {
    Person p1;
    Person p2;
    p2 = p1;
}