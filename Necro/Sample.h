#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Bit.h"
#include "UI.h"
#include "Scene.h"
#include "Dungeon.h"
#include "Charamgr.h"
#include "Std.h"

class Sample :public CACore
{
public:
    Dungeon dun;
    Scene scene;
    Bit bit;
    UI ui;
    Charamgr cha;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    
//void KeyCheck();
    
    POINT m_Shake_step = { 0,0 };   //가능하면 랜덤값 주자 mining 에 10~20사이 랜덤값 생성 대입.
  //  LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    
    void Move();
    void Make();

    Sample();
    virtual ~Sample();
};

