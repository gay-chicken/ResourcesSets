#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> deqA = {1, 2, 3, 4, 5};
    deqA.push_front(0);
    deqA.push_back(-1);

    for (auto &it : deqA)
        cout << it << " ";
    cout << endl;

}