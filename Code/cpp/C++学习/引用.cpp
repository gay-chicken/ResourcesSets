#include <iostream>

void show(int&) {
     std::cout << "int&" << std::endl;
}

void show(int) {
    std::cout << "int" << std::endl;
}

int main() {
    show(10);
}