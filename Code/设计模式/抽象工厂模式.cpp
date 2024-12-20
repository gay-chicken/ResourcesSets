#include <iostream>

using namespace std;

/*
 *    AbstractProducer: 抽象工厂生成器，用于创建抽象工厂
 *    AbstractFactory: 抽象工厂，用于创建具体工厂
 *    ColorFactory、ShapeFactory: 具体工厂，用于创建具体类
 *    Color、Shape: 抽象接口
 *    Circle、Red: 具体类，这就是最终所需要的产品
 */

class Color {
public:
    virtual void fill() = 0;
};

class Shape {
public:
    virtual void draw() = 0;
};

class AbstractFactory{
public:
    virtual Color* getColor(string chioce) = 0;
    virtual Shape* getShape(string chioce) = 0;
};

class AbstractProducer {
public:
    static AbstractFactory* getFactory(string chioce);
};

class ColorFactory : public AbstractFactory {
public:
    virtual Color* getColor(string chioce) override;
    virtual Shape* getShape(string chioce) override;
};

class ShapeFactory : public AbstractFactory {
public:
    virtual Color* getColor(string chioce) override;
    virtual Shape* getShape(string chioce) override;
};

class Circle : public Shape {
public:
    virtual void draw() override;
};

// Rectangle、Square、......

class Red : public Color {
public:
    virtual void fill() override;
};

// GREEN、BULE、......

void Circle::draw() {
    cout << "Circle" << endl;
}

void Red::fill() {
    cout << "Red" << endl;
}

Color* ColorFactory::getColor(string chioce) {
    if (chioce == "Red") return new Red();
    else return nullptr;
}

Shape* ColorFactory::getShape(string chioce) {
    return nullptr;
}

Color* ShapeFactory::getColor(string chioce) {
    return nullptr;
}

Shape* ShapeFactory::getShape(string chioce) {
    if (chioce == "Circle") return new Circle();
    else return nullptr;
}

AbstractFactory* AbstractProducer::getFactory(string chioce) {
        if (chioce == "Shape") return new ShapeFactory();
        else if (chioce == "Color") return new ColorFactory();
        else return nullptr;
    }

int main() {
    AbstractFactory* shapeFactory = AbstractProducer::getFactory("Shape");

    Shape* shape = shapeFactory->getShape("Circle");
    shape->draw();

    AbstractFactory* colorFactory = AbstractProducer::getFactory("Color");

    Color* color = colorFactory->getColor("Red");
    color->fill();
}