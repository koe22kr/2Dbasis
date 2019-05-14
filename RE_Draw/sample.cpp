#include "Sample.h"

LRESULT		Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
    {
        int kkk = 0;
    }break;
    }
    return 1;
}
bool Sample::Init()
{
    I_SoundMgr.Load("battle37.mp3");
    return true;
}
int AA, BB;
bool Sample::Frame()
{
    DWORD dwState = I_Input.KeyCheck('Z');
    if (dwState == KEY_PUSH)
    {
       // I_SoundMgr.PlayBGM();
    }
    if (dwState == KEY_UP)
    {
         BB = 10;
    }
    dwState = I_Input.KeyCheck('X');
    if (dwState == KEY_PUSH)
    {
        I_SoundMgr.Paused();
    }
    dwState = I_Input.KeyCheck('C');
    if (dwState == KEY_PUSH)
    {
        I_SoundMgr.Stop();
    }

    dwState = I_Input.KeyCheck(VK_LEFT);
    DWORD dwState2 = I_Input.KeyCheck(VK_CONTROL);
    if (dwState == KEY_PUSH && dwState2 == KEY_PUSH)
    {
        INT AA = 0;
    }
    if (I_Input.m_dwMouseState[0] == KEY_PUSH)
    {
        int kkk = 0;
    }
    if (I_Input.m_dwMouseState[1] == KEY_PUSH)
    {
        int kkk = 0;
    }
    if (I_Input.m_dwMouseState[2] == KEY_PUSH)
    {
        int kkk = 0;
    }
    return true;
}

Sample::Sample()
{
}

Sample::~Sample()
{
}

//WINRUN(0, 0, 720, 480); //int APIENTRY wWinMain(_In_ HINSTANCE hInstance,                 //wWinMain -시작.
                          //    _In_opt_ HINSTANCE hPrevInstance,
                          //    _In_ LPWSTR    lpCmdLine,
                          //    _In_ int       nCmdShow){}
WINRUN_DEFAULT; /*{Sample test_window; test_window.InitWindow(hInstance,0,0,800,600); test_window.Run();}*/
//#define WINRUN(x,y,width,height) /*{Sample test_window; test_window.InitWindow(hInstance,x,y,width,height); test_window.Run();}*/   //윈 메인 해야 hInstance 할당받고. init해서 창 띄우고, run해서 작업시작