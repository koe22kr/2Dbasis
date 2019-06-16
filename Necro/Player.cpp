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
            if (World_Charactor_pos[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x]!=0&&
                World_Charactor_pos[m_Chara_pos.y + m_Move_pos.y][m_Chara_pos.x + m_Move_pos.x] != Chara_num)
            {
                Attack();
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

WINT Player::Attack()
{
    WINT attack_result;
    attack_result = m_My_Weapon->Attack(m_Chara_pos, m_Move_pos);
    if (attack_result.x==0)
    {
        return { 0,0 };
    }
    else if (attack_result.x == 1)//검
    {
        CABitmapObject* atk;
        vector<RECT> rtlist = { {0,0,24,24},{24,0,24,24},{48,0,24,24} };
        
        atk = Action_bitmap_mgr.Load_Object(L"swipe_dagger.bmp");
        atk->Setobject(L"swipe_dagger", 3,
            (m_Chara_pos.x + m_Move_pos.x - start_pos.x) * 48,
            (m_Chara_pos.y + m_Move_pos.y - start_pos.y) * 48-55,
            rtlist, false, false, 0.09f, 0.09f);
        atk->Scale(2, 2);

        if (m_Move_pos.y == -1)//상
        {
            atk->m_fAngle = 270;
        }
        if (m_Move_pos.x == -1)
        {
            atk->m_fAngle = 180; //좌
        }
        if (m_Move_pos.y == +1)
        {
            atk->m_fAngle = 90;//아래
        }
        m_Move_pos = { 0,0 };
        m_bJump_flag = false;
        return attack_result;
    }
    else if (attack_result.x == 2)//그소
    {
        CABitmapObject* atk;
        vector<RECT> rtlist = { {0,0,24,72},{24,0,24,72},{48,0,24,72} };

        atk = Action_bitmap_mgr.Load_Object(L"swipe_broadsword.bmp");
        atk->Setobject(L"swipe_broadsword", 3, 
            (m_Chara_pos.x + m_Move_pos.x- start_pos.x)*48,
            (m_Chara_pos.y + m_Move_pos.y- start_pos.y)*48-55,
            rtlist, false, false, 0.09f, 0.09f);
        atk->Scale(2, 2);
        if (m_Move_pos.x == +1)
        {
            atk->m_pos.y -= 48;
        }
        if (m_Move_pos.y == -1)//상
        {
            atk->m_fAngle = 270;
        }
        if (m_Move_pos.x == -1)
        {
            atk->m_fAngle = 180; //좌
        }
        if (m_Move_pos.y == +1)
        {
            atk->m_fAngle = 90;//아래
        }

        m_Move_pos = { 0,0 };
        m_bJump_flag = false;
        return attack_result;
    }
    else if (attack_result.x == 3)//창
    {
        CABitmapObject* atk;
        vector<RECT> rtlist = { {0,0,48,24},{48,0,48,24},{96,0,48,24},{144,0,48,24} };

        atk = Action_bitmap_mgr.Load_Object(L"swipe_rapier.bmp");
        atk->Setobject(L"swipe_rapier", 4,
            (m_Chara_pos.x + m_Move_pos.x - start_pos.x)*48,
            (m_Chara_pos.y + m_Move_pos.y - start_pos.y)*48-55,
            rtlist, false, false, 0.09f, 0.09f);
        atk->Scale(2, 2);

        if (m_Move_pos.y == -1)//상
        {
            atk->m_fAngle = 270;
        }
        if (m_Move_pos.x == -1)
        {
            atk->m_fAngle = 180; //좌
        }
        if (m_Move_pos.y == +1)
        {
            atk->m_fAngle = 90;//아래
        }

        m_Move_pos = { 0,0 };
        m_bJump_flag = false;
        return attack_result;
    }
   
    return { 0, 0 };
}

bool Player::Weapon_swap(int weapon_num)
{
    delete m_My_Weapon;
    switch (weapon_num)
    {
        case 1: 
        {
            Weapon* new_weapon = new Sword;
            m_My_Weapon = new_weapon;
            break;
        }
        case 2:
        {
            Weapon* new_weapon = new Gratesword;
            m_My_Weapon = new_weapon;
            break;
        }
        case 3:
        {
            Weapon* new_weapon = new Spear;
            m_My_Weapon = new_weapon;
            break;
        }
        default:
            break;
    }
    return true;
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
    m_My_Weapon_num = 1;
    //기본무기 여기서 지급하기
    Action_delay = 1;
    Action_point = 1;
    
}


Player::~Player()
{
}
