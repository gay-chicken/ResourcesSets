#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // ========== SIFT特征点检测 ==========
    // auto ptr = SIFT::create();
    // ========== SURF特征点检测 ==========
    // auto ptr = xfeatures2d::SURF::create();
    // ========== ORB特征点检测 ==========
    auto ptr = ORB::create();

    Mat face_1 = imread("./image/2.jpg");
    Mat face_2 = imread("./image/3.jpg");
    if (face_1.empty() || face_2.empty()) return -1;

    vector<KeyPoint> kp1, kp2;
    Mat desc1, desc2, face1_gray, face2_gray, face1_out, face2_out, dst;
    cvtColor(face_1, face1_gray, COLOR_BGR2GRAY);
    cvtColor(face_2, face2_gray, COLOR_BGR2GRAY);
    ptr->detectAndCompute(face1_gray, noArray(), kp1, desc1);
    ptr->detectAndCompute(face2_gray, noArray(), kp2, desc2);
    drawKeypoints(face_1, kp1, face1_out, Scalar(0, 255, 0));
    drawKeypoints(face_2, kp2, face2_out, Scalar(0, 255, 0));
    imwrite("./out/2_keypoint.jpg", face1_out);
    imwrite("./out/3_keypoint.jpg", face2_out);

    // ========== 暴力特征匹配方法 ==========
    // Ptr<DescriptorMatcher> matcher = new BFMatcher(NORM_L2, true);

    /** ========== 最快邻近区特征匹配方法 ==========
     *
     *  一种快速匹配特征点的匹配算法，但是精度不如BFMatcher。
     *
     * indexParams: 匹配算法，当使用ORB作为特征检测算法时，应该使用LSH；否则使用KDTREE。
     * searchParams: 仅使用KDTREE时生效，指定KDTREE算法中遍历树的次数。以实际经验而言，KDTREE=5时，该参数通常设置为50
     */
    Ptr<DescriptorMatcher> matcher = new FlannBasedMatcher(cv::makePtr<cv::flann::LshIndexParams>(1, 12, 20));

    /**
     * DMatch:
     *  distance: 描述子之间的距离，值越低越好
     *  queryIdx: 第一个图像的描述子索引值
     *  trainIdx: 第二个图像的描述子索引值
     *  imgIdx: 第二个图像的索引值
     */
    vector<DMatch> matches;
    matcher->match(desc1, desc2, matches);
    drawMatches(face_1, kp1, face_2, kp2, matches, dst);
    imwrite("./out/2&3_matcher.jpg", dst);
}