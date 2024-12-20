#include <iostream>
#include <list>

using namespace std;

class Person {
    public:
    Person& PersonAddToSelf(const Person& p) {
        this->total += p.total;
        return *this;
    }

    int total;
};

int main() {

    Person p1, p2;
    p1.total = 10;
    p2.total = 4;

    p2.PersonAddToSelf(p1).PersonAddToSelf(p2).PersonAddToSelf(p1);

    cout << p2.total << endl;
}