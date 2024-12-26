#include <fstream>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main()
{
    // 1. 导入模型，权重
    // readNetFromTensorflow(model, config);        // TensorFlow
    // readNetFromCaffe(prototxt, caffeModel);      // GoogLeNet, Caffe
    // readNetFromDarknet(cfgFile, darknetModel);   // YOLO
    // readNetFromTorch(model, isBinary, evaluate); // Torch
    String model = "./model/bvlc_googlenet.caffemodel";
    String config = "./model/bvlc_googlenet.prototxt";
    String framework = "caffe";
    Net net = readNet(model, config,
        framework); // 通用模型导入函数, 自动识别读取的模型类型

    // 2. 读取图片
    Mat src = imread("./image/Coin.jpg");
    if (src.empty()) {
        cout << "图片读取失败" << endl;
        return -1;
    }

    // 3. 将图片转成张量，输入到深度神经网络中
    Mat blob = blobFromImage(src, 1.0, Size(224, 224), Scalar(104, 117, 123)); // 将图片转成张量
    net.setInput(blob); // 将张量输入到深度神经网络中

    // 4. 进行分析, 得到结果
    Mat result = net.forward(); // 对图像进行分析

    // 5. 可视化结果
    ifstream ifs("./modle/synset_words.txt");
    vector<string> classes;
    string line;
    while (getline(ifs, line)) {
        classes.push_back(line);
    }

    // 找到最大概率的索引
    Point classIdPoint;
    double confidence;
    minMaxLoc(result.reshape(1, 1), 0, &confidence, 0, &classIdPoint);
    int classId = classIdPoint.x;

    // 输出结果
    if (classId >= 0 && classId < classes.size()) {
        cout << "预测类目: " << classes[classId] << "，置信度: " << confidence << endl;
    } else {
        cerr << "无效的类目ID: " << classId << endl;
    }
}