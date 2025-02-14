#include <iostream>

consteval int square(int n) {
    return n * n;
}

int main() {
    std::cout << square(5);

}