#include <opencv2/opencv.hpp>
#include <opencv2/bgsegm.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	//auto mog = bgsegm::createBackgroundSubtractorMOG(); // 以时间作为缓冲单位，处理速度慢。
	auto mog = createBackgroundSubtractorMOG2(); // 计算精确，可以计算出阴影，但是也会产生许多噪点
	auto gmg = bgsegm::createBackgroundSubtractorGMG(); // MOG2的衍生算法，消除了大部分噪点，但会存在一段时间的黑屏
	VideoCapture cap("./2.mp4");
	Mat frame, dst;

	String path = "./frontground_for_mog2.mp4";
	String path2 = "./frontground_for_gmg.mp4";
	double fps = cap.get(CAP_PROP_FPS);
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int fourcc = cap.get(CAP_PROP_FOURCC);
	VideoWriter w(path, fourcc, fps, Size(width, height));
	VideoWriter w2(path2, fourcc, fps, Size(width, height));

	while (cap.read(frame)) {
		mog->apply(frame, dst);
		w.write(dst);
		gmg->apply(frame, dst);
		w2.write(dst);
	}

	w.release();
	w2.release();
	cap.release();
}