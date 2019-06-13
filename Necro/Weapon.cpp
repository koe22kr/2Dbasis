#include "Weapon.h"
Weapon::Weapon()
{
}
Weapon::~Weapon()
{
}
Sword::Sword()
{
    POWER = 1;
}
Sword::~Sword()
{


}
Gratesword::Gratesword()
{
    POWER = 2;
}
Gratesword::~Gratesword()
{

}

Spear::Spear()
{
    POWER = 2;
}
Spear::~Spear()
{
}


bool Weapon::Attack(int target_x, int target_y, int chara_x, int chara_y)
{
    
    return true;    
}

bool Sword::Attack(int target_x, int target_y, int chara_x, int chara_y)
{
    if (World_Charactor_pos[target_y][target_x] != 0)
    {
        POINT target1 = { target_x,target_y };
        for (int i = 0; i < Charactor_list.size(); i++)
        {
            if (Charactor_list[i]->m_Chara_pos.x == target1.x
                &&Charactor_list[i]->m_Chara_pos.y == target1.y)
            {
                Charactor_list[i]->m_iHp -= 1;
            }
        }
       
       
       // DWORD wparam = MAKELONG(1, 0);
       // DWORD lparam = MAKELONG(target_x, target_y);
       //
       // PostMessage(g_hWnd, WM_WEAPON, wparam, lparam);
        return true;
    }
    return false;
}

bool Gratesword::Attack(int target_x, int target_y, int chara_x, int chara_y)
{
    return true;
}

bool Spear::Attack(int target_x, int target_y, int chara_x, int chara_y)
{
    return true;
  
  
  

  
  
  
  
}
