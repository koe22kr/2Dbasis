#pragma once
#include "CAStd.h"
#include "Std.h"
class Chara
{
public:
    int Chara_num;
    int m_iHp;
    int m_iAtk;
    POINT m_Chara_pos;
    POINT m_Move_pos;
    int cur_rt_set_num;
    vector<WINT> start_end_rt_set_list;
    WINT cur_WINT;
    //bool m_bChara_move_flag;
    bool m_bJump_flag;
    virtual bool Init();

    virtual void Process();

    virtual void Move();
    virtual bool Mining();
    virtual void Attack();

    bool Chara_active_flag;

    int Action_point;
    int Action_delay;

    Chara();
    virtual ~Chara();
};

