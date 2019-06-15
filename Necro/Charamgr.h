#pragma once
#include "Chara.h"
#include "CAStd.h"
#include "CABitmapMgr.h"
#include "Std.h"
#include "Player.h"
#include "Enemy.h"
class Charamgr
{
public:
    
    CABitmapMgr Chara_bit_mgr;
   
    
   
    float m_fDelta_time;
   //기본 0 무브 1
    
    //void Make_chara();
    void Move_chara();

    void Load(int inx, int iny, int i, int k);
    //float m_jump_step;
    bool Move_done;
    
    int rt_num;

    LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    
    virtual bool Init();
    virtual bool Frame();
    virtual bool Render();
    virtual bool Release();
    Charamgr();
    virtual ~Charamgr();
};

