#include <windows.h>
#include <iostream>

int main() {
    // 壁纸文件路径
    const char* wallpaperPath = ".\\wallpaper.jpeg";  // 修改为你的图片路径

    // 调用 SystemParametersInfo 函数来更改壁纸
    int result = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)wallpaperPath, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

    if (result) {
        std::cout << "failed!" << std::endl;
    } else {
        std::cerr << "success!" << std::endl;
    }

    return 0;
}
