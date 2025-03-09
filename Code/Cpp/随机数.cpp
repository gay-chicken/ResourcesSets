#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

#define COUNT 10000

using namespace std;

int main() {
    uniform_int_distribution<int> uniform_engine(0, 100);    // 均匀分布
    linear_congruential_engine<std::uint_fast32_t, 48271, 0, 2147483647>/*minstd_rand*/ linear_engine;  // 线性分布 (ax+c) mod m
    std::mersenne_twister_engine<std::uint_fast32_t,
                             32, 624, 397, 31,
                             0x9908b0df, 11,
                             0xffffffff, 7,
                             0x9d2c5680, 15,
                             0xefc60000, 18, 1812433253>/*mt19937*/ mersenne_engine;   // 梅森扭转
    std::subtract_with_carry_engine<std::uint_fast64_t, 48, 5, 12>/*ranlux48_base*/ subtract_engine;
    std::shuffle_order_engine<std::minstd_rand0, 256> shuffle_adaptor;
    mt19937 seed;

    ofstream ofs;

    ofs.open("../../Files/uniform.txt");
    if (!ofs.is_open()) std::abort();
    for (int i = 0; i < COUNT; ++i) {
        ofs << uniform_engine(seed) << ", ";
    }
    ofs.close();

    ofs.open("../../Files/minstd_rand.txt");
    for (int i = 0; i < COUNT; ++i) {
        ofs << linear_engine() << ", ";
    }
    ofs.close();

    ofs.open("../../Files/mt19937.txt");
    for (int i = 0; i < COUNT; ++i) {
        ofs << mersenne_engine() << ", ";
    }
    ofs.close();

    ofs.open("../../Files/ranlux48_base.txt");
    for (int i = 0; i < COUNT; ++i) {
        ofs << subtract_engine() << ", ";
    }
    ofs.close();

    ofs.open("../../Files/shuffle.txt");
    for (int i = 0; i < COUNT; ++i) {
        ofs << shuffle_adaptor() << ", ";
    }
    ofs.close();
}