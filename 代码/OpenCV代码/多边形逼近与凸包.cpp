#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void drawPoly(cv::InputOutputArray src, std::vector<cv::Point> points) {
    for (int i = 0; i < points.size() - 1; ++i) {
        cv::line(src, points[i], points[i + 1], Scalar(0, 0, 255));
    }
}

int main() {
    Mat src = imread("./image/6.jpg");
    if (src.empty()) {
        cerr << "Not found image." << endl;
        return -1;
    }

    Mat gray, bin, dst;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    threshold(gray, bin, 128, 255, THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    std::vector<cv::Point> sets;
    approxPolyDP(contours[0], sets, 100, false);

    // drawPoly(src, sets);
    imwrite("./out/多边形逼近.jpg", src);
}