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
    vector<DMatch> matches, good_matches;
    matcher.match(desc1, desc2, matches);

    // 计算距离的中位数
    vector<double> distances;
    for (const auto& match : matches) {
        distances.push_back(match.distance);
    }
    sort(distances.begin(), distances.end());
    double median_dist = distances[distances.size() / 2];


    // 使用中位数的两倍作为阈值
    for (const auto& match : matches) {
        if (match.distance <= 2 * median_dist) {
            good_matches.push_back(match);
        }
    }
    cout << "origin matches: " << matches.size() << ", good matches: " << good_matches.size() << endl;

    // ===== 调试输出 =====
    Mat res;
    drawMatches(src1, kp1, src2, kp2, good_matches, res);
    imwrite("./out/7&8_good_matches.jpg", res); // 存在一块无关区域具有大量特征点
    return 0;
}