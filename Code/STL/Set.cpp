#include <iostream>
#include <random>
#include <iterator>
#include <set>

using namespace std;

class Student {
public:
    Student(int __id = -1) : uid_(__id) {}
    int uid_;
};

class Compare {
public:
    bool operator()(const Student &s1, const Student &s2) const {
        return s1.uid_ > s2.uid_;
    }
};

int main() {
    int rdr;

    random_device seed;
    ranlux48 engine(seed());
    // mt19937 engine(seed());
    uniform_int_distribution<> distrib(0, 100);

    set<int, greater<int>> set;
    std::set<Student, Compare> stus;
    multiset<int> mulset;

    for (int i = 0; i < 10; ++i) {
        rdr = distrib(engine);
        set.insert(rdr);
        mulset.insert(rdr);
        // stus.insert(Student(rdr));
        stus.emplace(Student(i));
    }

    for (auto &it : stus)
        cout << it.uid_ << " ";
    cout << endl;
}