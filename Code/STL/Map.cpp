#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<int, string> maps;

    // insert
    maps.insert(pair<int, string>(1, "zhangsan"));
    maps.insert(map<int, string>::value_type(2, "liusi"));
    maps[3] = "wangwu"; // 覆盖更新

    // getting
    string name = maps[2];  // 如果不存在，会创建键值对 key:""
    map<int, string>::iterator it = maps.find(2);   // pair<int, string>
    string at = maps.at(3); // if not found the key, throw out of range expetion.

    cout << (name.empty() ? "Not found key." : name) << endl;
    cout << (it == maps.end() ? "Not found key." : (*it).second) << endl;
}