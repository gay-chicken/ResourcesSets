#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat src = imread("./image/6.jpg");
    if (src.empty()) {
        cerr << "Not found image." << endl;
        return -1;
    }

    Mat dst, gray, bin;
    vector<vector<Point>> contours;
    vector<RotatedRect> rects;
    vector<Rect> bounds;

    // 图像预处理
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, bin, 128, 255, THRESH_BINARY_INV);
    findContours(bin, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (const auto &it : contours) {
        rects.push_back(minAreaRect(it)); // 最小外接矩形
        bounds.push_back(boundingRect(it)); // 最大外接矩形
    }

    // 绘制最小矩形
    vector<Point2f> pos(4);
    for (const auto &it : rects) {
        it.points(pos);
        for (int i = 0; i < 4; i++) {
            line(src, pos[i], pos[(i+1)%4], Scalar(0, 255, 0));
        }
    }

    // 绘制外接矩形
    for (const auto &it : bounds) {
        putText(src, "CID: 0012344", Point(it.x, it.y), FONT_HERSHEY_PLAIN, 0.75, Scalar(0, 0, 0), 1, LINE_AA);
        rectangle(src, it, Scalar(0, 0, 255));
    }
    imwrite("./out/外接矩形.jpg", src);
}