#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> listA;

    listA.push_front(0);
    listA.push_back(-1);
    listA.push_back(2);
    listA.push_front(9);
    listA.pop_back();

    for (auto &it : listA)
        cout << it << " ";
    cout << endl;

    cout << listA.front() << endl;
    cout << listA.front() << endl;

    for (auto &it : listA)
        cout << it << " ";
    cout << endl;
}