#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> stk;
    stk.emplace(10);
    stk.emplace(20);
    stk.emplace(30);

    cout << "size: " << stk.size() << endl;
}