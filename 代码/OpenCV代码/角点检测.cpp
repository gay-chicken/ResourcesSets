#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("./image/5.jpg");
    if (src.empty())
    {
        cerr << "Not found image." << endl;
        return -1;
    }

    Mat gray;
    Mat dst = src.clone();
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // ========== Harris or Shi-Tomasi角点检测 ==========
    vector<Point> cor_keys;
    int maxCorners = 0;             // 角点最大数量，0代表无限制
    double qualityLevel = 0.3;     // 小于1.0的正数，一般取值在0.01~0.1之间
    double minDistance = 10;       // 忽略在此距离内的角点
    InputArray mask = noArray();    // 掩码
    int blockSize = 3;              // 检测窗口大小
    bool useHarrisDetector = false; // 是否使用Harris算法，否则使用Shi-Tomasi算法
    double k = 0.04;                // 使用Harris算法时，所使用到的权重系数k
    goodFeaturesToTrack(gray, cor_keys, maxCorners, qualityLevel, minDistance, mask, blockSize, useHarrisDetector, k);

    for (const auto &it : cor_keys) {
        circle(dst, it, 5, Scalar(0, 0, 255), -1, LINE_AA);
    }
    imwrite("./out/Shi-Tomasi.jpg", dst);
}