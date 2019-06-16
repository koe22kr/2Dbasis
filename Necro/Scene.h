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
//   static vector<Scene> scene; 사용할지 생각해보고.필요 없을것 같음;
   static Bit bit;
   static UI ui;
   static Charamgr cha;



   int m_iphase_num;
   float m_fScene_deltatime_1s=0;
   bool m_Scene_scale_flag;
    virtual bool Init();
    virtual bool Frame() ;
    virtual  bool Render();
    virtual bool Release() ;


    Scene();
    virtual ~Scene();
};

