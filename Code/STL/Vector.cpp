#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int> &vec, const string str)
{
    cout << str << ": ";
    for (auto &it : vec)
    {
        cout << it << " ";
    }
    cout << endl;
}

int main()
{
    int iarr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> vecA = {1, 2, 3};
    vector<int> vecB(3, 7);

    print(vecA, "vecA");
    print(vecB, "vecB");

    vecA.swap(vecB);
    print(vecA, "vecA"); // vecA = {7, 7, 7};
    print(vecB, "vecB"); // vecB = {1, 2, 3};

    vecA.assign(vecB.begin(), vecB.end());
    print(vecA, "vecA"); // vecA = {1, 2, 3};
    print(vecB, "vecB"); // vecB = {1, 2, 3};

    vecA.assign(iarr, iarr + 8);
    vecA.resize(6);
    print(vecA, "vecA"); // vecA = {1, 2, 3, 4, 5, 6};

    vecA.resize(10, 100);
    print(vecA, "vecA"); // vecA = {1, 2, 3, 4, 5, 6, 100, 100, 100, 100};

    try {
        int val = vecA.at(20); // out of range
    } catch(out_of_range e) {
        cout << e.what() << endl;
    }

    vecA.push_back(123);
    vecA.pop_back();

    vecA.insert(vecA.begin() + 1, 5);
    vecA.insert(vecA.begin() + 4, 3, 7);
    vecA.insert(vecA.end(), vecB.begin(), vecB.end());
    print(vecA, "vecA");
}