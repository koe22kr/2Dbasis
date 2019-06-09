#pragma once
#include "CACore.h"
#include "Std.h"
#include "CABitmapMgr.h"

class Dungeon
{
public:
    CABitmapMgr Dunmgr;
    vector<RECT> rt_list = { { 0,0,0,0 }, { 0,0,24,42 }, { 0,0,24,42 }, { 0,0,24,42 },
                            { 0,144,24,42}, { 0,144,24,42 }, { 288,288,24,42 }, { 312,288,24,42 } };
    float m_fspeed=0.7;     //�������� �������� ������ �ʹ�.
    int m_iDungeon_size_x;//�� ������x
    int m_iDungeon_size_y;//�� ������y
    int m_iInput_Key;

    
    
    CAPOINT m_Camera_pos = { 20,20 }; //20ĭ�� ����
    
    CAPOINT m_Move_pos;  //����� �̵���ġ �� ����.
    float m_fDelta_time;
    bool m_bCamera_move_flag=false;

    
    POINT rending_map_size = { 20,16 };//¦���� ���
    int map[40][50];
    virtual bool Init();
    virtual bool Frame();
    virtual  bool Render();
    virtual bool Release();
    void Make_dungeon();
    void Camera_move();
    void Dungeon_move();
    Dungeon();
    virtual ~Dungeon();
};

