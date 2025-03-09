#include <stack>
#include <vector>
#include <iostream>

using namespace std;

/**
 * 单调栈：
 *      1. 假设当前进栈元素为 x，如果 x 比栈顶元素小，则直接入栈。
 *      2. 否则从栈顶开始遍历栈中元素，把小于 x 或者等于 x 的元素弹出栈，直到遇到一个大于 x 的元素
 *         为止，然后再把 x 压入栈中。
 */

template <template<typename> typename Cmp = greater, typename T>
vector<T> get_next_prev(vector<T> &arr, bool prev = false) {
    int n = arr.size();
    vector<T> res(n);
    stack<T> st;
    for (int i = prev ? 0 : n - 1; prev ? i < n : i >= 0; prev ? ++i : --i) {
        while (!st.empty() && !Cmp<T>()(arr[st.top()], arr[i])) st.pop();
        res[i] = st.empty() ? (prev ? -1 : n) : st.top();
        st.push(i);
    }
    return res;
}

int main() {
    vector<int> iarr = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> res = get_next_prev(iarr);

    for (const auto& it : res)
        cout << it << " ";
    cout << endl;

    iarr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    res = get_next_prev(iarr);
    for (const auto& it : res)
        cout << it << " ";
    cout << endl;

    iarr = {3, 2, 1, 6, 5, 4, 9, 8, 7};
    res = get_next_prev(iarr);
    for (const auto& it : res)
        cout << it << " ";
    cout << endl;
}