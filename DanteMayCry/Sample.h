#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Dante.h"
#include "CAScene.h"
#include "CABitmapMgr.h"
class Sample :public CACore
{
public: 
    CABitmapMgr mgr;
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    
    void KeyCheck();
    CAScene title;
    CAScene game;
    CAScene* Cur_Scene;

    Sample();
    virtual ~Sample();
};

