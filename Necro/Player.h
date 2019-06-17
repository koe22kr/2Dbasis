#pragma once
#include "Chara.h"
#include "Charamgr.h"
#include "Dungeon.h"
#include "Weapon.h"

class Player :public Chara
{
public:
    int m_iWeapon_num; //1 소드 2브로드 3창 0 실패
   Weapon* m_My_Weapon;
    
  

    void Move();
    bool Mining();
    bool check_attack();
    WINT Attack();
    
    bool Weapon_swap(int weapon_num);
    void Process();
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

    Player();
    virtual ~Player();
};

