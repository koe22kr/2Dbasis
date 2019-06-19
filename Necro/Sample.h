#pragma once
#include "Scene.h"

class Sample :public CACore
{
public:
    int m_iCur_Scene_num;
    Scene* Cur_scene;
    void Scene_change(int scene_num);

    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    
//    void KeyCheck();
//    POINT m_Shake_step = { 0,0 };   //가능하면 랜덤값 주고 마인잉 할때 진동..
//    LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


    Sample();
    virtual ~Sample();
};

