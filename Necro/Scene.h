#pragma once
#include "CABitmapMgr.h"
class Scene
{
public:
    CABitmapMgr Scenemgr;
    virtual bool Init();
    virtual bool Frame() ;
    virtual  bool Render();
    virtual bool Release() ;


    Scene();
    virtual ~Scene();
};

