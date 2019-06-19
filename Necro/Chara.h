#pragma once
#include "CAStd.h"
#include "Std.h"
#include "CABitmapMgr.h"
class Chara
{
public:
    int Chara_num;
    int m_iHp;
    int m_iAtk;
    POINT m_Chara_pos;
    POINT m_Move_pos;
    bool active_motion_flag;
    int cur_rt_set_num;
    vector<WINT> start_end_rt_set_list;
    //WINT cur_WINT;
    //bool m_bChara_move_flag;
    bool m_bJump_flag;
    float m_jump_step;
    static CABitmapMgr Action_bitmap_mgr;
    bool m_bDead_flag=false;
    

    virtual bool Init();
    virtual bool Frame();
    virtual bool Render();
    virtual bool Release();
    virtual void Process();

    virtual void Move();
    virtual bool Mining();
    WINT Attack();
    virtual bool Weapon_swap(int weapon_num);
    bool Chara_active_flag;

    int Action_point;
    int Action_delay;

    Chara();
    virtual ~Chara();
};

