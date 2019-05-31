#include "CACore.h"
HDC		 g_hOffScreenDC;
HDC		 g_hScreenDC;

bool CACore::Init()
{
    return true;
}

bool CACore::Frame()
{
    return true;
}

bool CACore::PreRender()
{
    PatBlt(m_hOffScreenDC,
        0, 0, m_Src_rtClient.right,
        m_Src_rtClient.bottom, PATCOPY);
    return true;
}

bool CACore::Render()
{
    return true;
}

bool CACore::PostRender()
{
   
    // DC -> DC
    BitBlt(m_hScreenDC, 0, 0,
        m_Src_rtClient.right,
        m_Src_rtClient.bottom,
        m_hOffScreenDC,
        0,
        0, SRCCOPY);
    return true;
}

bool CACore::Release()
{
    return true;
}

bool CACore::CACoreInit()
{
    m_hScreenDC = GetDC(m_hWnd);
    g_hScreenDC = m_hScreenDC;

    m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
    m_hOffScreenBitmap = CreateCompatibleBitmap(
        m_hScreenDC, m_Src_rtClient.right,
        m_Src_rtClient.bottom);
    SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

    g_hOffScreenDC = m_hOffScreenDC;

    m_bkColor = RGB(0, 0, 0);
    m_hbrBack = CreateSolidBrush(m_bkColor);
    SelectObject(m_hOffScreenDC, m_hbrBack);

    I_BITMAPMGR.Init();
    m_Timer.Init();
    I_Input.Init();
    I_SoundMgr.Init();
    return Init();
}
bool CACore::CACoreFrame()
{
    I_BITMAPMGR.Frame();
    m_Timer.Frame();
    I_Input.Frame();
    I_SoundMgr.Frame();
    return Frame();
    
}
bool CACore::CACoreRender()
{
    PreRender();
    Render();
    I_BITMAPMGR.Render();
    PostRender();

    m_Timer.Render();
    I_Input.Render();
    return Render();
    return true;
}
bool CACore::CACoreRelease()
{
    Release();

    DeleteObject(m_hOffScreenDC);           //4개 라고 하는데 샘 예재랑 비교해보기.
    DeleteObject(m_hOffScreenBitmap);       //
    DeleteObject(m_hbrBack);                //
    ReleaseDC(m_hWnd, m_hScreenDC);
    I_BITMAPMGR.Release();
    m_Timer.Release();
    I_Input.Release();
    I_SoundMgr.Release();
    return Release();
}
bool CACore::Run()
{
    CACoreInit();                                     
    MSG msg = { 0 };
    // WM_QUIT -> FALSE
    // 메세지 큐에서 하나하나씩 가져온다.
    //while (GetMessage(&msg, nullptr, 0, 0))
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // 메세지 번역
            DispatchMessage(&msg);	// 메세지 프로시져 전달	
            MessageProc(msg);
        }
        else
        {
            // 게임로직
            CACoreFrame(); // 게임계산
            CACoreRender();// 게임드로우
            //Sleep(1); //1미리초 쉬는건데 필요한가?
        }
    }
    CACoreRelease(); // 게임 종료 
    
    return true;        //정상종료
}

void CACore::MessageProc(MSG msg)
{
    //m_Input.MsgProc(msg);//마우스 프록시저...
    I_Input.MouseCheck(msg);
}

CACore::CACore()
{
}


CACore::~CACore()
{
}
