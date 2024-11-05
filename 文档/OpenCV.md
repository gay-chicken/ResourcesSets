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
