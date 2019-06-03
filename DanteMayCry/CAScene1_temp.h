#pragma once
#include "CAScene.h"
class CAScene1_temp :public CAScene
{
public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    CAScene1_temp();
    virtual ~CAScene1_temp();
};

