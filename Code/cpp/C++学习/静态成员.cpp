#include <iostream>

using namespace std;

class Person {
    public:

    static int total;
    static void handle(int x = total) {
        total = x;
        cout << total << endl;
    }
};

int Person::total = 100;

int main() {
    Person::handle();
    Person::handle(20);
}