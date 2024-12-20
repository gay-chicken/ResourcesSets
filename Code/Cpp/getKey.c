#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

void GetKeyToString(UINT keycode, char* buffer) {

    UINT scan = MapVirtualKey(keycode, MAPVK_VK_TO_VSC);
    ToUnicode(keycode, scan, NULL, (LPWSTR)buffer, 5, 0);
}

int main() {
    // while(true) {
    //     std::cout << ".";
    //     if (GetAsyncKeyState(VK_ESCAPE) != 0) break;
    // }
    char *p = NULL;
    p = (char*)malloc(sizeof(char) * 10);
    printf("%p\n", p);
    p = (char*)malloc(sizeof(char) * 10);
    printf("%p\n", p);
    free(p);
}