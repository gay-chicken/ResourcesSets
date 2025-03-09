#include <iostream>
#include <deque>

using namespace std;

int main() {
    deque<int> deq;

    for (int i = 0; i < 10; i++) deq.push_back(i);

    cout << deq.at(0) << endl;

}