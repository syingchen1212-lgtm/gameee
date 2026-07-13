#include <windows.h>
#include <string>

#define IDC_MATCH 1001
#define IDC_SPELL 1002
#define IDC_BACK 1003

static HINSTANCE g_hInst = nullptr;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LessonWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OpenLessonWindow(const wchar_t* title, const wchar_t* message);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    g_hInst = hInstance;

    WNDCLASSW wc{};
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"MainWindowClass";
    RegisterClassW(&wc);

    WNDCLASSW lessonClass{};
    lessonClass.lpfnWndProc = LessonWndProc;
    lessonClass.hInstance = hInstance;
    lessonClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    lessonClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    lessonClass.lpszClassName = L"LessonWindowClass";
    RegisterClassW(&lessonClass);

    HWND hwnd = CreateWindowW(
        L"MainWindowClass",
        L"Google 學習站",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 520, 320,
        nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        CreateWindowW(
            L"STATIC",
            L"Google 學習",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            0, 0, 500, 48,
            hwnd, nullptr, g_hInst, nullptr);

        CreateWindowW(
            L"BUTTON",
            L"中英配對",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            80, 90, 140, 40,
            hwnd, (HMENU)IDC_MATCH, g_hInst, nullptr);

        CreateWindowW(
            L"BUTTON",
            L"英單拼寫",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            280, 90, 140, 40,
            hwnd, (HMENU)IDC_SPELL, g_hInst, nullptr);

        SetWindowTextW(GetDlgItem(hwnd, IDC_MATCH), L"中英配對");
        SetWindowTextW(GetDlgItem(hwnd, IDC_SPELL), L"英單拼寫");
        return 0;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == IDC_MATCH && HIWORD(wParam) == BN_CLICKED) {
            OpenLessonWindow(L"中英配對", L"歡迎進入中英配對練習！\n請點選單字與對應英文。" );
            return 0;
        }
        if (LOWORD(wParam) == IDC_SPELL && HIWORD(wParam) == BN_CLICKED) {
            OpenLessonWindow(L"英單拼寫", L"歡迎進入英單拼寫練習！\n請依照提示拼出單字。" );
            return 0;
        }
        break;
    }
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            DestroyWindow(hwnd);
            return 0;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void OpenLessonWindow(const wchar_t* title, const wchar_t* message) {
    HWND lessonHwnd = CreateWindowW(
        L"LessonWindowClass",
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 480, 280,
        nullptr, nullptr, g_hInst, nullptr);

    if (lessonHwnd != nullptr) {
        ShowWindow(lessonHwnd, SW_SHOWDEFAULT);
        UpdateWindow(lessonHwnd);
        SetForegroundWindow(lessonHwnd);
        SetFocus(lessonHwnd);
    }
}

LRESULT CALLBACK LessonWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        CreateWindowW(
            L"STATIC",
            L"學習頁面",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            20, 20, 200, 24,
            hwnd, nullptr, g_hInst, nullptr);

        CreateWindowW(
            L"STATIC",
            L"",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            20, 60, 420, 80,
            hwnd, nullptr, g_hInst, nullptr);

        CreateWindowW(
            L"BUTTON",
            L"返回主畫面",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            150, 170, 140, 36,
            hwnd, (HMENU)IDC_BACK, g_hInst, nullptr);

        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
        return 0;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BACK && HIWORD(wParam) == BN_CLICKED) {
            DestroyWindow(hwnd);
            return 0;
        }
        break;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            DestroyWindow(hwnd);
            return 0;
        }
        break;
    case WM_DESTROY:
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
