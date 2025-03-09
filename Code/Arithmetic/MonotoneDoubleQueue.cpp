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

template <typename T, template<typename> typename Cmp = greater>
class mono_deque : public deque<pair<int, T>> {
public:
    mono_deque& push(int idx, const T &x) {
        while (!this->empty() && !Cmp<T>()(this->back().second, x)) this->pop_back();
        this->push_back({idx, x});
        return *this;
    }
    mono_deque& shrink_to(int idx) {
        while (!this->empty() && this->front() <= idx) this->pop_front();
        return *this;
    }
    T get_extremun() { return this->front().second; }
};

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
    vector<int> arr = {1, 4, 7, 2, 5, 8, 3, 6, 9};
    vector<int> window_max(arr.size());
    mono_deque<int> dec_q;

}