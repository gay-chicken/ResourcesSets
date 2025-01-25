#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int iarr[] = { 1, 2, 3, 4, 5 };
    vector<int> v1;

    v1.assign(iarr, iarr + 5);
}