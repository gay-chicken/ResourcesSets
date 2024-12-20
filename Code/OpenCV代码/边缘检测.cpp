#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("./image/2.jpg");
    if (src.empty()) {
        cerr << "Not found image." << endl;
        return -1;
    }

    Mat dst;

    // Canny边缘检测
    Canny(src, dst, 10, 50);
    imwrite("./out/2_Canny.jpg", dst);

    return 0;
}