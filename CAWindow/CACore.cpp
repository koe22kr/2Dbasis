#include "CACore.h"

bool CACore::Init()
{
    return true;
}
bool CACore::Frame()
{
    return true;
}
bool CACore::Render()
{
    return true;
}
bool CACore::Release()
{
    return true;
}

bool CACore::CACoreInit()
{
    m_Timer.Init();
    I_Input.Init();
    I_SoundMgr.Init();
    return Init();
}
bool CACore::CACoreFrame()
{
    m_Timer.Frame();
    I_Input.Frame();
    I_SoundMgr.Frame();
    return Frame();
    
}
bool CACore::CACoreRender()
{
    m_Timer.Render();
    I_Input.Render();
    
    return Render();
    return true;
}
bool CACore::CACoreRelease()
{
    m_Timer.Release();
    I_Input.Release();
    
    return Release();
    return true;
}
bool CACore::Run()
{
    CACoreInit();                                       //이놈때문에 코어의 init 계속 돈다.
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
            Sleep(1); //1미리초 쉬는건데 필요한가?
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
