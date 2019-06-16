#include "Charamgr.h"
int World_Charactor_pos[40][50];
vector<Chara*> Charactor_list;
//CAPOINT Player_Move_pos;
bool Move_flag;
void Charamgr::Load(int inx, int iny, int i, int k)
{

    if (World_Charactor_pos[iny + i][inx + k] > 0)
    {
        int chara_index = World_Charactor_pos[iny + i][inx + k] - 1; //1번케릭은 0번 배열에 들어가 있음

        Chara_bit_mgr.m_Obj_list[chara_index]->m_pos = { k * 48.f,i * 48.f - 48 };

//        if (World_Charactor_pos[iny + i][inx + k] == 1)
//        {
//        
////            Chara_bit_mgr.m_Obj_list[1]->m_pos = { k * 48.f,i * 48.f - 30 };
//        }
//        else
//        {
//           Chara_bit_mgr.m_Obj_list[chara_index]->m_pos = { k * 48.f,i * 48.f-48 };// m_pos 에서 케릭터의 m_chara_pos 로 바꾸자
//        }


    }
}
bool Charamgr::Init()   
{
    Chara_bit_mgr.Load_Bitmap_Script(L"../../data/chara.txt");
    
    Chara* chara = new Player;
    chara->m_Chara_pos = { 42, 7 };
    chara->Chara_num = 1;
    World_Charactor_pos[7][42] = chara->Chara_num;
    Charactor_list.push_back(chara);
    Chara_bit_mgr.m_Obj_list[0]->Scale(2.0, 2.0);
    Charactor_list[0]->start_end_rt_set_list.push_back({ 0, 4 });
    Charactor_list[0]->start_end_rt_set_list.push_back({ 4, 8 }); //rt_set 2개; 시간나면 스크립트로 빼자
    Charactor_list[0]->cur_rt_set_num = 0;
    Chara_bit_mgr.m_Obj_list[0]->Setrt(0,4);
    Charactor_list[0]->m_bJump_flag = 1;

    Chara* skeleton = new Enemy;
    skeleton->m_Chara_pos = { 40,6 };
    skeleton->Chara_num = 2;
    World_Charactor_pos[6][40] = skeleton->Chara_num;
    Charactor_list.push_back(skeleton);
    Chara_bit_mgr.m_Obj_list[1]->Scale(2.0, 2.0);
    Charactor_list[1]->start_end_rt_set_list.push_back({ 0, 4 });
    Charactor_list[1]->start_end_rt_set_list.push_back({ 4, 8 });
    Charactor_list[1]->cur_rt_set_num = 0;
    Chara_bit_mgr.m_Obj_list[1]->Setrt(0, 4);
    Charactor_list[1]->m_bJump_flag = 1;
    
    
   
    for (auto a : Charactor_list)
    {
        a->Init();
    }
    Chara_bit_mgr.Init();
    Charactor_list[0]->Action_bitmap_mgr.Init();
   // Make_chara();
    return true;
}
bool Charamgr::Frame()  //죽은몹 릴리즈 여기서 하자
{//리스트 돌면서 몹 무프 캬라 시켜주기.
    for (int i=0; i<Charactor_list.size();i++)
    {
       // Charactor_list[i]->cur_rt_set_num;
       
        
    }
    
    if (Move_flag)
    {
        Move_chara();
    }
    Chara_bit_mgr.Frame();
    Charactor_list[0]->Action_bitmap_mgr.Frame();
    return true;
}
bool Charamgr::Render() 
{
    Chara_bit_mgr.Render();
    Charactor_list[0]->Action_bitmap_mgr.Render();
    return true;
}
bool Charamgr::Release()
{
    Chara_bit_mgr.Release();
    Charactor_list[0]->Action_bitmap_mgr.Release();
    return true;
}
//void Charamgr::Make_chara()
//{
//    
//
//
//    POINT start_pos = { m_Chara_pos.x - (rending_arr_size.x / 2), m_Chara_pos.y - (rending_arr_size.y / 2) };
//
//    for (int i = 0; i < 20; i++)
//    {
//        for (int k = 0; k < 16; k++)
//        {
//            if (start_pos.x + k > 49 || start_pos.x + k < 0 || start_pos.y + i > 39 || start_pos.y + i < 0)
//                continue;
//
//            if (World_Charactor_pos[start_pos.y + i][start_pos.x + k] == 1)
//            {
//                Chara_bit_mgr.m_Obj_list[0]->m_pos = { k * 48.f,i * 48.f };
//                Chara_bit_mgr.m_Obj_list[1]->m_pos = { k * 48.f,i * 48.f };
//            }
//            
//        }
//    }
//}
void Charamgr::Move_chara()//캬라 리스트 map화 가능
{

    m_fDelta_time2 += 10 * g_fSecondPerFrame; //0.5초 동안 이동
    
    
   
    
    if (m_fDelta_time2 >= 1)
    {
        Move_done = true;
        Move_flag = 0;
        m_fDelta_time2 = 0;
        /*rt_num++;
        rt_num=rt_num % 2;*/
        for (int k = 0; k < Charactor_list.size(); k++)
        {
            Charactor_list[k]->Action_point += 1;
            Charactor_list[k]->m_Move_pos = { 0,0 };
            
        }
        return;
    }
   
    for (int i = 0;i<Charactor_list.size();i++)
    {
        if (Charactor_list[i]->m_Move_pos.x != 0)
        {

            Chara_bit_mgr.m_Obj_list[i]->Setrt(Charactor_list[i]->start_end_rt_set_list[Charactor_list[i]->cur_rt_set_num]);
        }
        Charactor_list[i]->Process();//리듬 한번마다 프로세싱 하게 할 예정

        if (Charactor_list[i]->m_Move_pos.x == 1)
        {
            Charactor_list[i]->cur_rt_set_num = 0;
            //Chara_bit_mgr.m_Obj_list[i]->Setrt(Charactor_list[i]->start_end_rt_set_list[Charactor_list[i]->cur_rt_set_num]);
            //                Chara_bit_mgr.m_Obj_list[i]->Setrt(0, 4);
            Charactor_list[i]->m_jump_step = 1;
            //오른쪽 보고 있을
        }
        else if ((Charactor_list[i]->m_Move_pos.x == -1))
        {
            Charactor_list[i]->cur_rt_set_num = 1;
            //Chara_bit_mgr.m_Obj_list[i]->Setrt(Charactor_list[i]->start_end_rt_set_list[Charactor_list[i]->cur_rt_set_num]);
            //                Chara_bit_mgr.m_Obj_list[i]->Setrt(4, 8);
            Charactor_list[i]->m_jump_step = 1;
            //왼쪽 보고 있을
        }
        else if (Charactor_list[i]->m_Move_pos.y == 1)
        {

            Charactor_list[i]->m_jump_step = -0.7;
        }
        else if (Charactor_list[i]->m_Move_pos.y == -1)
        {
            Charactor_list[i]->m_jump_step = 1;
        }
       
       
       
           
           
            Chara_bit_mgr.m_Obj_list[i]->m_pos.x += (40 * 10 * g_fSecondPerFrame * Charactor_list[i]->m_Move_pos.x*Charactor_list[i]->m_bJump_flag);
            if (m_fDelta_time2 > 0.5f)
            {
                Chara_bit_mgr.m_Obj_list[i]->m_pos.y += (24 * 20 * g_fSecondPerFrame*Charactor_list[i]->m_bJump_flag*Charactor_list[i]->m_jump_step);
            }
            else if (m_fDelta_time2 < 1)
            {
                Chara_bit_mgr.m_Obj_list[i]->m_pos.y -= (36 * 20 * g_fSecondPerFrame*Charactor_list[i]->m_bJump_flag*Charactor_list[i]->m_jump_step);
            }

            Charactor_list[i]->m_jump_step = 0;
    }
   // Player_Move_pos = { 0,0 };
}
Charamgr::Charamgr()
{
}


Charamgr::~Charamgr()
{
}
