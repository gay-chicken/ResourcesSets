#include <atomic>
#include <functional>
#include <iostream>
#include <thread>
#include <windows.h>

std::atomic<bool> running(false);

void PressEvent(int vkCode)
{
    if (vkCode == (VK_LBUTTON | VK_SHIFT)) {
        running = true;

        std::thread([]() {
            INPUT input;
            while (running) {
                input.type = INPUT_MOUSE;
                input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
                SendInput(1, &input, sizeof(INPUT));
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                input.type = INPUT_MOUSE;
                input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
                SendInput(1, &input, sizeof(INPUT));
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }).detach();
    }
}

void ReleaseEvent(int vkCode)
{
    if (vkCode == VK_LBUTTON) {
        running = false;
    }
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN) {
            PressEvent(pKeyBoard->vkCode);
        } else if (wParam == WM_KEYUP) {
            ReleaseEvent(pKeyBoard->vkCode);
        } else {
            std::cout << "other event." << std::endl;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hhkLowLevelKybd);
    return 0;
}