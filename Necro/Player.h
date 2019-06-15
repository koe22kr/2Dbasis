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
    bool Mining();
    bool Attack(CAPOINT Player_Move_pos);
    
    
    void Process();
    bool Init();
    bool Frame();
    bool Render();
    bool Release();

    Player();
    virtual ~Player();
};

