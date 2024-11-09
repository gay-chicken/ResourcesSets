## 1、基本操作

### 1.1 图像原理

#### 1.1.1 色彩空间

### 1.2 图像IO

#### 1.2.1 从文件读取图像

```C++
Mat cv::imread(const String &filename,
               int flags = IMREAD_COLOR)
```

从文件中加载图像。如果图像无法读取（由于文件丢失、权限不足、格式不支持或格式无效），则函数将返回一个空矩阵（Mat::data==NULL）。

**参数说明**

​	**filename** ：图像文件的路径

​	**flags** ：图像文件的读取方式，如灰度读取`IMREAD_GRAYSCALE`。参见[cv::ImreadModes](https://docs.opencv.org/4.0.0/d4/da8/group__imgcodecs.html#ga61d9b0126a3e57d9277ac48327799c80)

**示例代码**

```C++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat m1 = imread("./image/1.jpg");
    imshow("Color", m1);

    Mat m2 = imread("./image/1.jpg", IMREAD_GRAYSCALE);
    imshow("Gray", m2);

    Mat m3 = imread("./image/1.jpg", IMREAD_UNCHANGED);
    imshow("Alpha", m3);

    waitKey();
    destroyAllWindows();
    return 0;
}
```



#### 1.2.2 从内存读取图像

```C++
Mat cv::imdecode(InputArray buf,
                 int flags)
```



#### 1.2.3 保存图像至文件

```C++
bool cv::imwrite(const String &filename,
                 InputArray img,
                 const std::vector<int> &params = std::vector<int>())
```

将图像保存到指定的文件。图像格式根据文件名扩展名选择，一般来说，只有 8 位无符号（CV_8U）单通道或 3 通道（通道顺序为 'BGR'）图像可以使用此函数保存。

**参数说明**

​	**filename** ：保存的文件路径

​	**img**：(Mat 或 Mat 的向量) 要保存的图像或图像。

​	**flags** ：格式特定的参数编码为对 (paramId_1, paramValue_1, paramId_2, paramValue_2, ... .) 参见 [cv::ImwriteFlags](https://docs.opencv.org/4.0.0/d4/da8/group__imgcodecs.html#ga292d81be8d76901bff7988d18d2b42ac)

**示例代码**

```C++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat m1 = imread("./image/1.jpg");
    imwrite("./image/1_bak.jpg", m1);
    return 0;
}
```



#### 1.2.4 保存图像至内存

```C++
bool cv::imencode(const String &ext,
                  InputArray img,
                  std::vector<uchar> &buf,
                  const std::vector<int> &params = std::vector<int>())
```



### 1.3 绘制图形

#### 1.3.1 直线

```C++
void cv::line(InputOutputArray img,
              Point pt1,
              Point pt2,
              const Scalar &color,
              int thickness = 1,
              int lineType = LINE_8,
              int shift = 0)
```

在图像中绘制pt1和pt2点之间的线段，对于超出图像大小的部分会被裁剪。

**参数说明**

​	**img**：输入图像

​	**ptr1**：线段的第一个端点

​	**ptr2**：线段的第二个端点

​	**color**：线段的颜色

​	**thickness**：线段粗细

​	**lineType**：线段类型，参见[cv::LineTypes](https://docs.opencv.org/4.0.0/d6/d6e/group__imgproc__draw.html#gaf076ef45de481ac96e0ab3dc2c29a777)

​	**shift**： 点坐标中的分数位数量。

**示例代码**

```C++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat m1 = imread("./image/1.jpg");
    line(m1, Point(100, 100), Point(500, 500), Scalar(0, 0, 255), 4, LINE_AA);
    imshow("InputWindow", m1);
    waitKey();
    destroyAllWindows();
    return 0;
}
```

**运行结果**

![绘制线段](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411071557929.png)



#### 1.3.2 矩形

```C++
void cv::rectangle(InputOutputArray img,
                   Point pt1,
                   Point pt2,
                   const Scalar &color,
                   int thickness = 1,
                   int lineType = LINE_8,
                   int shift = 0)
```

绘制由pt1和pt2的两对相对顶点定义的矩形轮廓或填充矩形。

**参数说明**

​	**img**：输入图像

​	**pt1**：矩形的第一个顶点

​	**pt2**：对应pt1的矩形对角线顶点

​	**color**：矩形的颜色

​	**thickness**：绘制矩形线条的宽度，负值表示填充图形。

​	**lineType**：线的类型，参见[cv::LineTypes](https://docs.opencv.org/4.0.0/d6/d6e/group__imgproc__draw.html#gaf076ef45de481ac96e0ab3dc2c29a777)

​	**shift**：点坐标中的分数位数量。

**示例代码**

```C++
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    vector<Point> pts;
    Mat m1 = imread("./image/1.jpg");

    rectangle(m1, Point(100, 100), Point(500, 500), Scalar(0, 0, 255), 3, LINE_8);

    imshow("InputWindow", m1);
    waitKey();
    destroyAllWindows();
    return 0;
}
```

**运行结果**

![绘制矩形](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411071631048.png)

#### 1.3.3 圆形

```C++
void cv::circle(InputOutputArray img,
                Point center,
                int radius,
                const Scalar &color,
                int thickness = 1,
                int lineType = LINE_8,
                int shift = 0)
```

以给定的中心和半径绘制简单的或填充的圆。

**参数说明**

​	**img** ：输入图像

​	**center**：圆心

​	**radius**：圆半径

​	**color**：圆的颜色

​	**thickness**：线条宽度，负值表示填充。

​	**lineType**：线的类型，参见[cv::LineTypes](https://docs.opencv.org/4.0.0/d6/d6e/group__imgproc__draw.html#gaf076ef45de481ac96e0ab3dc2c29a777)

​	**shift**：点坐标中的分数位数量。

**示例代码**

```C++
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat m1 = imread("./image/1.jpg");

    circle(m1, Point(250, 250), 250, Scalar(0, 0, 255), 4);

    imshow("InputWindow", m1);
    waitKey();
    destroyAllWindows();
    return 0;
}
```

**运行结果**

![绘制圆形](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411071640046.png)

#### 1.3.4 椭圆

```C++
void cv::ellipse(InputOutputArray img,
                 Point center,
                 Size axes,
                 double angle,
                 double startAngle,
                 double endAngle,
                 const Scalar &color,
                 int thickness = 1,
                 int lineType = LINE_8,
                 int shift = 0)
```



#### 1.3.5 多边形

```C++
void cv::polylines(InputOutputArray img,
                   InputArrayOfArrays pts,
                   bool isClosed,
                   const Scalar &color,
                   int thickness = 1,
                   int lineType = LINE_8,
                   int shift = 0)
```

绘制多个多边形曲线。

**参数说明**

​	**img**：输入图像

​	**pts：**多边形曲线端点

​	**isClosed：**指示绘制的多边形是否闭合的标志。如果它们闭合，则从每个曲线的最后一个顶点绘制线条到其第一个顶点。

​	**color**：多边形颜色。

​	**thickness**：多边形边框的厚度。

​	**lineType**：线条段类型，参见[LineTypes](https://docs.opencv.ac.cn/4.10.0/d6/d6e/group__imgproc__draw.html#gaf076ef45de481ac96e0ab3dc2c29a777)

​	**shift：**顶点坐标中的小数位数的数量。

**示例代码**

```C++
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    vector<Point> pts;
    Mat m1 = imread("./image/1.jpg");

    pts.push_back(Point(250, 20));
    pts.push_back(Point(500, 250));
    pts.push_back(Point(500, 500));
    pts.push_back(Point(250, 500));
    pts.push_back(Point(250, 250));
    polylines(m1, pts, true, Scalar(0, 0, 255), 2, LINE_AA);

    imshow("InputWindow", m1);
    waitKey();
    destroyAllWindows();
    return 0;
}
```

**运行结果**

![绘制多边形](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411071621984.png)

#### 1.3.6 文本

```C++
void cv::putText(InputOutputArray img,
                 const String &text,
                 Point org,
                 int fontFace,
                 double fontScale,
                 Scalar color,
                 int thickness = 1,
                 int lineType = LINE_8,
                 bool bottomLeftOrigin = false)
```

在图像中渲染指定的文本字符串，无法使用指定字体显示的符号由问号替换。
**参数说明**

​	**img**：输入图像

​	**text**：进行绘制的文本字符串

​	**org**：文本左下角在图像中的位置

​	**fontFace**：字体类型，参见[cv::HersheyFonts](https://docs.opencv.org/4.0.0/d6/d6e/group__imgproc__draw.html#ga0f9314ea6e35f99bb23f29567fc16e11)

​	**fontScale**：字体缩放因子，它乘以字体特定的基础大小

​	**color**：文本颜色

​	**thickness**：绘制文本的线条厚度

​	**lineType**： 线条类型，参见[cv::LineTypes](https://docs.opencv.org/4.0.0/d6/d6e/group__imgproc__draw.html#gaf076ef45de481ac96e0ab3dc2c29a777)

​	**bottomLeftOrigin**：当为true时，图像数据原点位于左下角。否则，在左上角。

**示例代码**

```C++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat m1 = imread("./image/1.jpg");
    putText(m1, "Hello, OpenCV!", Point(0, 500), FONT_HERSHEY_SIMPLEX , 1.2, Scalar(0, 0, 255), 2, LINE_AA, false);
    imshow("InputWindow", m1);
    waitKey();
    destroyAllWindows();
    return 0;
}
```

**运行结果**

![绘制字符串](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411071615250.png)

#### 1.3.7 标记

```C++
void cv::drawMarker(InputOutputArray img,
                    Point position,
                    const Scalar &color,
                    int markerType = MARKER_CROSS,
                    int markerSize = 20,
                    int thickness = 1,
                    int line_type = 8)
```



#### 1.3.7 轮廓

```C++
void cv::drawContours(InputOutputArray image,
                      InputArrayOfArrays contours,
                      int contourIdx,
                      const Scalar &color,
                      int thickness = 1,
                      int lineType = LINE_8,
                      InputArray hierarchy = noArray(),
                      int maxLevel = INT_MAX,
                      Point offset = Point())
```



#### 1.3.8 箭头

```C++
void cv::arrowedLine(InputOutputArray img,
                     Point pt1,
                     Point pt2,
                     const Scalar &color,
                     int thickness = 1,
                     int line_type = 8,
                     int shift = 0,
                     double tipLength = 0.1)
```

在图像中绘制从 pt1 到 pt2 的箭头。

**参数说明**

​	**img**：输入图像

​	**pt1**：线段起始点

​	**pt2**：线段终点

​	**color**：线段颜色

​	**thickness**：多边形边框的厚度。

​	**lineType**：线条段类型，参见[LineTypes](https://docs.opencv.ac.cn/4.10.0/d6/d6e/group__imgproc__draw.html#gaf076ef45de481ac96e0ab3dc2c29a777)

​	**shift：**顶点坐标中的小数位数的数量。

**示例代码**

```C++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat m1 = imread("./image/1.jpg");
    arrowedLine(m1, Point(100, 100), Point(500, 500), Scalar(0, 0, 255), 4, LINE_AA);
    imshow("InputWindow", m1);
    waitKey();
    destroyAllWindows();
    return 0;
}
```

**运行结果**

![绘制箭头](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411071647561.png)

### 1.4 修改像素

### 1.5 修改属性

### 1.6 通道的拆分与合并

### 1.7 色彩空间转换

## 2、算术运算

### 2.1 图像加法

```C++
void cv::add(InputArray src1,
             InputArray src2,
             OutputArray dst,
             InputArray mask = noArray(),
             int dtype = -1)
```



### 2.2 图像混合

```C++
void cv::addWeighted(InputArray src1,
                     double alpha,
                     InputArray src2,
                     double beta,
                     double gamma,
                     OutputArray dst,
                     int dtype = -1)
```



### 2.3 方差与标准差

```C++
void cv::meanStdDev(InputArray src,
                    OutputArray mean,
                    OutputArray stddev,
                    InputArray mask = noArray())
```



### 2.4 位运算

**与运算**

```C++
void cv::bitwise_and(InputArray src1,
                     InputArray src2,
                     OutputArray dst,
                     InputArray mask = noArray())
```



**或运算**

```C++
void cv::bitwise_or(InputArray src1,
                    InputArray src2,
                    OutputArray dst,
                    InputArray mask = noArray())
```



**取反运算**

```C++
void cv::bitwise_not(InputArray src,
                     OutputArray dst,
                     InputArray mask = noArray())
```



**异或运算**

```C++
void cv::bitwise_xor(InputArray src1,
                     InputArray src2,
                     OutputArray dst,
                     InputArray mask = noArray())
```



### 2.5 协方差

```C++
void cv::calcCovarMatrix(const Mat *samples,
                         int nsamples,
                         Mat &covar,
                         Mat &mean,
                         int flags,
                         int ctype = CV_64F)
```



## 3、几何变换

### 3.1 平移

### 3.2 旋转

### 3.3 缩放

### 3.4 仿射变换

### 3.5 透射变换

### 3.6 图像金字塔

## 4、形态学

### 4.1 形态学基本原理

#### 4.1.1 邻域与连通性

#### 4.1.2 腐蚀与膨胀

#### 4.1.3 开闭运算

#### 4.1.4 礼帽与黑帽

### 4.2 形态学操作

```C++
void cv::morphologyEx(InputArray src,
                      OutputArray dst,
                      int op,
                      InputArray kernel,
                      Point anchor = Point(-1, -1),
                      int iterations = 1,
                      int borderType = BORDER_CONSTANT,
                      const Scalar &borderValue = morphologyDefaultBorderValue())
```



## 5、图像平滑

### 5.1 噪声

​    **高斯噪声** ：噪声值遵循高斯分布，通常出现在图像传感器测量过程中，使图像显得模糊或粒状，特别是在低光环境下更为明显。

​    **椒盐噪声** ：在图像中随机出现黑点（胡椒）和白点（盐），类似于盐和胡椒撒在图像上，会造成图像中的小区域突变，影响细节。

​    **斑点噪声** ：通常与医学成像（如超声波）相关，噪声和信号的强度成比例，使图像中出现明显的斑点，影响结构的清晰度。

​    **量化噪声** ：由于图像数字化过程中的量化误差引入的噪声，特别在色彩渐变区域明显，导致色带现象。

​    **周期性噪声** ：具有特定频率的噪声，通常是电源干扰引起的，在图像中表现为规则的条纹或波纹。

​    **色彩噪声** ：噪声在不同颜色通道中的强度不同，可能会导致色彩失真，常见于高ISO设置的摄影图像中，影响颜色的准确性。

​    **白噪声** ：在所有频率上均匀分布的噪声，通常看起来像是随机的亮度变化，整体降低图像的对比度和细节。

​    **模糊噪声** ：由于图像模糊造成的噪声，通常是因为运动或对焦不准确，使细节模糊不清，影响识别。

### 5.2 滤波

#### 5.2.1 线性滤波

​    **均值滤波**

​    通过计算邻域像素的平均值来平滑图像，适合去除高斯噪声。

```C++
void cv::blur(InputArray src,
              OutputArray dst,
              Size ksize,
              Point anchor = Point(-1, -1),
              int borderType = BORDER_DEFAULT)
```



​    **高斯滤波**

​    使用高斯函数加权邻域像素，效果更平滑，保留边缘特征。

```C++
void cv::GaussianBlur(InputArray src,
                      OutputArray dst,
                      Size ksize,
                      double sigmaX,
                      double sigmaY = 0,
                      int borderType = BORDER_DEFAULT)
```



#### 5.2.2 非线性滤波

​    **中值滤波**

​    通过取邻域像素的中值来替代中心像素，有效去除尖锐噪声。

```C++
void cv::medianBlur(InputArray src,
                    OutputArray dst,
                    int ksize)
```



​    **双边滤波**

​    同时考虑空间距离和像素值差异，能够平滑图像同时保留边缘。

#### 5.2.3 频域滤波

​    **傅里叶变换**

​    通过傅里叶变换将图像转换到频域，使用滤波器（如低通、高通滤波器）处理，然后反变换回空间域。

​    **小波变换**

​    用于多尺度分析，通过小波基函数处理图像，适合处理具有多层次特征的图像。

#### 5.2.4 自适应滤波

​    **自适应均值滤波**

​    根据局部噪声水平调整滤波强度。

​    **自适应中值滤波**

​    动态调整中值滤波的窗口大小，根据噪声程度处理图像。

#### 5.2.5 边缘增强滤波

​    **拉普拉斯滤波**

​    通过拉普拉斯算子检测边缘，突出图像变化较大的区域。

​    **锐化滤波**

​    使用增强算子（如高通滤波器）提升图像的边缘和细节。

#### 5.2.6 特征提取滤波

​    **Gabor滤波**

​    用于纹理分析，结合频率和方向信息。

​    **方向滤波**

​    如Sobel、Prewitt算子，主要用于边缘检测。

## 6、直方图

### 6.1 灰度直方图

```C++
void cv::calcHist(const Mat *images,
                  int nimages,
                  const int *channels,
                  InputArray mask,
                  OutputArray hist,
                  int dims,
                  const int *histSize,
                  const float **ranges,
                  bool uniform = true,
                  bool accumulate = false)
```



### 6.2 直方图均衡化

![直方图均衡](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411041122461.JPG)

```C++
void cv::equalizeHist(InputArray src,
                      OutputArray dst)
```



**自适应均衡化**

![均衡化](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411041141445.JPG)

```C++
Ptr<CLAHE> cv::createCLAHE(double clipLimit = 40.0,
                           Size tileGridSize = Size(8, 8))
```



```C++
virtual void cv::CLAHE::apply(InputArray src,
                              OutputArray dst)
```



## 7、边缘检测

### 7.1 Sobel检测算子

Sobel边缘检测算法比较简单，检测效率也比较高，但是其边缘检测的准确率较差。尽管如此，在大多数实际应用场景中还是首选Sobel算法。Sobel算子是高斯平滑与微分操作的结合体，所以其抗噪声能力很强，用途较多。尤其效率要求较高，对图像细节不需要太过注重的场景。

```C++
void cv::Sobel(InputArray src,
               OutputArray dst,
               int ddepth,
               int dx,
               int dy,
               int ksize = 3,
               double scale = 1,
               double delta = 0,
               int borderType = BORDER_DEFAULT)
```

$$
计算公式...
$$

![](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411050545753.jpg)

![](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411050545662.jpg)

### 7.2 Scharr算子

当Sobel算子的内核为3时，可能会产生比较明显的误差，为解决这一问题，可以使用Scharr算法，但是该算法仅作用于大小为3的内核。该算法与Sobel算法具有一样的效率，但是结果更加精确。

```C++
void cv::Scharr(InputArray src,
                OutputArray dst,
                int ddepth,
                int dx,
                int dy,
                double scale = 1,
                double delta = 0,
                int borderType = BORDER_DEFAULT)
```

### 7.3 Laplacian算子

![](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411050608337.jpg)

```C++
void cv::Laplacian(InputArray src,
                   OutputArray dst,
                   int ddepth,
                   int ksize = 1,
                   double scale = 1,
                   double delta = 0,
                   int borderType = BORDER_DEFAULT)
```



### 7.4 Canny边缘检测

![](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411050616710.jpg)

![](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411050617962.jpg)

![](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411050617784.jpg)

```C++
void cv::Canny(InputArray image,
               OutputArray edges,
               double threshold1,
               double threshold2,
               int apertureSize = 3,
               bool L2gradient = false)
```



### 7.5 算子比较

| 算子      | 优点                                                         | 缺点                                                         |
| --------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Roberts   | ①计算速度非常快，特别适合实时处理。②能够检测到较为精确的边缘。 | ①对噪声非常敏感，容易产生伪边缘。 ②由于窗口较小，可能无法捕捉到较大区域的边缘信息。③边缘较粗，边缘定位不够准确 |
| Sobel     | ①容易实现，计算量较小。 ②能够有效地检测到边缘，尤其是图像中的垂直和水平边缘。 ③对噪声具有一定的抑制作用，因为它是一个加权平均操作。 | ①对角线边缘的检测效果较差。 ②对噪声相对敏感，可能导致噪声点也被当作边缘检测出来。 |
| Kirsch    | ①在捕捉方向性边缘时更加有效。②能够识别复杂背景或噪声较大的图像边缘。③原理简单，实现容易。④能够捕捉方向性特征。 | ①对噪声比较敏感。②计算量大，处理时间长。③边缘定位不准确。④处理结果不平滑。 |
| Prewitt   | ①计算简单，类似Sobel算子。②对噪声有一定抑制作用。            | ①与Sobel算子类似，对角线边缘的检测效果差。 ②对噪声的敏感性较高。 |
| Laplacian | ①可以检测到边缘的细节，适用于轮廓检测。②较为简单且不需要多个参数调整。 | ①对噪声非常敏感，容易检测到噪声。②对于边缘方向没有明确的选择性。③可能会产生较为模糊的边缘。 |
| LoG       | ①能够有效去除高频噪声。②对复杂图像中的细节也能够较好的识别。③可以在不同尺度下检测到不同大小的边缘 | ①可能会产生一些虚假的边缘或检测到不连续的边缘。②对噪声比较敏感。③计算量大，速度慢。④受传入的参数影响，不合适的参数会导致边缘不够清晰。 |
| Canny     | ①边缘检测效果非常好，能检测到细小的边缘。②能有效去除噪声。③对边缘的定位精度较高。 | ①计算量较大，速度较慢。②对于某些复杂背景下的图像，可能会出现误检。 |
| Scharr    | ①较Sobel算子对噪声的抑制效果更好，检测结果更平滑。②对边缘的精确定位比Sobel算子更为精确。 | ①计算复杂度较Sobel算子略高。②对于某些图像可能过度平滑，导致边缘细节丢失。 |

## 8、模板匹配和霍夫变换

### 8.1 模板匹配

模板匹配是指在给定的图片中查找与模板最相似的区域。该算法包括输入的图片和模板，通过移动模板图片与输入图片一一比对，计算与图像中区域的匹配度，最终将匹配度最高的区域选择为最佳结果。如下图所示：

![模板匹配过程](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051342737.png)

**示例**

![模板匹配示例](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051350412.jpg)

```C++
void cv::matchTemplate(InputArray image,
                       InputArray templ,
                       OutputArray result,
                       int method,
                       InputArray mask = noArray())
```

**参数说明** 

​	**method** :

​		![取值功能](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051348458.png)

​		![计算公式](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051348504.png)

### 8.2 霍夫线检测

```C++
void cv::HoughLines(InputArray image,
                    OutputArray lines,
                    double rho,
                    double theta,
                    int threshold,
                    double srn = 0,
                    double stn = 0,
                    double min_theta = 0,
                    double max_theta = CV_PI)
```

**参数说明**

​	**image**：8位单通道二值源图像。图像可能会被函数修改。
​	**lines**：输出线段的向量。每条线由一个包含2或3个元素的向量表示 $(\rho, \theta)$ 或 $(\rho, \theta, 投票数)$。$\rho$ 是从坐标原点$(0, 0)$（图像的左上角）到线的距离。$\theta$ 是线的旋转角度（单位：弧度）（0为垂直线，$\frac{\pi}{2}$为水平线）。投票数是累加器的值。
​	**rho**：累加器的距离分辨率，单位为像素。
​	**theta**：累加器的角度分辨率，单位为弧度。
​	**threshold**：累加器阈值参数。只有获得足够投票数（`>threshold`）的线段才会被返回。
​	**srn**：对于多尺度霍夫变换，它是累加器距离分辨率 $\rho$ 的除数。粗略的累加器距离分辨率为 $\rho$，精确的累加器距离分辨率为 $\frac{\rho}{srn}$。如果`srn=0`并且`stn=0`，则使用经典的霍夫变换。否则，这两个参数都应该是正数。
​	**stn**：对于多尺度霍夫变换，它是累加器角度分辨率θ的除数。
​	**min_theta**：对于标准和多尺度霍夫变换，检查线段的最小角度。必须在`0`和`max_theta`之间。
​	**max_theta**：对于标准和多尺度霍夫变换，检查线段的最大角度。必须在`min_theta`和`CV_PI`之间。

**示例代码**

```C++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main()
{
    cv::Mat src = cv::imread("./image/7.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
    if (src.empty())
    {
        std::cerr << "Not found image." << std::endl;
        return -1;
    }

    /*
       霍夫线检测
     */
    cv::Point p1(src.cols / 2, src.rows / 2), p2;
    cv::Mat canny, edges;
    cv::Mat dst = src.clone();
    float lenght, angle;

    cv::Canny(src, canny, 20, 50);
    cv::HoughLines(canny, edges, 1.0, CV_PI / 180.0, 100);

    // 将得到的极坐标点绘制在图像上
    for (int i = 0; i < edges.rows; i++)
    {
        lenght = edges.at<float>(i, 0);
        angle = edges.at<float>(i, 1);

        p1.x = cos(angle) * lenght + 1000 * (-sin(angle));
        p1.y = sin(angle) * lenght + 1000 * cos(angle);
        p2.x = cos(angle) * lenght - 1000 * (-sin(angle));
        p2.y = sin(angle) * lenght - 1000 * cos(angle);

        line(dst, p1, p2, cv::Scalar(255), 1, cv::LINE_AA);
    }
    cv::imwrite("./image/7_Canny.jpg", canny);
    cv::imwrite("./image/7_HoughLines.jpg", dst);
    return 0;
}
```



### 8.3 霍夫圆检测

```C++
void cv::HoughCircles(InputArray image,
                      OutputArray circles,
                      int method,
                      double dp,
                      double minDist,
                      double param1 = 100,
                      double param2 = 100,
                      int minRadius = 0,
                      int maxRadius = 0)
```

**参数说明**

​	**image**：8位单通道灰度输入图像。

​	**circles**：输出向量，包含找到的圆。每个圆被编码为一个包含3或4个元素的浮动点向量（x, y, 半径）或（x, y, 半径, 投票数）。

​	**method**：检测方法，参见 [HoughModes](https://docs.opencv.org/4.0.0/dd/d1a/group__imgproc__feature.html#ga073687a5b96ac7a3ab5802eb5510fe65)。当前实现的唯一方法是 `HOUGH_GRADIENT`。

​	**dp**：累加器分辨率与图像分辨率的倒数比例。例如，如果 `dp=1`，累加器的分辨率与输入图像相同；如果 `dp=2`，累加器的宽度和高度是输入图像的一半。

​	**minDist**：检测到的圆心之间的最小距离。如果这个参数设置得过小，可能会错误地检测到多个相邻的圆。如果设置得过大，可能会漏掉一些圆。

​	**param1**：第一个方法特定的参数。在 `HOUGH_GRADIENT` 方法中，它是传递给 Canny 边缘检测器的两个阈值中的较高值（较低值为高值的一半）。

​	**param2**：第二个方法特定的参数。在 `HOUGH_GRADIENT` 方法中，它是检测阶段用来判断圆心的累加器阈值。该值越小，可能检测到的假圆越多。累加器值较大的圆将优先返回。

​	**minRadius**：最小圆的半径。

​	**maxRadius**：最大圆的半径。如果 ≤ 0，使用图像的最大维度。如果 < 0，返回圆心而不查找半径。

在霍夫圆检测中，需要对**param1**和**param2**进行细致的调整，不恰当的数值可能会导致无法检测到圆或错误的检测出不是圆的数据。通常设置**param1** = 200，**param2** = 100。

**示例代码**

```C++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

int main()
{
    cv::Mat src = cv::imread("./image/7.jpg", cv::ImreadModes::IMREAD_GRAYSCALE);
    if (src.empty())
    {
        std::cerr << "Not found image." << std::endl;
        return -1;
    }

    /*
        霍夫圆检测
    */
    cv::Mat median, data, circle;
    cv::Point center;
    int radius;

    cv::medianBlur(src, median, 7);
    cv::HoughCircles(median, data, cv::HOUGH_GRADIENT, 2, median.rows/4, 200, 100);

    // 绘制圆心和外圆
    for (int i = 0; i < data.cols; i+=3)
    {
        center.x = static_cast<int>(data.at<float>(0, i));
        center.y = static_cast<int>(data.at<float>(0, i+1));
        radius = static_cast<int>(data.at<float>(0, i+2));

        cv::circle(median, center, 3, cv::Scalar(128), -1, cv::LINE_AA);
        cv::circle(median, center, radius, cv::Scalar(128), 2, cv::LINE_AA);
    }
    cv::imwrite("./image/7_HoughCircles.jpg", median);
    return 0;
}
```



## 9、特征提取与描述

特征提取就是从图像中提取显著并且具有可区分性和可匹配性的点结构。常见的点结构一般为图像内容中的**角点**、**交叉点**、**闭合区域中心点**等具有一定物理结构的点，而提取点结构的一般思想为**构建能够区分其他图像结构的响应函数**或者从特征线或轮廓中进行稀疏采样。

![特征提取方式](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051519864.png)

### 9.1 Harris角点检测

Harris角点检测的思想是通过图像的局部小窗口观察图像，角点的特征是窗口沿着任意方向移动都会导致图像灰度的明显变化。如下图所示：

![Harris角点检测原理](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051456272.png)

![特征值的规律](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051511522.png)

```C++
void cv::cornerHarris(InputArray src,
                      OutputArray dst,
                      int blockSize,
                      int ksize,
                      double k,
                      int borderType = BORDER_DEFAULT)
```



### 9.2 Shi-Tomas算法

Shi-Tomas检测算法是对Harris算法的改进，一般会得到比Harris更好的角点。Harris算法的角点响应函数是将矩阵$M$ 的行列式与$M$ 的迹相减，利用差值判断是否为角点。Shi-Tomas算法的改进方案为，若矩阵$M$ 的两个特征值中较小一个大于阈值，则认为它是角点。如下图所示：

![](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051513954.jpg)

只有当$\lambda_1$ 和$\lambda_2$ 都大于最小值时，才会被认为是角点。

```C++
void cv::goodFeaturesToTrack(InputArray image,
                             OutputArray corners,
                             int maxCorners,
                             double qualityLevel,
                             double minDistance,
                             InputArray mask = noArray(),
                             int blockSize = 3,
                             bool useHarrisDetector = false,
                             double k = 0.04)
```

### 9.3 SIFT算法

#### 9.3.1 SIFT算法介绍

Harris算法和Shi-Tomas算法具有旋转不变性，但不具备尺度不变性，即能够检测图像旋转后的角点，但无法检测出图像放大后的角点。如下图所示：

![](https://raw.githubusercontent.com/gay-chicken/ResourcesSets/main/%E5%9B%BE%E7%89%87/202411051525493.png)

SIFT 全名为尺度不变特征转换 (即 Scale-invariant feature transform)，是一种计算机视觉算法，用来检测与描述图像中的局部特征。SIFT 算法就是在空间尺度中寻找特征，并提取出其位置、尺度和旋转不变量，该算法的特点主要是：

+ 平移旋转不变性、尺度缩放不变性。
+ 明暗度变化保持不变性，即场景亮度变化，该特征不变。
+ SIFT 特征是图像的局部区域的特征。
+  对噪声不敏感，有一定的噪声容错能力。
+ 信息量丰富，信息具有独特性，匹配准确。
+ 简单场景也可以产生大量 SIFT 特征。

#### 9.3.2 SIFT算法步骤

1. 尺度空间极值检测：搜索所有尺度上的图像位置，通过高斯差分函数来识别潜在的对尺度和旋转不变的关键点。
2. 关键点定位：在每个候选的位置上，通过一个拟合精细的模型来确定位置和尺度。关键点的选择将依据于他们的稳定程度。
3. 关键点方向确定：基于图像局部的梯度方向，分配给每个关键点位置一个或多个方向。所有后面的对图像数据的操作都相对于关键点的方向、尺度和位置进行交换，从而保证了对于这些变换的不变性。
4. 关键点描述：在每个关键点周围的邻域内，在选定的尺度上测量图像局部的梯度。这些梯度作为关键点的描述符，它允许比较大的局部形状的变形或光照变化。

```C++
static Ptr<SIFT> cv::xfeatures2d::SIFT::create(int nfeatures = 0,
                                               int nOctaveLayers = 3,
                                               double contrastThreshold = 0.04,
                                               double edgeThreshold = 10,
                                               double sigma = 1.6)
```



### 9.4 SURF算法

SIFT的改进算法

```C++
static Ptr<SURF> cv::xfeatures2d::SURF::create(double hessianThreshold = 100,
                                               int nOctaves = 4,
                                               int nOctaveLayers = 3,
                                               bool extended = false,
                                               bool upright = false)
```



### 9.5 Fast算法

**FAST算法**（Features From Accelerated Segment Test，FAST）是一种用于角点检测的算法。FAST 角点定义为：若某像素点与周围邻域足够多的像素点处于不同区域，则该像素可能为角点。即某个像素周围拥有一定数量的像素与该像素值不同，则认为其为角点。与其他特征点相比较而言，FAST 在进行角点检测时，**计算速度更快，实时性更好**。

```C++
static Ptr<FastFeatureDetector> cv::FastFeatureDetector::create(int threshold = 10,
                                   bool nonmaxSuppression = true,
                                   FastFeatureDetector::DetectorType type = FastFeatureDetector::TYPE_9_16)
```

### 9.6 ORB算法

ORB算法结合了Fast算法和Brief算法，提出了构造金字塔，为Fast特征点添加了方向，从而使得关键点有了尺度不变性和旋转不变性。

```C++
static Ptr<ORB> cv::ORB::create(int nfeatures = 500,
                                float scaleFactor = 1.2f,
                                int nlevels = 8,
                                int edgeThreshold = 31,
                                int firstLevel = 0,
                                int WTA_K = 2,
                                ORB::ScoreType scoreType = ORB::HARRIS_SCORE,
                                int patchSize = 31,
                                int fastThreshold = 20)
```

## 10、视频处理

### 10.1 读取视频

```C++
cv::VideoCapture::VideoCapture();
cv::VideoCapture::VideoCapture(const String &filename,
                               int apiPreference = CAP_ANY);
cv::VideoCapture::VideoCapture(int index,
                               int apiPreference = CAP_ANY);
```

### 10.2 保存视频

```C++
cv::VideoWriter::VideoWriter();
cv::VideoWriter::VideoWriter(const String &filename,
                             int fourcc,
                             double fps,
                             Size frameSize,
                             bool isColor = true);
cv::VideoWriter::VideoWriter(const String &filename,
                             int apiPreference,
                             int fourcc,
                             double fps,
                             Size frameSize,
                             bool isColor = true);
```

设置视频编码：

```C++
static int cv::VideoWriter::fourcc(char c1,
                                   char c2,
                                   char c3,
                                   char c4);
```

### 10.3 视频追踪

#### 10.3.1 meanshift算法

使用一个固定大小的跟踪窗口遍历整幅图像确定目标区域，通过计算目标区域的直方图分布，找到最相似的直方图便完成了目标跟踪。

```C++
int cv::meanShift(InputArray probImage,
                  Rect &window,
                  TermCriteria criteria)
```

#### 10.3.2 Camshift算法

Camshift算法是meanshift算法的改进版本，可根据跟踪目标的大小实时变化跟踪窗口的大小。

```C++
RotatedRect cv::CamShift(InputArray probImage,
                         Rect &window,
                         TermCriteria criteria)
```

## 11、机器学习

### 11.1 人脸检测

使用大量的正样本图像（面部图像）和负样本图像（不含面部图像）来训练分类器，从中提取Haar特征。得到图像的Haar特征后，训练一个决策树构建的adaboost级联决策器来识别是否为人脸。

**实现流程**

1. 读取图片，并转换为灰度图。

2. 实例化人脸和眼睛检测的分类器对象

   ```C++
   cv::CascadeClassifier::CascadeClassifier();
   cv::CascadeClassifier::CascadeClassifier(const String &filename);
   ```

3. 进行人脸和眼睛的检测

   ```C++
   virtual void cv::BaseCascadeClassifier::detectMultiScale(InputArray image,
                                                            std::vector<Rect> &objects,
                                                            double scaleFactor,
                                                            int minNeighbors,
                                                            int flags,
                                                            Size minSize,
                                                            Size maxSize)
   ```

   ```C++
   virtual bool cv::BaseCascadeClassifier::load(const String &filename)
   ```

4. 显示结果图像。

