#include "Enemy.h"


void Enemy::Process()
{

    if (Chara_active_flag&&Action_point>Action_delay)
    {
        int x = abs(Charactor_list[Chara_num]->m_Chara_pos.x - Charactor_list[0]->m_Chara_pos.x);
        int y = abs(Charactor_list[Chara_num]->m_Chara_pos.y - Charactor_list[0]->m_Chara_pos.y);
        
        //이동 알고리즘
        //타겟 pos 선정
        //타겟 pos if(플레이어)  
        //          어택
        //    아니면 무브
        //
        //
        //   rt 기본(0,4) 설정
    }

}
void Enemy::Move()
{
}
void Enemy::Mining()
{
}
void Enemy::Attack()
{
}
void Enemy::Change_rt()
{

}
bool Enemy::Astar()
{
    POINT start_pos;
    start_pos.x = Charactor_list[Chara_num]->m_Chara_pos.x;
    start_pos.y = Charactor_list[Chara_num]->m_Chara_pos.y;
    POINT target_pos;
    target_pos.x = Charactor_list[0]->m_Chara_pos.x;
    target_pos.y = Charactor_list[0]->m_Chara_pos.y;
    POINT cur_pos = start_pos;
    while (start_pos.x != target_pos.x|| start_pos.y != target_pos.y)
    {
        vector <POINT> Openlist;
        vector <POINT> Closelist;
        Closelist.push_back(cur_pos);
        
        for(POINT step : Direction_for_search)
        {
            POINT temp = cur_pos;
            temp.x =+ step.x;
            temp.y =+ step.y;
            if (Dungeon_world[temp.y][temp.x] == 0 &&
                World_Charactor_pos[temp.y][temp.x] == 0)
            {
                Openlist.push_back(temp);
            }

            
        }
    }
        
}


bool Enemy::Init()
{
    Direction_for_search[0] = { 0, -1 };
    Direction_for_search[1] = { 0, 1 };
    Direction_for_search[2] = { -1, 0 };
    Direction_for_search[3] = { 1, 0 };
}

Enemy::Enemy()
{
   

}


Enemy::~Enemy()
{
}
