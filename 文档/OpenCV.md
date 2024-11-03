## 1、基本操作

### 1.1 图像原理

#### 1.1.1 色彩空间

### 1.2 图像IO

**从文件读取图像**

```C++
Mat cv::imread(const String &filename,
               int flags = IMREAD_COLOR)
```



**从内存读取图像**

```C++
Mat cv::imdecode(InputArray buf,
                 int flags)
```



**保存图像至文件**

```C++
bool cv::imwrite(const String &filename,
                 InputArray img,
                 const std::vector<int> &params = std::vector<int>())
```



**保存图像至内存**

```C++
bool cv::imencode(const String &ext,
                  InputArray img,
                  std::vector<uchar> &buf,
                  const std::vector<int> &params = std::vector<int>())
```



### 1.3 绘制图形

**直线**

```C++
void cv::line(InputOutputArray img,
              Point pt1,
              Point pt2,
              const Scalar &color,
              int thickness = 1,
              int lineType = LINE_8,
              int shift = 0)
```



**矩形**

```C++
void cv::rectangle(InputOutputArray img,
                   Point pt1,
                   Point pt2,
                   const Scalar &color,
                   int thickness = 1,
                   int lineType = LINE_8,
                   int shift = 0)
```



**圆形**

```C++
void cv::circle(InputOutputArray img,
                Point center,
                int radius,
                const Scalar &color,
                int thickness = 1,
                int lineType = LINE_8,
                int shift = 0)
```



**椭圆**

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



**多边形**

```C++
void cv::polylines(InputOutputArray img,
                   InputArrayOfArrays pts,
                   bool isClosed,
                   const Scalar &color,
                   int thickness = 1,
                   int lineType = LINE_8,
                   int shift = 0)
```



**文本**

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



**标记**

```C++
void cv::drawMarker(InputOutputArray img,
                    Point position,
                    const Scalar &color,
                    int markerType = MARKER_CROSS,
                    int markerSize = 20,
                    int thickness = 1,
                    int line_type = 8)
```



**轮廓**

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



**箭头线段**

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
