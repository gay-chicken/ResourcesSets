#include <filesystem>
#include <iostream>
#include <windows.h>

// int main()
// {
//     char origin[MAX_PATH];
//     wchar_t wallpaper[MAX_PATH] = L".\\wallpaper.bmp";

//     std::cout << std::endl
//               << "Set wallpaper..." << std::endl;

//     int ret;

//     // 获取旧壁纸文件路径
//     ret = SystemParametersInfo(SPI_GETDESKWALLPAPER, MAX_PATH, origin, 0);
//     std::cout << "Origin wallpaper: " << origin << ", status: " << ret << std::endl;

//     // 调用 SystemParametersInfo 函数来更改壁纸
//     ret = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)wallpaper, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
//     std::cout << "Set wallpaper: " << wallpaper << ", status: " << ret << std::endl;

//     return 0;
// }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    wchar_t wallpaper[MAX_PATH] = L".\\wallpaper.bmp";

    int ret;
    ret = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)wallpaper, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
    std::cout << "Set wallpaper: " << wallpaper << ", status: " << ret << std::endl;
    return 0;
}