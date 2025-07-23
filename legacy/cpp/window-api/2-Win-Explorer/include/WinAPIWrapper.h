#pragma once
#include <Windows.h>


class MainWindow : public BaseWindow
{
public:
    PCWSTR ClassName() const override;
    //LRESULT HandleMessage(UINT uMsg, WPARAM wp, LPARAM lp);
};


class BaseWindow
{
protected:
    HWND m_hwnd;
    virtual PCWSTR ClassName() const = 0;
    //virtual LRESULT HandleMessage(UINT uMsg, WPARAM wp, LPARAM lp) = 0;
public:
    BaseWindow();
    ~BaseWindow();

    HWND Window() const;


    /*cursor.x = cursor.x + boxRect.left;
cursor.y = cursor.y + boxRect.top;*/
    static LRESULT CALLBACK HandleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);


    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
        );
};
