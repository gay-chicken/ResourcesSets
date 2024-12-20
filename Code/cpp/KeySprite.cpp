#include <iostream>
#include <Windows.h>

// 钩子句柄
HHOOK hHook;

// 钩子回调函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        // 只处理按键事件
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
            std::cout << "Key pressed: " << pKeyboard->vkCode << std::endl;
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

// 设置钩子函数
void SetHook() {
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (hHook == NULL) {
        std::cerr << "Failed to install hook!" << std::endl;
    }
}

// 卸载钩子函数
void Unhook() {
    if (hHook) {
        UnhookWindowsHookEx(hHook);
    }
}

int main() {
    SetHook();

    // 消息循环，保持钩子运行
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Unhook();
    return 0;
}
