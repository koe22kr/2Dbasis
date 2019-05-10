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
    HINSTANCE   m_hInstance;    //�ν��Ͻ� �ڵ�
    HWND    m_hWnd;             //������ �ڵ�
    DWORD   m_dwWindowStyle;    //������ ��Ÿ��
    RECT    m_reWindowBounds;   //������ ����
    RECT    m_reWindowClinet;   //Ŭ���̾�Ʈ ����
    UINT    m_iWindowWidth;     //Ŭ���̾�Ʈ ���� ����ũ��
    UINT    m_iWindowHeight;    //Ŭ���̾�Ʈ ���� ����ũ��
    
public:
    // ������ ����
    bool InitWindow(HINSTANCE hinstnce, int nCmdShow,const TCHAR* strWindowTitle);
    // ������ ��ġȭ�� �߾����� �̵�
  //  void CenterWindow(HWND hwnd) {};
public:
    //virtual bool Init();            //�ش� Ŭ������ �ʱ�ȭ�� ���
    //virtual bool Render() { return false; };          //�ش� Ŭ������ �� ������ ����� ���
    //virtual bool Release() { return false; };         //�ش� Ŭ������ �� ������ �������� ���
    virtual bool Run();             //�޸� �Ҹ� �� ��ü ������ ���
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
    //�۾����� (Ÿ��Ʋ��/��輱/�޴�/��ũ�ѹ� ���� ������ ������ ����), ������ ��Ÿ�� �޴�����
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
// ���� ������ ���ν���
//-----------------------
LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
    assert(&g_pWindow);
    return g_pWindow.WndProc(hWnd, message, wParam, IParam);
}

//-----------------------
//������ ��������
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