#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    Mat src1 = imread("./image/7.jpg");
    Mat src2 = imread("./image/8.jpg");
    if (src1.empty() || src2.empty())
    {
        cerr << "Not found image." << endl;
        return -1;
    }

    Ptr<ORB> ptr = ORB::create();
    vector<KeyPoint> kp1, kp2;
    Mat desc1, desc2;

    ptr->detectAndCompute(src1, noArray(), kp1, desc1);
    ptr->detectAndCompute(src2, noArray(), kp2, desc2);

    // 使用BFMatcher进行描述符匹配
    BFMatcher matcher(NORM_L2);
    vector<DMatch> matches;
    matcher.match(desc1, desc2, matches);

    // 过滤特征点
    vector<DMatch> good_matches;
    for (size_t i = 0; i < matches.size() - 1; i++)
    {
        if (matches[i].distance < (matches[i + 1].distance * 0.8))
        {
            good_matches.push_back(matches[i]);
        }
    }

    vector<Point2f> pts1, pts2;
    for (size_t i = 0; i < good_matches.size(); i++)
    {
        pts1.push_back(kp1[good_matches[i].queryIdx].pt);
        pts2.push_back(kp2[good_matches[i].trainIdx].pt);
    }

    Mat dst, mask;
    Mat H = findHomography(pts1, pts2, RANSAC, 5.0, mask);
    cout << H << endl;

    return 0;
}