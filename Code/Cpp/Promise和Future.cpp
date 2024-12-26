#include <future>
#include <iostream>
#include <thread>

using namespace std;

int main()
{
    promise<int> p;
    future<int> f = p.get_future();
    thread t([&p] { p.set_value(10); });
    cout << f.get() << endl;
    t.join();
    return 0;
}