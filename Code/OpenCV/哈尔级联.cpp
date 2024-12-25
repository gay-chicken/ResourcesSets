#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    CascadeClassifier faceCascade("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml");
    if (faceCascade.empty()) {
        cerr << "Error: Could not load Haar cascade classifier!" << endl;
        return -1;
    }

    Mat src = imread("./image/多人合影.jpg");
    if (src.empty()) {
        cerr << "Error: Could not load image!" << endl;
        return -1;
    }

    // 将图像转换为灰度图像
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // 检测人脸
    vector<Rect> faces;
    faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

    for (const auto &face : faces) {
        rectangle(src, face, Scalar(0, 255, 0), 2);
    }

    imwrite("./out/哈尔级联检测.jpg", src);
}