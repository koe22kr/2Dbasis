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

WINT Weapon::Attack(POINT chara_pos, POINT chara_move_pos)
{
    
    return { 0,0 };
}

WINT Sword::Attack(POINT chara_pos, POINT chara_move_pos)
{
    POINT target_pos;
    target_pos.y = chara_pos.y + chara_move_pos.y;
    target_pos.x = chara_pos.x + chara_move_pos.x;
    if (World_Charactor_pos[target_pos.y][target_pos.x] != 0)
    {

        for (int i = 0; i < Charactor_list.size(); i++)
        {
            if (Charactor_list[i]->m_Chara_pos.x == target_pos.x
                &&Charactor_list[i]->m_Chara_pos.y == target_pos.y)
            {
                Charactor_list[i]->m_iHp -= 1;
                return { 1,i };
            }
        }
    }
    return { 0,0 };
}   



WINT Gratesword::Attack(POINT chara_pos, POINT chara_move_pos)
{
    POINT target_pos;
    target_pos.y = chara_pos.y + chara_move_pos.y;
    target_pos.x = chara_pos.x + chara_move_pos.x;
    POINT target_pos2;
    POINT target_pos3;
    
    if (chara_move_pos.x !=0)
    {
        target_pos2.y = target_pos.x;
        target_pos2.y = target_pos.y + 1;

        target_pos3.y = target_pos.x;
        target_pos3.y = target_pos.y - 1;

    }
    else if (chara_move_pos.y != 0)
    {
        target_pos2.x = target_pos.x + 1;
        target_pos2.y = target_pos.y;

        target_pos3.x = target_pos.x - 1;
        target_pos3.y = target_pos.y;
    }

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
        
        
    }
    return { 0,0 };
}

WINT Spear::Attack(POINT chara_pos, POINT chara_move_pos)
{
    POINT target_pos;
    target_pos.y = chara_pos.y + chara_move_pos.y;
    target_pos.x = chara_pos.x + chara_move_pos.x;
    POINT target_pos2;

    if (chara_move_pos.x == 1)
    {
        target_pos2.x = target_pos.x + 1;
        target_pos2.y = target_pos.y;

    }
    else if (chara_move_pos.x == -1)
    {
        target_pos2.x = target_pos.x - 1;
        target_pos2.y = target_pos.y;
    }
    else if (chara_move_pos.y == 1)
    {
        target_pos2.x = target_pos.x;
        target_pos2.y = target_pos.y + 1;
    }
    else if (chara_move_pos.y == -1)
    {
        target_pos2.x = target_pos.x;
        target_pos2.y = target_pos.y - 1;
    }


    if (World_Charactor_pos[target_pos.y][target_pos.x] != 0 ||
        World_Charactor_pos[target_pos2.y][target_pos2.x] != 0)
    {
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
                return { 3,i };
            }
        }


    }
    return { 0,0 };
}
