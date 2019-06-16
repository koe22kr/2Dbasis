#pragma once
#include "CABitmapMgr.h"
#include "CAStd.h"
#include "CACore.h"
#include "Bit.h"
#include "UI.h"
#include "Dungeon.h"
#include "Charamgr.h"
#include "Std.h"
class Scene
{
public:
    int Scene_num;

   static Dungeon dun;
   static vector<Scene> scene;
   static Bit bit;
   static UI ui;
   static Charamgr cha;



    virtual bool Init();
    virtual bool Frame() ;
    virtual  bool Render();
    virtual bool Release() ;


    Scene();
    virtual ~Scene();
};

