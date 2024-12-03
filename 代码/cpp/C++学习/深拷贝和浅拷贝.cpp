#include <iostream>
#include <string>

class Apple {
    public:
    Apple(int c = 0, int b = 0) {
        count = c;
        brand = new int(b);
    }
    Apple(const Apple& p) {
        count = p.count;
        brand = new int(*p.brand);
    }
    ~Apple() {
        if (brand != nullptr) {
            delete brand;
            brand = nullptr;
        }
    }

    int count;
    int* brand;
};

void test() {
    Apple app1(10, 4);
    Apple app2 = app1;

    std::cout << app1.count << "    " << app1.brand << std::endl;
    std::cout << app2.count << "    " << app2.brand << std::endl;
}

int main() {
    test();
}