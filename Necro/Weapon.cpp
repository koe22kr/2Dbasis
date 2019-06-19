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
    POWER = 1;
}
Gratesword::~Gratesword()
{

}

Spear::Spear()
{
    POWER = 1;
}
Spear::~Spear()
{
}
bool Weapon::Check(WINT target)
{
    return false;
}

WINT Weapon::Attack(POINT chara_pos, POINT chara_move_pos)
{
    
    return { 0,0 };
}

bool Sword::Check(WINT target)
{
    return false;
}
WINT Sword::Attack(POINT chara_pos, POINT chara_move_pos)
{
    WINT target1 = { chara_pos.x + chara_move_pos.x,chara_pos.y + chara_move_pos.y };

    
        for (int i = 0; i < Charactor_list.size(); i++)
        {
            int num = World_Charactor_pos[target1.y][target1.x];
            if (num!=0)
            {
                Charactor_list[num-1]->m_iHp -= POWER;
                return { 1,0 };
            }
        }
    
    return { 0,0 };
}   


bool Gratesword::Check(WINT target)
{
    return false;
}
WINT Gratesword::Attack(POINT chara_pos, POINT chara_move_pos)
{
    WINT target1 = { chara_pos.x + chara_move_pos.x,chara_pos.y + chara_move_pos.y };
    WINT target2;
    WINT target3;
    if (chara_move_pos.x != 0)
    {
        target2.x = target1.x;
        target2.y = target1.y + 1;

        target3.x = target1.x;
        target3.y = target1.y - 1;
    }
    else if (chara_move_pos.y != 0)
    {
        target2.x = target1.x + 1;
        target2.y = target1.y;

        target3.x = target1.x - 1;
        target3.y = target1.y;
    }
    bool success_flag = false;
    
    
    for (int i = 0; i < Charactor_list.size(); i++)
    {
        int num = World_Charactor_pos[target1.y][target1.x];
        if (num != 0)
        {
            Charactor_list[num-1]->m_iHp -= POWER;
            return { 2,0 };
        }
    }
    
    for (int i = 0; i < Charactor_list.size(); i++)
    {
        int num = World_Charactor_pos[target2.y][target2.x];
        if (num != 0)
        {
            Charactor_list[num-1]->m_iHp -= POWER;
            return { 2,0 };
        }
    }

    for (int i = 0; i < Charactor_list.size(); i++)
    {
        int num = World_Charactor_pos[target3.y][target3.x];
        if (num != 0)
        {
            Charactor_list[num-1]->m_iHp -= POWER;
            return { 2,0 };
        }
    }
    if (success_flag)
    {
        return { 2,0 };
    }
    return { 0,0 };
/*
    if (World_Charactor_pos[target_pos.y][target_pos.x] != 0|| 
        World_Charactor_pos[target_pos2.y][target_pos2.x] != 0||
        World_Charactor_pos[target_pos3.y][target_pos3.x] != 0)
    {
        

        for (int i = 0; i < Charactor_list.size(); i++)
        {
            if (Charactor_list[i]->m_Chara_pos.x == target_pos3.x
                &&Charactor_list[i]->m_Chara_pos.y == target_pos3.y)
            {
                Charactor_list[i]->m_iHp -= 1;

            }
        }

        for (int i = 0; i < Charactor_list.size(); i++)
        {
            if (Charactor_list[i]->m_Chara_pos.x == target_pos2.x
                &&Charactor_list[i]->m_Chara_pos.y == target_pos2.y)
            {
                Charactor_list[i]->m_iHp -= 1;
               
            }
        }
     

        for (int i = 0; i < Charactor_list.size(); i++)
        {
            if (Charactor_list[i]->m_Chara_pos.x == target_pos.x
                &&Charactor_list[i]->m_Chara_pos.y == target_pos.y)
            {
                Charactor_list[i]->m_iHp -= 1;
                return { 2,i };
            }
        }
        
        
    }*/
   
}
bool Spear::Check(WINT target)
{
    return false;
}

WINT Spear::Attack(POINT chara_pos, POINT chara_move_pos)
{
    WINT target1 = { chara_pos.x + chara_move_pos.x,chara_pos.y + chara_move_pos.y };
    WINT target2;

    if (chara_move_pos.x == -1)
    {
        target2.x = target1.x - 1;
        target2.y = target1.y;
    }
    else if (chara_move_pos.x == 1)
    {
        target2.x = target1.x + 1;
        target2.y = target1.y;
    }
    else if (chara_move_pos.y == -1)
    {
        target2.x = target1.x;
        target2.y = target1.y  -1;
    }
    else if (chara_move_pos.y ==1)
    {
        target2.x = target1.x;
        target2.y = target1.y + 1;
    }

    bool success_flag = false;
   
    for (int i = 0; i < Charactor_list.size(); i++)
    {
        int num = World_Charactor_pos[target1.y][target1.x];
        if (num != 0)
        {
            Charactor_list[num-1]->m_iHp -= POWER;
            return { 3,0 };
        }
    }
    
   
    for (int i = 0; i < Charactor_list.size(); i++)
    {
        int num = World_Charactor_pos[target2.y][target2.x];
        if (num != 0)
        {
            Charactor_list[num-1]->m_iHp -= POWER;
            return { 3,0 };
        }
    }
    
    if (success_flag)
    {
        return { 3,0 };
    }
    return { 0,0 };
}
