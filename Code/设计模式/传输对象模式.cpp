#include <iostream>
#include <vector>

using namespace std;

class StudentVO {
    public:
        StudentVO(string name, int age);
        string getName() const;
        int getAge() const;
        void setName(string name);
        void setAge(int age);

    private:
        int m_age;
        string m_name;
};

StudentVO::StudentVO(string name, int age) {
    m_age = age;
    m_name = name;
}

string StudentVO::getName() const {
    return m_name;
}

int StudentVO::getAge() const {
    return m_age;
}

void StudentVO::setName(string name) {
    m_name = name;
}

void StudentVO::setAge(int age) {
    m_age = age;
}

class StudentBO {
public:
    StudentBO();
    StudentVO* getStudent(int index);
    void Show() const;
private:
    // 将列表当作一个数据库
    vector<StudentVO*> students;
};

StudentBO::StudentBO() {
        students.push_back(new StudentVO("lihua", 21));
        students.push_back(new StudentVO("zhangsan", 23));
}

void StudentBO::Show() const {
    for (auto it : students) {
        cout << "Name: " << it->getName() << ", Age: " << it->getAge() << endl;
    }
}

StudentVO* StudentBO::getStudent(int index) {
    auto it = students.begin() + index;
    return *it;
}

int main() {
    StudentBO businessObject;

    businessObject.Show();
    StudentVO *student = businessObject.getStudent(1);

    cout << "-->Name: " << student->getName() << ", Age: " << student->getAge() << endl;
}