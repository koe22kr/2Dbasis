#include "Charamgr.h"

int World_Charactor_pos[40][50];
vector<Chara*> Charactor_list;
bool Move_flag;

void Charamgr::Dead_Check()
{
    for (int i = 0; i < Charactor_list.size(); i++)
    {
        if (Charactor_list[i]->m_iHp <= 0)
        {
            if (Charactor_list[i]->Chara_num == 1)
            {
                I_SoundMgr.PlaySE("vo_cad_death_01.ogg");
            }
            if (Charactor_list[i]->Chara_num == 2)
            {
                //I_SoundMgr.PlaySE("en_skel_death.ogg");
            }
            World_Charactor_pos[Charactor_list[i]->m_Chara_pos.y][Charactor_list[i]->m_Chara_pos.x] = 0;
                Charactor_list[i]->m_Move_pos = { 0,0 };
                Charactor_list[i]->m_Chara_pos = { 0,0 };
               
                //Chara_bit_mgr.m_Obj_list[i]->m_pos = { -100,-100 };
                Chara_bit_mgr.m_Obj_list[i]->m_bDraw_flag = false;
                
                Charactor_list[i]->m_bDead_flag = true;
            
          //  if(i==0)
          
        }
    }
}

void Charamgr::chara_init()
{
   //for (auto obj : Chara_bit_mgr.m_Obj_list)
   //{
   //    obj->m_bDraw_flag = false;
   //}
}

