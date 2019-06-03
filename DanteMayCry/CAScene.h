#pragma once
#include "CAStd.h"
#include "CABitmapMgr.h"

class CAScene
{
public:
    
   virtual bool Init();
   virtual bool Frame();
   virtual  bool Render();
   virtual bool Release();
    CAScene();
    virtual ~CAScene();
};

