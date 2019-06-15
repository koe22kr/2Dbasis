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
    //float m_fspeed=0.7;     //전역으로 빼놓으면 좋을듯 싶다.
    int m_iDungeon_size_x;//맵 사이즈x
    int m_iDungeon_size_y;//맵 사이즈y
    int m_iInput_Key;

    bool m_bCamera_move_flag = false;

    POINT m_Camera_pos = { 41,7 }; //20칸만 뽑자    
    
    float m_fDelta_time;
    
 
   
    void Load(int inx, int iny, int i, int k);
    
    void Map_check(int x, int y,int count=0 );


    virtual bool Init();
    virtual bool Frame();
    virtual  bool Render();
    virtual bool Release();
    void Make_dungeon();
    
    void Dungeon_move();
    
    
    

    Dungeon();
    virtual ~Dungeon();
};

