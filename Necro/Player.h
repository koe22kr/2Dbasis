#pragma once
#include "Chara.h"
#include "Charamgr.h"
#include "Dungeon.h"
#include "Weapon.h"

class Player :public Chara
{
public:
    int m_iWeapon_num; //1 �ҵ� 2��ε� 3â 0 ����
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