void Charamgr::Load(int inx, int iny, int i, int k)
{

    if (World_Charactor_pos[iny + i][inx + k] > 0)
    {
        int chara_index = World_Charactor_pos[iny + i][inx + k] - 1; //1번케릭은 0번 배열에 들어가 있음
        {
            Chara_bit_mgr.m_Obj_list[chara_index]->m_pos = { k * 48.f,i * 48.f - 48 };
            
        }
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
void Charamgr::New_skel(WINT pos)
{
    vector<RECT> rt = { {360 ,0 ,24 ,28},
{336,  0, 24, 28},
{312,  0, 24, 28},
{288,  0, 24, 28},
{0  , 28, 24, 28},
{24 , 28, 24, 28},
{48 , 28, 24, 28},
{72 , 28, 24, 28},
{264, 0 ,24 ,28 },
{240, 0 ,24 ,28 },
{216, 0 ,24 ,28 },
{192, 0 ,24 ,28 },
{96 , 28, 24, 28},
{120, 28, 24, 28},
{144, 28, 24, 28},
{168, 28, 24, 28} };
    int size = Charactor_list.size();
    //
    CABitmapObject* skel =  Chara_bit_mgr.Load_Object(L"skel2.bmp");
    skel->Setobject(L"sk2", 12, 0, 0, rt, false, true, 0.7);
  
    Chara* skeleton = new Enemy;
    skeleton->m_Chara_pos = { pos.x,pos.y };

    skeleton->Chara_num = 2;
    World_Charactor_pos[pos.y][pos.x] = skeleton->Chara_num;
    Charactor_list.push_back(skeleton);
    skel->Scale(2.0, 2.0);
    skeleton->start_end_rt_set_list.push_back({ 0, 4 });
    skeleton->start_end_rt_set_list.push_back({ 4, 8 });
    skeleton->start_end_rt_set_list.push_back({ 8, 12 });
    skeleton->start_end_rt_set_list.push_back({ 12, 16 });
    skeleton->cur_rt_set_num = 0;
    skel->Setrt(0, 4);
    skeleton->m_bJump_flag = 1;


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
    skeleton->start_end_rt_set_list.push_back({ 0, 4 });
    skeleton->start_end_rt_set_list.push_back({ 4, 8 });
    skeleton->start_end_rt_set_list.push_back({ 8, 12 });
    skeleton->start_end_rt_set_list.push_back({ 12, 16 });
    skeleton->cur_rt_set_num = 0;
    Chara_bit_mgr.m_Obj_list[1]->Setrt(0, 4);
    skeleton->m_bJump_flag = 1;
    
   

 //Chara* skeleton2 = new Enemy;
 //skeleton2->m_Chara_pos = {39,6 };


 //skeleton2->Chara_num = 3;
 //World_Charactor_pos[6][39] = skeleton2->Chara_num;
 //Charactor_list.push_back(skeleton2);
 //Chara_bit_mgr.m_Obj_list[2]->Scale(2.0, 2.0);
 //skeleton2->start_end_rt_set_list.push_back({ 0, 4 });
 //skeleton2->start_end_rt_set_list.push_back({ 4, 8 });
 //skeleton2->start_end_rt_set_list.push_back({ 8, 12 });
 //skeleton2->start_end_rt_set_list.push_back({ 12, 16 });
 //skeleton2->cur_rt_set_num = 0;
 //Chara_bit_mgr.m_Obj_list[2]->Setrt(0, 4);
 //skeleton2->m_bJump_flag = 1;
 //   

 //Chara* skeleton3 = new Enemy;
 //skeleton3->m_Chara_pos = { 38,6 };


 //skeleton3->Chara_num = 4;
 //World_Charactor_pos[6][38] = skeleton3->Chara_num;
 //Charactor_list.push_back(skeleton3);
 //Chara_bit_mgr.m_Obj_list[3]->Scale(2.0, 2.0);
 //skeleton3->start_end_rt_set_list.push_back({ 0, 4 });
 //skeleton3->start_end_rt_set_list.push_back({ 4, 8 });
 //skeleton3->start_end_rt_set_list.push_back({ 8, 12 });
 //skeleton3->start_end_rt_set_list.push_back({ 12, 16 });
 //skeleton3->cur_rt_set_num = 0;
 //skeleton3->m_bJump_flag = 1;
 //Chara_bit_mgr.m_Obj_list[3]->Setrt(0, 4);


 //Chara* skeleton4 = new Enemy;
 //skeleton4->m_Chara_pos = { 39,7 };


 //skeleton4->Chara_num = 5;
 //World_Charactor_pos[7][39] = skeleton4->Chara_num;
 //Charactor_list.push_back(skeleton4);
 //Chara_bit_mgr.m_Obj_list[4]->Scale(2.0, 2.0);
 //skeleton4->start_end_rt_set_list.push_back({ 0, 4 });
 //skeleton4->start_end_rt_set_list.push_back({ 4, 8 });
 //skeleton4->start_end_rt_set_list.push_back({ 8, 12 });
 //skeleton4->start_end_rt_set_list.push_back({ 12, 16 });
 //skeleton4->cur_rt_set_num = 0;
 //skeleton4->m_bJump_flag = 1;
 //Chara_bit_mgr.m_Obj_list[4]->Setrt(0, 4);



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
    Chara::Action_bitmap_mgr.Render();
    return true;
}
bool Charamgr::Release()
{
    Chara_bit_mgr.Release();
    Charactor_list[0]->Action_bitmap_mgr.Release();
    for (auto a : Charactor_list)
    {
        delete a;
    }
    Charactor_list.clear();
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

    m_fDelta_time2 += 10 * g_fSecondPerFrame; //10배  초 동안 이동
    
    
   
    
    if (m_fDelta_time2 >= 1)
    {
        Move_done = true;
        Move_flag = 0;
        m_fDelta_time2 = 0;
        /*rt_num++;
        rt_num=rt_num % 2;*/
        for (int k = 0; k < Charactor_list.size(); k++)
        {
           
            if (Charactor_list[k]->m_bDead_flag == false)
            {
                Charactor_list[k]->Action_point += 1;
                Charactor_list[k]->m_Move_pos = { 0,0 };
            }
        }
        return;
    }
   
    for (int i = 0;i<Charactor_list.size();i++)
    {
       if (Charactor_list[i]->m_bDead_flag == true)
       {
           continue;
       }
        Charactor_list[i]->Process();//리듬 한번마다 프로세싱 하게 할 예정
        Dead_Check();
        if (Charactor_list[i]->m_Move_pos.x == 1)
        {
            Charactor_list[i]->cur_rt_set_num = 0;
           /* if (Charactor_list[i]->active_motion_flag)
            {
                Charactor_list[i]->cur_rt_set_num += 2;
            }*/
            //Chara_bit_mgr.m_Obj_list[i]->Setrt(Charactor_list[i]->start_end_rt_set_list[Charactor_list[i]->cur_rt_set_num]);
            //                Chara_bit_mgr.m_Obj_list[i]->Setrt(0, 4);
            Charactor_list[i]->m_jump_step = 1;
            //오른쪽 보고 있을
        }
        else if ((Charactor_list[i]->m_Move_pos.x == -1))
        {
            Charactor_list[i]->cur_rt_set_num = 1;
            /*if (Charactor_list[i]->active_motion_flag)
            {
                Charactor_list[i]->cur_rt_set_num += 2;
            }*/
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
        //모션 rt
        if (Charactor_list[i]->active_motion_flag == true && Charactor_list[i]->cur_rt_set_num < 2)
        {
            Charactor_list[i]->cur_rt_set_num += 2;
        }
        if (Charactor_list[i]->active_motion_flag == false && Charactor_list[i]->cur_rt_set_num >= 2)
        {
               
            Charactor_list[i]->cur_rt_set_num -= 2;
        }
        


        if (Charactor_list[i]->m_Move_pos.x != 0|| Charactor_list[i]->m_Move_pos.y != 0)
        {

            Chara_bit_mgr.m_Obj_list[i]->Setrt(Charactor_list[i]->start_end_rt_set_list[Charactor_list[i]->cur_rt_set_num]);
        }

      
       
       
       
           
           
            Chara_bit_mgr.m_Obj_list[i]->m_pos.x += (40 * 10 * g_fSecondPerFrame * Charactor_list[i]->m_Move_pos.x*Charactor_list[i]->m_bJump_flag);
            if (m_fDelta_time2 > 0.5f)
            {
                Chara_bit_mgr.m_Obj_list[i]->m_pos.y += (24 * 20 * g_fSecondPerFrame*Charactor_list[i]->m_bJump_flag*Charactor_list[i]->m_jump_step);
            }
            else if (m_fDelta_time2 >= 0)
            {
                Chara_bit_mgr.m_Obj_list[i]->m_pos.y -= (30 * 20 * g_fSecondPerFrame*Charactor_list[i]->m_bJump_flag*Charactor_list[i]->m_jump_step);
            }

            Charactor_list[i]->m_jump_step = 0;
    }
    int list_size = Charactor_list.size();
    //for (int i = 0; i < list_size; i++)
    //{
    //    //if (Charactor_list[i]->m_bDead_flag == true)
    //    //{
    //    //    Charactor_list.erase(Charactor_list.begin() + i);
    //    //    i--;
    //    //    list_size--;
    //    //    World_Charactor_pos[Charactor_list[i]->m_Chara_pos.y][Charactor_list[i]->m_Chara_pos.x] == 0;
    //    //}
    //
    //}
   // Player_Move_pos = { 0,0 };
}
Charamgr::Charamgr()
{
}


Charamgr::~Charamgr()
{

}
