#include "Player.h"

void Player::Process()
{

    POINT target_pos;
    target_pos.x = m_Chara_pos.x + Player_Move_pos.x;
    target_pos.y = m_Chara_pos.y + Player_Move_pos.y;
    if (Dungeon_world[target_pos.y][target_pos.x] == FLOOR)
    {
        if(Attack(target_pos.x, target_pos.y, m_Chara_pos.x, m_Chara_pos.y))
        {
            return;
        }
        else
        {
            Move();
            return;
        }
    }
    else
        /*if (Dungeon_world[target_pos.y][target_pos.x] == WALL1
        || Dungeon_world[target_pos.y][target_pos.x] == WALL2
        || Dungeon_world[target_pos.y][target_pos.x] == WALL3
        || Dungeon_world[target_pos.y][target_pos.x] == DOOR1
        || Dungeon_world[target_pos.y][target_pos.x] == DOOR2)*/
    {
        Mining(target_pos.x, target_pos.y);
        return;
    }

}
bool Player::Mining(int target_x, int target_y)
{
    if (Dungeon_world[target_y][target_x] == WALL1
        || Dungeon_world[target_y][target_x] == WALL2
        || Dungeon_world[target_y][target_x] == WALL3
        || Dungeon_world[target_y][target_x] == DOOR1
        || Dungeon_world[target_y][target_x] == DOOR2)
    {
        Dungeon_world[target_y][target_x] = FLOOR;
        Player_Move_pos = {0,0};
        m_bJump_flag = false;
        return true;
    }
    //마이닝 실패
    
        return false;
}
void Player::Move()
{
    m_bJump_flag = true;
    
    m_Move_pos.x = Player_Move_pos.x;
    m_Move_pos.y = Player_Move_pos.y;


}

bool Player::Attack(int target_x, int target_y, int chara_x, int chara_y)
{
    if (m_My_Weapon->Attack(target_x, target_y, chara_x, chara_y))
    {
        return true;
    }
    return false;
}

bool Player::Init()   
{
    
    return true;
}
bool Player::Frame()  
{
   

    return true;
}
bool Player::Render() 
{
    return true;
}
bool Player::Release()
{
    return true;
}
Player::Player()
{
    m_iHp = 10;
    //m_Chara_pos = { 40,6 };
    m_My_Weapon = new Sword;
    //기본무기 여기서 지급하기
    
}


Player::~Player()
{
}
