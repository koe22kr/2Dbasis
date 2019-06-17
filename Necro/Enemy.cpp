#include "Enemy.h"


void Enemy::Process()
{
    
    //Change_rt(4, 8);
    if (Chara_active_flag&&Action_point>=Action_delay)
    {
        
        POINT target_pos =  Astar();
        if (target_pos.x != 0 || target_pos.y != 0) //이동0 ==[이동경로 없음]
        {
            if (Charactor_list[0]->m_Chara_pos.x == target_pos.x&&
                Charactor_list[0]->m_Chara_pos.y == target_pos.y)
            {
                Attack();
            }
            else
            {
                
                m_Move_pos.x = target_pos.x - m_Chara_pos.x;
                m_Move_pos.y = target_pos.y - m_Chara_pos.y;
                Move();
                m_bJump_flag = true;
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
       //if (cur_pather->Score > 8)
       //{
       //    break;
       //}
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