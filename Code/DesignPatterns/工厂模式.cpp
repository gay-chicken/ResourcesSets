#include <iostream>

using namespace std;

class Money {
public:
    virtual void pay() = 0;
};

class USD : public Money {
public:
    virtual void pay();
};

class CNY : public Money {
public:
    virtual void pay();
};

class MoneyFactory {
public:
    Money* getMoney(int idx);
};

void USD::pay() {
    cout << "Dollar" << endl;
}

void CNY::pay() {
    cout << "Renminbi" << endl;
}

Money* MoneyFactory::getMoney(int idx) {
    switch(idx) {
        case 0: return new USD();
        case 1: return new CNY();
        default: return nullptr;
    }
}

int main() {
    MoneyFactory factory;

    Money *money = factory.getMoney(1);
    money->pay();

    factory.getMoney(0)->pay();
}