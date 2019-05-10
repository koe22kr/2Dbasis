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
    CACoreInit();                                       //�̳𶧹��� �ھ��� init ��� ����.
    MSG msg = { 0 };
    // WM_QUIT -> FALSE
    // �޼��� ť���� �ϳ��ϳ��� �����´�.
    //while (GetMessage(&msg, nullptr, 0, 0))
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg); // �޼��� ����
            DispatchMessage(&msg);	// �޼��� ���ν��� ����	
            MessageProc(msg);
        }
        else
        {
            // ���ӷ���
            CACoreFrame(); // ���Ӱ��
            CACoreRender();// ���ӵ�ο�
            Sleep(1); //1�̸��� ���°ǵ� �ʿ��Ѱ�?
        }
    }
    CACoreRelease(); // ���� ���� 
    
    return true;        //��������
}

void CACore::MessageProc(MSG msg)
{
    //m_Input.MsgProc(msg);//���콺 ���Ͻ���...
    I_Input.MouseCheck(msg);
}

CACore::CACore()
{
}


CACore::~CACore()
{
}
