#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Black_Jack.h"
#include "resource.h"
class Sample :public CACore
{
public:

    Connecter* g_pConnecter;//생성자필
public:
    //LRESULT MsgProc2(/*HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam*/);
    Black_Jack BJ;
    bool m_Dlg_Flag;
    

    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    void Join_Thread();
    Sample();
    virtual ~Sample();
};

