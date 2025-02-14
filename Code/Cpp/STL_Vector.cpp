#include <vector>
#include <iostream>

using namespace std;

int main() {
    int iarr[] = {1, 2, 3, 4, 5};
    vector<int> vecInt;
    vector<int> vecConPtr(iarr, iarr+5);
    vector<int> vecConInt(5, 6);
    vector<int> vecConCpy(vecConPtr);

    for (int i = 0; i < 5; i++) {
        cout << vecConInt[i] << " ";
    }
    cout << endl;

    vecConPtr.assign(iarr, iarr+5);
    for (int i = 0; i < vecConPtr.size(); i++) {
        cout << vecConPtr[i] << " ";
    }
    cout << endl;
}