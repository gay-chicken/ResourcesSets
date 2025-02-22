#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

string read_file_using_tellg_and_read(const filesystem::path& fileName) {
    ifstream fin(fileName, ios::binary);
    fin.exceptions(ios::failbit | ios::badbit);

    auto beginPos = fin.tellg();
    fin.seekg(0, ios::end);
    auto endPos = fin.tellg();
    fin.seekg(beginPos);

    string content;
    content.resize(endPos - beginPos);
    fin.read(content.data(), static_cast<streamsize>(content.size()));
    return content;
}