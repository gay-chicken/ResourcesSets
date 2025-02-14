#include <iostream>
#include <atomic>

using namespace std;

struct A { int a[100]; };
struct B { char c[8]; };

int main() {
    cout << "atomic<A> is free?" << boolalpha << atomic<A>{}.is_lock_free() << endl;
    cout << "atomic<B> is free?" << boolalpha << atomic<B>{}.is_lock_free() << endl;
}