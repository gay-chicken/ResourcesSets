## tesseract 4.00+ 的训练数据文件

[tessdata_best](https://github.com/tesseract-ocr/tessdata_best) (2017 年 9 月) 在 Google 的评估数据上取得最佳结果，速度较慢，`浮点数` 模型。这是唯一可以作为微调训练基础的模型。

[tessdata_fast](https://github.com/tesseract-ocr/tessdata_fast) (2017 年 9 月) 在速度和准确性之间取得最佳平衡，`整数` 模型。

[testdata](https://github.com/tesseract-ocr/tessdata)  (2016 年 11 月和 2017 年 9 月) 这些包含 2016 年的传统 tesseract 模型。



## 特殊数据文件

| 语言代码 | 描述            | traineddata                                                  |
| -------- | --------------- | ------------------------------------------------------------ |
| osd      | 方向和脚本检测  | [osd.traineddata](https://github.com/tesseract-ocr/tessdata/raw/3.04.00/osd.traineddata) |
| equ      | 数学/方程式检测 | [equ.traineddata](https://github.com/tesseract-ocr/tessdata/raw/3.04.00/equ.traineddata) |

