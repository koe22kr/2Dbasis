#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Black_Jack.h"
#include "resource.h"
#include "Chat.h"
class Sample :public CACore
{
public:

    Connecter* g_pConnecter;//��������
public:
    //LRESULT MsgProc2(/*HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam*/);
    Black_Jack BJ;
    Chat chat;
    bool m_Dlg_Flag;
    
    


    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    void Join_Thread();
    Sample();
    virtual ~Sample();
};

