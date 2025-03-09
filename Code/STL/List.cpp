#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> listA = {10, 20, 30};
    list<int>::iterator iterA = listA.begin();
    iterA++;

    listA.push_front(0);
    listA.push_back(-1);
    listA.pop_back();
    listA.pop_front();

    listA.front() = 10;
    listA.back() = -100;

    list<int> listB(listA.begin(), iterA);    // listB = {10}
    listB.assign(listA.begin(), listA.end());   // listB = {10, 20, -100}
    listB.resize(5, 2);    // listB = {10, 20, -100, 2, 2}
    listB.resize(2);        // listB = {10, 20}

    iterA = listA.insert(iterA, 5);    // listA = {10, 5, 20, -100}
    listA.insert(iterA, 3, 11);     // listA = {10, 11, 11, 11, 5, 20, -100}
    listA.insert(iterA, listB.begin(), listB.end());    // listA = {10, 11, 11, 11, 10, 20, 5, 20, -100}

    listA.remove(11);   // listA = {10, 10, 20, 5(iterA), 20, -100}
    iterA = listA.erase(iterA); // listA = {10, 10, 20, 20(iterA), -100}
    iterA = listA.erase(iterA, listA.end());    // listA = {10, 10, 20, ???(iterA)}
    listA.clear();  // listA = {}

    listA.assign(5, 11);
    listA.push_back(10);
    listA.push_back(20);
    listA.push_front(-10);
    for (auto iter = listA.begin(); iter != listA.end(); iter = (*iter == 11) ? listA.erase(iter) : ++iter);
}