#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("./image/Coin.jpg");
    if (src.empty()) {
        cout << "can not load image..." << endl;
        return -1;
    }

    // =====卷积锐化=====
    Mat dst;
    Mat kernel = (cv::Mat_<float>(3, 3) <<
                                            0, -1, 0,
                                            -1, 5, -1,
                                            0, -1, 0);
    filter2D(src, dst, -1, kernel);
    imwrite("./out/coin_filter.jpg", dst);

    // =====高斯模糊锐化=====
    cv::Mat blurredImg;
    cv::GaussianBlur(src, blurredImg, cv::Size(5, 5), 1.5);

    // 计算原图像和模糊图像的差异
    cv::Mat sharpenedImg = src - blurredImg;
    // 将差异与原图像相加进行锐化
    sharpenedImg = src + sharpenedImg;
    imwrite("./out/coin_sharpen.jpg", sharpenedImg);

    // =====边缘检测与图像叠加锐化=====
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // 使用 Sobel 算子进行边缘检测
    cv::Mat gradX, gradY, grad;
    cv::Sobel(gray, gradX, CV_16S, 1, 0, 3);
    cv::Sobel(gray, gradY, CV_16S, 0, 1, 3);

    // 合并 X 和 Y 方向的梯度
    cv::Mat absGradX, absGradY;
    cv::convertScaleAbs(gradX, absGradX);
    cv::convertScaleAbs(gradY, absGradY);
    grad = absGradX + absGradY;

    // 将边缘图像扩展为三通道，以便与原图叠加
    cv::Mat grad3Channel;
    cv::Mat channels[3] = {grad, grad, grad}; // 使用相同的梯度图填充所有三个通道
    cv::merge(channels, 3, grad3Channel); // 合并为三通道图像

    // 将边缘与原图像叠加
    cv::Mat dstImg;
    src.convertTo(dstImg, CV_8UC3);
    dstImg += grad3Channel;
    imwrite("./out/coin_sobel.jpg", dstImg);
}