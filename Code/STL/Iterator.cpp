#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<int> vecA = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int>::iterator iter;
    iter = vecA.begin() + 3;
    cout << *iter << endl;

    // 迭代器失效：插入元素、删除元素
    iter = vecA.insert(iter, 0);
    cout << *iter << endl;
    iter = vecA.erase(iter);
    cout << *iter << endl;
}