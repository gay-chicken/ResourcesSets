#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 返回两点之间距离
double getDistance(Point a, Point b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)); // sqrt(x² + y²)
}

// 移除两点之间距离在dis内的点
void reducedPoint(std::vector<cv::Point>& v, double dis) {
    size_t i = 0;
    while (i < v.size() - 1) {
        if (getDistance(v[i], v[i + 1]) <= dis) {
            v.erase(v.begin() + i + 1);
        } else {
            ++i;
        }
    }

    if (v.size() > 1 && getDistance(v.back(), v[0]) <= dis) {
        v.pop_back();
    }
}

// 打印点序号
void drawNumber(cv::InputOutputArray src, std::vector<cv::Point> points) {
    for (size_t i = 0; i < points.size(); ++i) {
        circle(src, points[i], 3, Scalar(0, 0, 255), -1, LINE_AA);
        putText(src, to_string(i), points[i], FONT_HERSHEY_PLAIN, 0.75, Scalar(0, 255, 0));
    }
}

int main() {
    Mat src = imread("./image/6.jpg");
    if (src.empty()) {
        cerr << "Not found image." << endl;
        return -1;
    }

    Mat gray, bin, dst;
    Point center(src.cols / 2, src.rows / 2);
    std::vector<cv::Point> sets, dp;
    std::vector<std::vector<cv::Point>> contours;

    // 图像预处理
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, bin, 128, 255, THRESH_BINARY_INV);
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 多边形逼近
    dst = src.clone();
    approxPolyDP(contours[3], sets, 20, true);
    // convexHull(dp, sets); // 排序顶点
    polylines(dst, sets, true, Scalar(0, 0, 255));
    drawNumber(dst, sets);
    imwrite("./out/多边形逼近.jpg", dst);

    // 凸包
    sets.clear();
    dst = src.clone();
    convexHull(contours[3], sets);
    // reducedPoint(sets, 50);
    polylines(dst, sets, true, Scalar(0, 0, 255));
    drawNumber(dst, sets);
    imwrite("./out/凸包.jpg", dst);
}