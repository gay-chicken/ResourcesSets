#include <windows.h>
#include <stdio.h>

void Register() {
    int ret = RegisterHotKey(NULL, 1, 0, VK_F10);
    if (!ret) return;

    MSG msg;
    while (1) {
        GetMessage(&msg,  NULL, 0, 0);
        if (msg.message == WM_HOTKEY && msg.wParam == 1) {
            // TODO: 热键被触发
            printf("hello, world\n");
        }
        // 使用ESC退出程序
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
    }

    UnregisterHotKey(NULL, 1);
}

int main() {
    Register();
}