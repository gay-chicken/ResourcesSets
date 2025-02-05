#include <opencv2/opencv.hpp>
#include <opencv2/bgsegm.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	//auto mog = bgsegm::createBackgroundSubtractorMOG(); // ��ʱ����Ϊ���嵥λ�������ٶ�����
	auto mog = createBackgroundSubtractorMOG2(); // ���㾫ȷ�����Լ������Ӱ������Ҳ�����������
	auto gmg = bgsegm::createBackgroundSubtractorGMG(); // MOG2�������㷨�������˴󲿷���㣬�������һ��ʱ��ĺ���
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