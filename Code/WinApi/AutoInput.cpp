#include <windows.h>
#include <thread>
#include <functional>
#include <atomic>
#include <iostream>

#define VK_U 0x55
#define VK_I 0x49

std::atomic<bool> running(false);

void softAttack();
void missRoll();

/**
 * 调用对应方法处理键码。
 *
 * 能够保证按键的连续按下和释放不会导致多次调用。但是每次按下都会创建一个线程，开销较大。
 */
void handleIdle(int vkCode) {
    if (vkCode == VK_U) {
        running = !running;
        if (running) {
            std::thread(missRoll).detach();
        }
    } else if (vkCode == VK_I) {
        running = !running;
        if (running) {
            std::thread(softAttack).detach();
        }
    }
}

/**
 * 当按下I键后，模拟鼠标左键按下100毫秒,完成贯注轻攻击动作，再次按下I键可解除。
 */
void softAttack() {
    while (running) {
        // 创建一个INPUT结构体来模拟鼠标左键按下
        INPUT input[2];

        // 模拟鼠标左键按下
        input[0].type = INPUT_MOUSE;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        SendInput(1, &input[0], sizeof(INPUT));
        std::this_thread::sleep_for(std::chrono::milliseconds(680));

        // 模拟鼠标左键释放
        input[1].type = INPUT_MOUSE;
        input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

        // 发送鼠标输入
        SendInput(1, &input[1], sizeof(INPUT));

        // 按下100毫秒
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "soft attack" << std::endl; // Debug info
    }
}

/**
 * 当按下U键后，模拟按下空格键和鼠标左键，完成躲闪翻滚动作，再次按下U键可解除。
 */
void missRoll() {
    while (running) {
        // 创建一个INPUT结构体来模拟按键
        INPUT input[4] = {0};

        // 模拟按下空格键（使用扫描码）
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC);
        input[0].ki.dwFlags = KEYEVENTF_SCANCODE;

        // 模拟释放空格键（使用扫描码）
        input[1].type = INPUT_KEYBOARD;
        input[1].ki.wScan = MapVirtualKey(VK_SPACE, MAPVK_VK_TO_VSC);
        input[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

        // 发送按键输入
        SendInput(2, input, sizeof(INPUT));

        // 模拟鼠标左键按下
        input[0].type = INPUT_MOUSE;
        input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        // 模拟鼠标左键释放
        input[1].type = INPUT_MOUSE;
        input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

        // 发送鼠标输入
        SendInput(2, input, sizeof(INPUT));

        // 每隔100ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "miss roll" << std::endl; // Debug info
    }
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
        if (wParam == WM_KEYDOWN) {
            handleIdle(pKeyBoard->vkCode);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hhkLowLevelKybd);
    return 0;
}