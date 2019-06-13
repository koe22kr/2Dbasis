#pragma once
#include "Chara.h"
#include "Charamgr.h"
#include "Dungeon.h"
#include "Weapon.h"
class Player :public Chara
{
public:
    
   Weapon* m_My_Weapon;
    
  

    void Move();
    bool Mining(int target_x, int target_y);
    bool Attack(int target_x, int target_y, int chara_x, int chara_y);
    
    
    void Process();
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

    Player();
    virtual ~Player();
};

