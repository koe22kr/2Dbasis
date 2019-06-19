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
   
    float m_fDelta_time2;
   //기본 0 무브 1
    //void Make_chara();
    void Move_chara();

    void Load(int inx, int iny, int i, int k);
    //float m_jump_step;
    bool Move_done;
    void Dead_Check();
    int rt_num;

    LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void New_skel(WINT pos);

    void chara_init();

    virtual bool Init();
    virtual bool Frame();
    virtual bool Render();
    virtual bool Release();
    Charamgr();
    virtual ~Charamgr();
};

