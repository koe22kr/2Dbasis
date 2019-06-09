#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Bit.h"
#include "UI.h"
#include "Scene.h"
#include "Dungeon.h"

class Sample :public CACore
{
public:
    Dungeon dun;
    Scene scene;
    Bit bit;
    UI ui;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

    void KeyCheck();



    Sample();
    virtual ~Sample();
};

