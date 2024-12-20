#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("./image/2.jpg");
    if (src.empty())
    {
        cerr << "Not found image." << endl;
        return -1;
    }

    Mat dst, kernel;
    Mat process;

    cvtColor(src, src, COLOR_BGR2GRAY);

    // 全局二值化
    threshold(src, dst, 128, 255, THRESH_BINARY);
    imwrite("./out/g_binrary.jpg", dst);

    // 自适应二值化
    adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 0);
    imwrite("./out/a_binrary.jpg", dst);

    // 生成一个卷积核
    kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    // 腐蚀
    // erode(dst, process, kernel);
    morphologyEx(dst, process, MORPH_ERODE, kernel);
    imwrite("./out/腐蚀^1.jpg", process);

    // 膨胀
    // dilate(dst, process, kernel);
    morphologyEx(dst, process, MORPH_DILATE, kernel);
    imwrite("./out/膨胀^1.jpg", process);

    // 开运算
    morphologyEx(dst, process, MORPH_OPEN, kernel);
    imwrite("./out/开运算^1.jpg", process);

    // 闭运算
    morphologyEx(dst, process, MORPH_CLOSE, kernel);
    imwrite("./out/闭运算^1.jpg", process);

    // 梯度运算
    morphologyEx(dst, process, MORPH_GRADIENT, kernel);
    imwrite("./out/梯度运算^1.jpg", process);

    // 黑帽运算
    morphologyEx(dst, process, MORPH_BLACKHAT, kernel);
    imwrite("./out/黑帽运算^1.jpg", process);

    // 梯度运算
    morphologyEx(dst, process, MORPH_GRADIENT, kernel);
    imwrite("./out/梯度运算^1.jpg", process);
}
