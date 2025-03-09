### 问：QIODevice(): not open device

答：可以通过QFile::exists(filepath)检测文件路径是否正确以及QFile.isOpen()测试文件是否正确打开。该问题的大部分情况是使用到了.qrc资源文件，路径配置不正确而导致的。使用.qrc资源文件的路径应当如下：

```C++
QFile file(":/input.txt");
```

使用 ``:`` 表明文件处在资源文件路径下。
