#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main() {
    Mat left = imread("./image/9.jpeg");
    Mat right = imread("./image/10.jpeg");
    if (left.empty() || right.empty()) {
        cout << "图像读取失败" << endl;
        return -1;
    }

    Mat left2, right2;
    resize(left, left2, Size(0, 0), 0.2, 0.2);
    resize(right, right2, Size(0, 0), 0.2, 0.2);

    Ptr<SIFT> algorithm = SIFT::create();
    vector<KeyPoint> keyPoints1, keyPoints2;
    Mat descriptors1, descriptors2;
    algorithm->detectAndCompute(left2, Mat(), keyPoints1, descriptors1);
    algorithm->detectAndCompute(right2, Mat(), keyPoints2, descriptors2);

    BFMatcher matcher(NORM_L2, true);
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    vector<DMatch> goodMatches;
    for (size_t i = 0; i < matches.size(); ++i) {
        if (matches[i].distance < 200) {
            goodMatches.push_back(matches[i]);
        }
    }

    if (goodMatches.size() < 4) {
        cout << "匹配点太少" << endl;
        return -1;
    }

    vector<Point2f> pts1, pts2;
    for (size_t i = 0; i < goodMatches.size(); ++i) {
        pts1.push_back(keyPoints1[goodMatches[i].queryIdx].pt);
        pts2.push_back(keyPoints2[goodMatches[i].trainIdx].pt);
    }
    Mat mask;
    Mat H = findHomography(pts1, pts2, RANSAC, 4.0, mask);

    if (H.empty()) {
        cout << "未找到单应性矩阵" << endl;
        return -1;
    }

    Mat result;
    warpPerspective(left2, result, H, Size(left2.cols + right2.cols, left2.rows));
    Mat half(result, Rect(0, 0, right2.cols, right2.rows));
    right2.copyTo(half);
    imwrite("./out/result.jpg", half`);
}