#pragma once
#include <Windows.h>
#include <tchar.h>
#include <assert.h>

LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam);

class TWindow
{
public:
    //-----------------------
    //Global Variables
    //-----------------------    
    HINSTANCE   m_hInstance;    //인스턴스 핸들
    HWND    m_hWnd;             //윈도우 핸들
    DWORD   m_dwWindowStyle;    //윈도우 스타일
    RECT    m_reWindowBounds;   //윈도우 영역
    RECT    m_reWindowClinet;   //클라이언트 영역
    UINT    m_iWindowWidth;     //클라이언트 영역 가로크기
    UINT    m_iWindowHeight;    //클라이언트 영역 세로크기
    
public:
    // 윈도우 생성
    bool InitWindow(HINSTANCE hinstnce, int nCmdShow,const TCHAR* strWindowTitle);
    // 윈도우 위치화면 중앙으로 이동
  //  void CenterWindow(HWND hwnd) {};
public:
    //virtual bool Init();            //해당 클래스의 초기화를 담당
    //virtual bool Render() { return false; };          //해당 클래스의 매 프레임 계산을 담당
    //virtual bool Release() { return false; };         //해당 클래스의 매 프레임 랜더링을 담당
    virtual bool Run();             //메모리 소멸 및 객체 해제를 담당
    virtual LRESULT WndProc(HWND, UINT, WPARAM, LPARAM);
public:
    TWindow(void) {};
    virtual ~TWindow(void) {};

};

bool TWindow::InitWindow(HINSTANCE hInstance, int nCmdShow,const TCHAR* strWindowTitle)
{
    //Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &StaticWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TBasis3D10Sample";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    if (!RegisterClassEx(&wcex))
        return false;
    m_hInstance = hInstance;
    RECT rc{ 0,0,640,480 };
    //작업영역 (타이틀바/경계선/메뉴/스크롤바 등의 영역을 제외한 영역), 윈도우 스타일 메뉴여부
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    m_hWnd = CreateWindowEx(WS_EX_TOPMOST, L"TBasis3D10Sample", strWindowTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
    if (!m_hWnd)
        return false;
    ShowWindow(m_hWnd, nCmdShow);
    return true;
          
}
TWindow g_pWindow;
//-----------------------
// 메인 윈도우 프로시저
//-----------------------
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
    assert(&g_pWindow);
    return g_pWindow.WndProc(hWnd, message, wParam, IParam);
}

//-----------------------
//윈도우 프로지서
//-----------------------
LRESULT TWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, IParam);

}

bool TWindow::Run()
{
   // if (!Init())return false;
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (false/*!(Frame() || Render())*/)break;
        }
    }
    return false;
}