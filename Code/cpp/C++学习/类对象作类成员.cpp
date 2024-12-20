#include <iostream>
#include <string>

using namespace std;

class Teather {
    public:
    Teather(string n) : name(n) {
        cout << "Teather" << endl;
    }
    string name;
};

class Student {
    public:
    Student(string n) : name(n) {
        cout << "Student" << endl;
    }
    string name;
    int age;
};

class Class {
    public:
    Class(string t_name, string s_name) : teather(t_name), student(s_name) {
        cout << "Class" << endl;
    }
    Teather teather;
    Student student;
};

int main() {
    Class c("老刘", "张三");    // 调用顺序：先 Teather, Student 后 Class
    cout << c.teather.name << c.student.name << endl;
}