#pragma once
#include "Scene.h"

class Scene_Dungeon:public Scene
{
public:
    int Scene_num;

    /*Dungeon dun;
    vector<Scene> scene;
    Bit bit;
    UI ui;
    Charamgr cha;*/
    bool Init();
    bool Frame();
    bool Render();
    bool Release();


  //  LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void Make();


    Scene_Dungeon();
    virtual ~Scene_Dungeon();
};

