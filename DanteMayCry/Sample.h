#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Dante.h"
#include "CAScene.h"
class Sample :public CACore
{
public: 
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    
    void KeyCheck();
    CAScene title;
    CAScene game;
    CAScene* Cur_Scene = &title;


    Sample();
    virtual ~Sample();
};

