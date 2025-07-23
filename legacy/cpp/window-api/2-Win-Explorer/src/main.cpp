// Query data trough the exploer . but with overengineering backgrounds. //
//
// Comments
// 1. Use only unsigend, when the intiger is not allowed to be negative. Otherwise when the situation is not so strictly, just use an int.
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <ctime>
#include <shobjidl.h> // shell object interface definition language
#include <map> // shell object interface definition language

#include "WinAPIWrapper.h"
#include "OrderAlgorythms.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    char*   path   = {};
    uint8_t szpath = {};

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    IFileOpenDialog* pfileOpen;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileOpenDialog, reinterpret_cast<void**>(&pfileOpen));
    if (SUCCEEDED(hr))
    {
        hr = pfileOpen->Show(NULL);
        if (SUCCEEDED(hr))
        {
            IShellItem* pItem;
            hr = pfileOpen->GetResult(&pItem);
            if (SUCCEEDED(hr))
            {
                PWSTR pszpathName;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszpathName);
                if (SUCCEEDED(hr))
                {
                    // if the first 3 values are the same -> delete these an mark as end of the string | an pointer array at the end of the index is setting next to the first again.
                    path = (char*)pszpathName;
                    int8_t ptrlen = CkPtrstrLRep(path, 3); 
                    MessageBox(NULL, pszpathName, L"Your selected path:", MB_OK | MB_ICONINFORMATION);
                    CoTaskMemFree(pszpathName);
                }
                pItem->Release(); // ULONG
            }
        }
        pfileOpen->Release();
    }
    CoUninitialize();

    WCHAR msgTxt[100] = {};
    char* filename = new char[szpath];
    filename = SFileInPath(path, szpath);

    wsprintf(msgTxt, L"Do you want to open ", filename);
    MessageBox(NULL, msgTxt, L"Info", MB_OK | MB_ICONINFORMATION);

    delete[] filename;
    return 0;

    
#pragma    region WinStuff
    // windows Stuff. | DEACTIVATED
    MainWindow mainWin;
    if (!mainWin.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
    {
        return 1;
    }

    ShowWindow(mainWin.Window(), nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
#pragma endregion WinStuff
}
