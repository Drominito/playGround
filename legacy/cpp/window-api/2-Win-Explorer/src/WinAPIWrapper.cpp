#include <Windows.h>
#include "WinAPIWrapper.h"

//Protected:
PCWSTR MainWindow::ClassName() const { return L"Sample Window Class"; }
//Public:


BaseWindow::BaseWindow() : m_hwnd(NULL) {}
HWND BaseWindow::Window() const { return m_hwnd; }

LRESULT CALLBACK BaseWindow::HandleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    PAINTSTRUCT ps{};
    RECT windowRect; RECT boxRect;
    POINT cursor = { 0, 0 };
    int bkgrndcol = 5;
    constexpr const unsigned int squreSize = 32; // x-pixels.
    GetWindowRect(hwnd, &boxRect);
    int screenWidth = boxRect.right - boxRect.left;

    GetCursorPos(&cursor);

    cursor.x -= boxRect.left;
    cursor.y -= boxRect.top;

    boxRect.left = cursor.x - squreSize;
    boxRect.top = cursor.y - squreSize;

    boxRect.right = cursor.x;
    boxRect.bottom = cursor.y;

    switch (msg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        } break;
        case WM_CREATE:
        {
        } break;

        case WM_KEYDOWN:
        {
            switch (wp)
            {
            case VK_SPACE: RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE); break;
            case VK_RETURN:
            {
                InvalidateRect(hwnd, &boxRect, TRUE);
                RedrawWindow(hwnd, &windowRect, NULL, RDW_UPDATENOW | RDW_ERASENOW);
            } break;
            }
        } break;

        case WM_PAINT:
        {
            HDC hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &windowRect);
            FillRect(hdc, &windowRect, (HBRUSH)(COLOR_WINDOW + bkgrndcol));
            FillRect(hdc, &boxRect, (HBRUSH)(COLOR_WINDOW + bkgrndcol + 2));
            EndPaint(hwnd, &ps);

        } break;
        default:
        {
        } break;
    } return DefWindowProc(hwnd, msg, wp, lp);
}

BOOL BaseWindow::Create(
    PCWSTR lpWindowName,
    DWORD dwStyle,
    DWORD dwExStyle = 0,
    int x = CW_USEDEFAULT,
    int y = CW_USEDEFAULT,
    int nWidth = CW_USEDEFAULT,
    int nHeight = CW_USEDEFAULT,
    HWND hWndParent = 0,
    HMENU hMenu = 0
)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = BaseWindow::HandleMessage;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = ClassName();
    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(
        dwExStyle, ClassName(),
        lpWindowName, dwStyle,
        x, y, nWidth, nHeight,
        hWndParent, hMenu,
        GetModuleHandle(NULL),
        this
    );
    return (m_hwnd ? TRUE : FALSE);
}
