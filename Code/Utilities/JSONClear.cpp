// compiler: g++ JSONClear.cpp -o tool

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>

/**
 * tool -o output.txt input.txt
 * tool input.txt -o output.txt
 */
void usage() {
    std::cout << "error: missing parameter." << std::endl;
    std::cout << "usage: tool input_file output_file" << std::endl;
    std::exit(1);
}

int main(int argc, char** argv) {
    if (argc != 3) usage();
    if (!std::filesystem::exists(argv[1])) return 1;

    std::ifstream ifs(argv[1]);
    std::ofstream ofs(argv[2]);
    std::string buff;
    std::string comm;
    size_t pos;
    while (!ifs.eof()) {
        std::getline(ifs, buff);
        pos = buff.find("user");
        if (pos != std::string::npos) {
            comm = buff.substr(pos + 8);
            comm.pop_back();
            comm.pop_back();
            comm.push_back(':');

            std::getline(ifs, buff);
            pos = buff.find("body");
            if (pos != std::string::npos) {
                comm += buff.substr(pos + 6);
                comm.pop_back();
                while (1) {
                    pos = comm.find("\\n");
                    if (pos == std::string::npos) break;
                    comm.replace(pos, 2, "    ");
                }
                comm.push_back('\n');
                ofs << comm;
            }
        }
    }

    ifs.close();
    ofs.close();
}
