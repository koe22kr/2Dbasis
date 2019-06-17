#pragma once
#include "Scene.h"
class Scene_Title:public Scene
{
public:

    virtual bool Init();
    virtual bool Frame();
    virtual bool Render();
    virtual bool Release();

    int m_icur_button_num;

    Scene_Title();
    virtual ~Scene_Title();
};

