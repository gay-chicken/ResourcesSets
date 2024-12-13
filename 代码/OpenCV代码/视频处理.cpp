#include <opencv2/opencv.hpp>
#include <opencv2/bgsegm.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    auto bg = bgsegm::createBackgroundSubtractorMOG();
    VideoCapture cap("./videos/2.avi");
    Mat dst, mask;

    String path = "./trash/videos.avi";
    double fps = cap.get(CAP_PROP_FPS);
    int width = cap.get(CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CAP_PROP_FRAME_HEIGHT);
    int fourcc = cap.get(CAP_PROP_FOURCC);
    VideoWriter w(path, fourcc, fps, Size(width, height));

    if (!w.isOpened()) {
        cerr << "Unable to open video." << endl;
        return -1;
    }

    if (!cap.isOpened()) {
        cerr << "Unable to open video." << endl;
        return -1;
    }

    int i = 0;
    cout << "video processing, please wait ..." << endl;
    while (true)
    {
        // ++i;
        // if (!cap.grab())
        //     break; // 视频尾
        // if (i % 100 == 0)
        // {
        //     cap.retrieve(dst);
        //     bg->apply(dst, mask);
        //     imwrite("./trash/" + to_string(++i) + ".jpg", mask);
        // }
        cap >> dst;
        if (dst.empty()) break;
        bg->apply(dst, mask);
        w << mask;
    }
    cout << "finished." << endl;
    cap.release();
    w.release();
}