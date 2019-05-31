#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Dante.h"
class Sample :public CACore
{
public: 
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    
    void KeyCheck();


    Sample();
    virtual ~Sample();
};

