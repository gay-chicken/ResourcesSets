#include <iostream>
#include <opencv2/opencv.hpp>

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

    Mat gray, bin;

    // 转变为灰度图
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // 二值化
    threshold(gray, bin, 128, 255, THRESH_BINARY_INV); // 当轮廓为整幅图像时，尝试修改THRESH_BINARY_INV为THRESH_BINARY

    // 查找轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(bin, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 绘制轮廓
    drawContours(src, contours, -1, Scalar(0, 255, 0), 1); // 绘制绿色轮廓

    // 计算轮廓的周长和面积
    double area, arc;
    area = contourArea(contours[0]); // 计算第一个轮廓面积
    arc = arcLength(contours[0], true); // 计算第一个轮廓的周长，true表示这个轮廓是闭合的
    cout << "面积：" << area << ", 周长：" << arc << endl;

    imwrite("./out/查找轮廓.jpg", src);
}
