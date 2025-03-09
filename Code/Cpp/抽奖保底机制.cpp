#include <iostream>
#include <random>
#include <map>
#include <functional>

/*测试代码使用constexpr定义，业务代码从csv读取。*/
constexpr static int BestPrize = 1;
constexpr static int FirstPrize = 50;
constexpr static int SecondPrize = 85;
constexpr static int ThirdPrize = 120;
constexpr static int ConsolationPrize = 200;

constexpr static int Counter = 100;             // 保底次数
constexpr static int MinRange = 0;
constexpr static int MaxRange = 1000;

class Lottery {
public:
    Lottery() : prob_(BestPrize), seed_(std::random_device{}()), engine_(MinRange, MaxRange) {}

    bool run() {
        static int count = 1;
        if (count == Counter) {
            count = 1;
            prob_ = BestPrize;
            return true;
        }
        count++;

        int once = engine_(seed_);
        if (once < prob_) {
            std::printf("random: %d, prob_: %d\n", once, prob_);
            count = 1;
            prob_ = BestPrize;
            return true;
        } else if (prob_ < 20) {
            prob_++;
        }
        return false;
    }
private:
    int prob_;      // 获奖概率

    std::mt19937 seed_;
    std::uniform_int_distribution<int> engine_;
};

int main() {
    Lottery lot;

    for (int i = 0; i < 100; i++) {
        bool aim = lot.run();
        // if (aim) std::cout << i << " ";
    }
}