#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("./image/Coin.jpg");
    if (src.empty()) {
        cout << "can not load image..." << endl;
        return -1;
    }

    Mat dst, front, back, gray, binary;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 75, 255, THRESH_BINARY_INV);
    // imwrite("./out/coin_binary.jpg", binary);

    // 消除轮廓内部细节
    morphologyEx(binary, dst, MORPH_DILATE, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 3);
    morphologyEx(dst, back, MORPH_ERODE, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 3);
    // imwrite("./out/coin_morphology.jpg", back);

    // 提取硬币
    distanceTransform(back, dst, DIST_L2, 5);
    threshold(dst, front, 20, 255, THRESH_BINARY);
    imwrite("./out/coin_dist.jpg", front);

    // 获取未知区域
    front.convertTo(front, CV_8U);
    Mat area = back - front;
    imwrite("./out/coin_unknown.jpg", area);

    // 创建连通域
    Mat markers;
    int n = connectedComponents(area, markers);
    cout << "labels: " << n << endl;

    // 分水岭算法
    watershed(src, markers);
    src.setTo(Scalar(0, 0, 255), markers < 0);
    imwrite("./out/coin_watershed.jpg", src);
}