#pragma once
#include "Scene.h"

class Sample :public CACore
{
public:
    Scene* Cur_scene;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    
//    void KeyCheck();
//    POINT m_Shake_step = { 0,0 };   //�����ϸ� ������ �ְ� ������ �Ҷ� ����..
//    LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


    Sample();
    virtual ~Sample();
};

