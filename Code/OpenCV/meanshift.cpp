#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("./image/Coin.jpg");
    if (src.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    // meanShift
    Mat shift;
    pyrMeanShiftFiltering(src, shift, 15, 30);
    imwrite("./out/coin_meanshift.jpg", shift);

    // Canny
    Mat canny, gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Canny(gray, canny, 200, 100);
    imwrite("./out/coin_canny.jpg", canny);

    // Find contours
    Mat dst = src.clone();
    vector<vector<Point>> contours;
    findContours(gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(dst, contours, -1, Scalar(0, 0, 255), 2);
    imwrite("./out/coin_contours.jpg", dst);
}