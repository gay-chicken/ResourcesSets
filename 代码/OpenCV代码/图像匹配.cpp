#include <opencv2/opencv.hpp>
#include <iostream>

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
}
