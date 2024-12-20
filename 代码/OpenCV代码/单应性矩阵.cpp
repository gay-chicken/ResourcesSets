#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat src1 = imread("./image/7.png");
    Mat src2 = imread("./image/8.png");
    if (src1.empty() || src2.empty())
    {
        cerr << "Not found image." << endl;
        return -1;
    }

    Ptr<SIFT> ptr = SIFT::create();
    vector<KeyPoint> kp1, kp2;
    Mat desc1, desc2;

}
