#include "TWindow.h"
class Sample :public TWindow
{
public:
    Sample(void) {};
    ~Sample(void) {};


};

int WINAPI wWinMain(
    HINSTANCE hInstance, 
    HINSTANCE hPrevinstance,
    LPWSTR ipCmdLine, 
    int nCmdShow)

{
    Sample gSample;
    if (!gSample.InitWindow(hInstance, nCmdShow, L"CreatWindow"))
    {
        MessageBox(0, _T("CreateWindow �ʱ�ȭ ����"), _T("Fatal error"), MB_OK);
        return 0;
    }
    ShowCursor(TRUE);
    gSample.Run();
    return 1;

}