#include "Player.h"

void Player::Process()
{
   // Action_point += 1;
    //POINT target_pos = { 0, 0};
    /*target_pos.x = m_Chara_pos.x + Player_Move_pos.x;
    target_pos.y = m_Chara_pos.y + Player_Move_pos.y;*/
    if (Action_point >= Action_delay)
    {
        Action_point -= Action_delay;
        if (Dungeon_world[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] == FLOOR)
        {
            if (World_Charactor_pos[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x])
            {
                //Attack();
                //어택

                //Player_Move_pos = { 0,0 };

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
            Mining();
            return;
        }
    }
}
bool Player::Mining()
{//        if(World_Charactor_pos[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x])

    if (Dungeon_world[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] == WALL1
        || Dungeon_world[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] == WALL2
        || Dungeon_world[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] == WALL3
        || Dungeon_world[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] == DOOR1
        || Dungeon_world[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] == DOOR2)
    {
        Dungeon_world[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] = FLOOR;
        m_Move_pos = { 0,0 };
        m_bJump_flag = false;
        return true;
    }
    //마이닝 실패
    
        return false;
}
void Player::Move()
{
    m_bJump_flag = true;
    if (World_Charactor_pos[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] == 0)
    {
        World_Charactor_pos[m_Chara_pos.y][m_Chara_pos.x] = 0;
        m_Chara_pos.x += m_Move_pos.x;
        m_Chara_pos.y += m_Move_pos.y;
        World_Charactor_pos[m_Chara_pos.y][m_Chara_pos.x] = Chara_num;
        //m_Move_pos = { 0,0 };
    }
   /* m_Move_pos.x = Player_Move_pos.x;
    m_Move_pos.y = Player_Move_pos.y;*/


}

bool Player::Attack(CAPOINT Move_pos)
{
  //  if (m_My_Weapon->Attack( chara_pos, chara_move_pos)
  //  {
  //      return true;
  //  }
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
    Action_delay = 1;
    Action_point = 1;
    
}


Player::~Player()
{
}
