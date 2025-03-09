#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<int> que;

    for (int i = 1; i <= 10; i++) que.push(i);

    cout << "front: " << que.front() << endl;
    cout << "back: " << que.back() << endl;
    cout << "size: " << que.size() << endl;

    que.pop();
    cout << "pop an element after: " << endl;
    cout << "front: " << que.front() << endl;
    cout << "back: " << que.back() << endl;
    cout << "size: " << que.size() << endl;
}