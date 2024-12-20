#include <opencv2/opencv.hpp>
#include <opencv2/bgsegm.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	auto bg = bgsegm::createBackgroundSubtractorMOG();
	VideoCapture cap("./2.mp4");
	Mat dst, frame;

	String path = "./contour.mp4";
	double fps = cap.get(CAP_PROP_FPS);
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int fourcc = cap.get(CAP_PROP_FOURCC);
	VideoWriter w(path, fourcc, fps, Size(width, height));

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	vector<vector<Point>> contours;
	Rect rect;

	list<Point> cars;
	int carnums = 0;
	constexpr int CHECK_LINE = 400;
	constexpr int OFFSET = 5;

	if (!cap.isOpened()) {
		cerr << "Not found videos." << endl;
		return -1;
	}

	while (cap.read(frame)) {
		cvtColor(frame, dst, COLOR_BGR2GRAY);
        // 对图像进行平滑处理，减少光照的影响
		GaussianBlur(dst, dst, Size(3, 3), 20);
		bg->apply(dst, dst);
		//morphologyEx(dst, dst, MORPH_OPEN, kernel, Point(-1, -1), 2);
        // 消除车辆内部细节，只保留外部轮廓
		morphologyEx(dst, dst, MORPH_CLOSE, kernel, Point(-1, -1), 5);
		findContours(dst, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		// 检测线
		line(frame, Point(0, CHECK_LINE), Point(1280, CHECK_LINE), Scalar(0, 255, 0), 3);
		for (const auto& it : contours) {
			rect = boundingRect(it);

			// 不绘制面积小的轮廓
			if (rect.area() < 1000) continue;

			// 绘制车辆轮廓
			rectangle(frame, rect, Scalar(0, 0, 255));
			cars.emplace_back(Point(rect.x + (rect.width / 2), rect.y + (rect.height / 2)));
			//putText(frame, "area: " + to_string(rect.area()), Point(rect.x, rect.y), FONT_HERSHEY_PLAIN, 0.75, Scalar(0, 0, 255), 1, LINE_AA);
			//circle(frame, Point(rect.x + (rect.width / 2), rect.y + (rect.height / 2)), 3, Scalar(0, 0, 255), -1, LINE_AA);

			// 车辆计数
			for (auto it = cars.begin(); it != cars.end();) {
				if (it->y < CHECK_LINE + OFFSET && it->y > CHECK_LINE - OFFSET) {
					++carnums;
					it = cars.erase(it);
				}
				else {
					++it;
				}
			}
		}
		putText(frame, "Cars count: " + to_string(carnums), Point(width / 3, height / 3), FONT_HERSHEY_PLAIN, 5, Scalar(0, 0, 0), 2, LINE_AA);
		w << frame;
	}

	w.release();
	cap.release();
}
