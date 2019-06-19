#include "Enemy.h"


void Enemy::Process()
{
    /*if(m_bDead_flag)
    {
        return;
    }*/
    
    //Change_rt(4, 8);
    if (Chara_active_flag&&Action_point >= Action_delay)
    {

        POINT target_pos = Astar();

        if (target_pos.x != 0 || target_pos.y != 0) //이동0 ==[이동경로 없음]
        {

        
            m_Move_pos.x = target_pos.x - m_Chara_pos.x;
            m_Move_pos.y = target_pos.y - m_Chara_pos.y;
            WINT result;
            result = Attack();
        
            if (result.x == 0)
            {

                m_Move_pos.x = target_pos.x - m_Chara_pos.x;
                m_Move_pos.y = target_pos.y - m_Chara_pos.y;
                Move();
                m_bJump_flag = true;
            }
        }
        Action_point -= Action_delay;
        active_motion_flag = !active_motion_flag;  //+2

    }

        //이동 알고리즘
        //타겟 pos 선정
        //타겟 pos if(플레이어)  
        //          어택
        //    아니면 무브
        //   rt 기본(0,4) 설정
        
        //Change_rt(0, 4);
    

}
void Enemy::Move()

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
}
bool Enemy::Mining()
{
    return true;
}
WINT Enemy::Attack()
{
    WINT attack_result;
    WINT target1 = { m_Chara_pos.x + m_Move_pos.x,m_Chara_pos.y + m_Move_pos.y };

    
    for (int i = 0; i < Charactor_list.size(); i++)
    {
        int num = World_Charactor_pos[target1.y][target1.x];
        if (num == 1)
        {
            I_SoundMgr.PlaySE("en_skel_attack_melee.ogg");
            I_SoundMgr.PlaySE("vo_cad_hurt_06.ogg");
            Charactor_list[num - 1]->m_iHp -= 1;
            attack_result = { 1,0 };
        }
    }



    if (attack_result.x == 1)
    {
        CABitmapObject* atk;
        vector<RECT> rtlist = { {0,0,27,24},{27,0,27,24},{54,0,27,24} ,{81,0,27,24},{108,0,27,24} };
        atk = Action_bitmap_mgr.Load_Object(L"swipe_enemy.bmp");
        atk->Setobject(L"swipe_enemy", 5,
            (m_Chara_pos.x + m_Move_pos.x - start_pos.x) * 48,
            (m_Chara_pos.y + m_Move_pos.y - start_pos.y) * 48 - 55,
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

    return { 0,0 };
}
void Enemy::Change_rt(int start_rt, int end_rt)
{
    
}


POINT Enemy::Astar()
{
    path.clear();

    Pather start_pather;
    start_pather.pos.x = Charactor_list[Chara_num-1]->m_Chara_pos.x;
    start_pather.pos.y = Charactor_list[Chara_num-1]->m_Chara_pos.y;
    
    Pather target_pather;
    target_pather.pos.x = Charactor_list[0]->m_Chara_pos.x;
    target_pather.pos.y = Charactor_list[0]->m_Chara_pos.y;
    

    Pather* cur_pather = new Pather(start_pather);

    Openlist.insert(cur_pather);
    
    cur_pather->direction =cur_pather->Getdirection();
    while (!Openlist.empty())
    {
        cur_pather = *Openlist.begin();
        for (Pather* temp : Openlist)
        {
            temp->direction = temp->Getdirection();

            if (cur_pather->direction > temp->direction)
            {
                cur_pather = temp;
            }
        }
        if (cur_pather->pos.x == target_pather.pos.x&&
            cur_pather->pos.y == target_pather.pos.y)
        {
            
            break;
        }
        if (cur_pather->Score > 8)
        {
            
            break;
        }
        Closelist.insert(cur_pather);
        Openlist.erase(cur_pather);   //안되면 find 클래스 쓰자...
        

        for(POINT step : Direction_for_search)
        {
            
            Pather* temp = new Pather;
            temp->pos.x = cur_pather->pos.x + step.x;
            temp->pos.y = cur_pather->pos.y + step.y;
            temp->Score = cur_pather->Score + 1;
            temp->direction=temp->Getdirection();
            
            if (Dungeon_world[temp->pos.y][temp->pos.x] != 0 ||!(
                World_Charactor_pos[temp->pos.y][temp->pos.x] == 0||
                World_Charactor_pos[temp->pos.y][temp->pos.x] == 1))
            {
                continue;
            }

            Pather* search_pather = find_Pather_in_openlist(Closelist,temp);
            if(search_pather == nullptr)
            {
                temp->pre_pather = cur_pather;
                Openlist.insert(temp);

            }
            else if (search_pather->Score>temp->Score)
            {
                search_pather->pre_pather = cur_pather;
                search_pather->Score = temp->Score;
                delete temp;
            }

             
            
        }
        


    }
  if (cur_pather->pos.x != target_pather.pos.x 
      || cur_pather->pos.y != target_pather.pos.y)
  {
      release();
      return { 0,0 };

  }
  
  while (cur_pather->pre_pather!=nullptr)
  {
      path.insert(path.begin(), cur_pather->pos);
      cur_pather = cur_pather->pre_pather;
  }
  release();
  return path[0];
        
}

bool Enemy::release()
{
    for (auto a : Openlist)
    {
        if (a != nullptr)
        {
            delete a;
            a = nullptr;
        }
    }
    Openlist.clear();
    for (auto b : Closelist)
    {
        if (b != nullptr)
        {
            delete b;
            b = nullptr;
        }
    }
    Closelist.clear();
    return true;
}

Pather* Enemy::find_Pather_in_openlist(set<Pather*> openlist,Pather* newpather)
{
    for (Pather* search : openlist)
    {
        if (search->pos.x == newpather->pos.x&&
            search->pos.y == newpather->pos.y)
        {
            return search;
        }
        
    }
    return nullptr;
}

bool Enemy::Init()
{
    Direction_for_search.push_back({ 0, 1 });
    Direction_for_search.push_back({ 1, 0 });
    Direction_for_search.push_back({ 0, -1 }); 
    
    Direction_for_search.push_back({ -1, 0 });
    
    return true;
}

Enemy::Enemy()
{
    Action_delay = 2;
    m_iHp = 2;
    
}


Enemy::~Enemy()
{
}



Pather::Pather()
{
}

Pather::~Pather()
{
}
int Pather::Getdirection()
{
    int x = abs(pos.x - Charactor_list[0]->m_Chara_pos.x);
    int y = abs(pos.y - Charactor_list[0]->m_Chara_pos.y);
    return x + y;

}