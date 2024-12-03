#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Packing {
public:
    virtual string pack() = 0;
};

class Item {
public:
    virtual string name() = 0;
    virtual Packing* packing() = 0;
    virtual float price() = 0;
};

class Meal {
public:
    void addItem(Item* item);
    float getCost();
    void showItems();
private:
    vector<Item*> items;
};

class MealBuilder {
public:
    Meal* preapareVegBurger();
    Meal* preapareNonBurger();
};

class Wrapper : public Packing {
public:
    virtual string pack() override;
};

class Bottle : public Packing {
public:
    virtual string pack() override;
};

class Burger : public Item{
public:
    virtual Packing* packing() override;
};

class ColdDrink : public Item{
public:
    virtual Packing* packing() override;
};

class VegBurger : public Burger {
public:
    virtual string name() override;
    virtual float price() override;
};

class ChickenBurger : public Burger {
public:
    virtual string name() override;
    virtual float price() override;
};

class Pepsi : public ColdDrink {
public:
    virtual string name() override;
    virtual float price() override;
};

class Coke : public ColdDrink {
public:
    virtual string name() override;
    virtual float price() override;
};

Meal* MealBuilder::preapareVegBurger() {
    Meal* meal = new Meal();
    meal->addItem(new VegBurger());
    meal->addItem(new Coke());
    return meal;
}

Meal* MealBuilder::preapareNonBurger() {
    Meal* meal = new Meal();
    meal->addItem(new ChickenBurger());
    meal->addItem(new Pepsi());
    return meal;
}

void Meal::addItem(Item* item) {
    items.push_back(item);
}

float Meal::getCost() {
    float cost = 0;
    for (auto it : items) {
        cost += it->price();
    }
    return cost;
}

void Meal::showItems() {
    for (auto it : items) {
        cout << "Item: " << it->name()
             << ", Packing: " << it->packing()->pack()
             << ", Price: " << it->price() << endl;
    }
}

string Wrapper::pack() {
    return "Wrapper";
}

string Bottle::pack() {
    return "Bottle";
}

Packing* Burger::packing() {
    return new Wrapper();
}

Packing* ColdDrink::packing() {
    return new Bottle();
}

string VegBurger::name() {
    return "VegBurger";
}

float VegBurger::price() {
    return 15.3;
}

string ChickenBurger::name() {
    return "ChickenBurger";
}

float ChickenBurger::price() {
    return 25.4;
}

string Pepsi::name() {
    return "Pepsi";
}

float Pepsi::price() {
    return 72.4;
}

string Coke::name() {
    return "Coke";
}

float Coke::price() {
    return 3.5;
}

int main() {
    MealBuilder* builder = new MealBuilder();
    Meal* meal = builder->preapareNonBurger();

    meal->showItems();
    cout << meal->getCost();
}