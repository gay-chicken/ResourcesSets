#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("./image/1.jpg");
    if (src.empty())
    {
        cerr << "Not found image." << endl;
        return -1;
    }

    Mat dst;

    // 均值滤波
    blur(src, dst, Size(5, 5));
    imwrite("./out/1_blur.jpg", dst);

    // 高斯滤波
    GaussianBlur(src, dst, Size(5, 5), 0.7);
    imwrite("./out/1_GaussianBlur.jpg", dst);

    // 中值滤波
    medianBlur(src, dst, 5);
    imwrite("./out/1_medianBlur.jpg", dst);

    // 双边滤波
    bilateralFilter(src, dst, 5, 20, 30);
    imwrite("./out/1_bilateralFilter.jpg", dst);

    // Sobel高通滤波
    Mat m1, m2, m3;
    Sobel(src, m1, CV_32F, 1, 0); // ∂x
    Sobel(src, m2, CV_32F, 0, 1); // ∂y
    magnitude(m1, m2, m3);      // 梯度合并
    // dst = m1 + m2;
    imwrite("./out/1_Sobel.jpg", m3);

    // Scharr高通滤波
    Scharr(src, m1, CV_32F, 1, 0);
    Scharr(src, m2, CV_32F, 0, 1);
    magnitude(m1, m2, m3);
    // dst = m1 + m2;
    imwrite("./out/1_Scharr.jpg", m3);

    // Laplacian算子
    Laplacian(src, dst, CV_8U);
    imwrite("./out/1_Laplacian.jpg", dst);
}
