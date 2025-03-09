#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Item {
public:
    Item(int __v = 0) : id_(__v) {}
    int id_;
};

int main() {
    string str;
    fstream fs;
    fs.open("../../Files/output.txt", ios_base::in|ios_base::out|ios_base::binary|ios_base::trunc);

    fs << "hello, world!\nthis is a new line.";
    fs.seekg(15);
    fs >> str;
    cout << str << endl;
    cout << fs.tellg() << endl;
    cout << fs.tellp() << endl;
    fs.close();

}