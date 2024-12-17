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
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // ========== Harris or Shi-Tomasi角点检测 ==========
    vector<Point> keys;
    int maxCorners = 0;             // 角点最大数量，0代表无限制
    double qualityLevel = 0.3;     // 小于1.0的正数，一般取值在0.01~0.1之间
    double minDistance = 10;       // 忽略在此距离内的角点
    InputArray mask = noArray();    // 掩码
    int blockSize = 3;              // 检测窗口大小
    bool useHarrisDetector = false; // 是否使用Harris算法，否则使用Shi-Tomasi算法
    double k = 0.04;                // 使用Harris算法时，所使用到的权重系数k
    goodFeaturesToTrack(gray, keys, maxCorners, qualityLevel, minDistance, mask, blockSize, useHarrisDetector, k);

    for (const auto &it : keys) {
        circle(src, it, 5, Scalar(0, 0, 255), -1, LINE_AA);
    }
    imwrite("./out/Shi-Tomasi.jpg", src);

    // ========== SIFT特征点检测 ==========
    Mat in_1 = imread("./image/2.jpg");
    Mat in_2 = imread("./image/3.jpg");
    Mat gr_1, gr_2;
    cvtColor(in_1, gr_1, COLOR_BGR2GRAY);
    cvtColor(in_2, gr_2, COLOR_BGR2GRAY);
    auto sift = SIFT::create();
    vector<KeyPoint> kp1, kp2;
    Mat d1, d2;
    sift->detectAndCompute(gr_1, noArray(), kp1, d1);
    sift->detectAndCompute(gr_2, noArray(), kp2, d2);
    drawKeypoints(in_1, kp1, in_1, Scalar(0, 255, 0));
    imwrite("./out/SIFT_keypoint.jpg", in_1);

    // ========== SURF特征点检测 ==========
    Mat desc;
    vector<KeyPoint> kp;
    auto surf = xfeatures2d::SURF::create();
    surf->detectAndCompute(gray, noArray(), kp, desc);
    drawKeypoints(src, kp, src, Scalar(255, 0, 0));
    imwrite("./out/SURF_keypoing.jpg", src);
}