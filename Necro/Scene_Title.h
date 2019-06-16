#pragma once
#include "Scene.h"
class Scene_Title:public Scene
{
public:

    virtual bool Init();
    virtual bool Frame();
    virtual bool Render();
    virtual bool Release();


    Scene_Title();
    virtual ~Scene_Title();
};

