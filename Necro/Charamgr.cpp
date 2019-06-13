#include "Charamgr.h"
int World_Charactor_pos[40][50];
vector<Chara*> Charactor_list;
CAPOINT Player_Move_pos;
bool Move_flag;
void Charamgr::Load(int inx, int iny, int i, int k)
{

    if (World_Charactor_pos[iny + i][inx + k] > 0)
    {
        int chara_index = World_Charactor_pos[iny + i][inx + k];

        if (World_Charactor_pos[iny + i][inx + k] == 1)
        {
            Chara_bit_mgr.m_Obj_list[0]->m_pos = { k * 48.f,i * 48.f-48 };
//            Chara_bit_mgr.m_Obj_list[1]->m_pos = { k * 48.f,i * 48.f - 30 };
        }
        else
        {
           Chara_bit_mgr.m_Obj_list[chara_index]->m_pos = { k * 48.f,i * 48.f-48 };// m_pos ���� �ɸ����� m_chara_pos �� �ٲ���
        }


    }
}
bool Charamgr::Init()   
{
    Chara_bit_mgr.Load_Bitmap_Script(L"../../data/chara.txt");
    Chara_bit_mgr.m_Obj_list[0]->Scale(2.0, 2.0);
    Chara_bit_mgr.m_Obj_list[0]->Setrt(0, 4);
    Chara_bit_mgr.m_Obj_list[1]->Scale(2.0, 2.0);
    Chara_bit_mgr.m_Obj_list[1]->Setrt(0, 4);
//    Chara_bit_mgr.m_Obj_list[1]->Scale(2.0, 2.0);
    Chara* chara = new Player;
//    Chara_bit_mgr.m_Obj_list[0]->m_pos = { 40,6 };
    chara->m_Chara_pos = { 40, 6 };
    chara->Chara_num = 1;
    Chara* skeleton = new Enemy;
    
    World_Charactor_pos[6][40] = 1;
    Charactor_list.push_back(chara);
    
    
    Chara_bit_mgr.Init();
   // Make_chara();
    return true;
}
bool Charamgr::Frame()  //������ ������ ���⼭ ����
{//����Ʈ ���鼭 �� ���� ļ�� �����ֱ�.
   
    if (Move_flag)
    {
        Move_chara();
    }
    Chara_bit_mgr.Frame();
    
    return true;
}
bool Charamgr::Render() 
{
    Chara_bit_mgr.Render();
    return true;
}
bool Charamgr::Release()
{
    Chara_bit_mgr.Release();
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
void Charamgr::Move_chara()//ļ�� ����Ʈ mapȭ ����
{
    

    m_fDelta_time += 10 * g_fSecondPerFrame; //0.5�� ���� �̵�

    for (int i = 0;i<Charactor_list.size();i++)
    {
        Charactor_list[i]->Action_point += 1;
        Charactor_list[i]->Process();//���� �ѹ����� ���μ��� �ϰ� �� ����

            if (m_fDelta_time >= 1)
            {
                Move_flag = false;
                Move_done = true;
                m_fDelta_time = 0;

                POINT& temp = Charactor_list[i]->m_Chara_pos;

                World_Charactor_pos[temp.y][temp.x] = 0;

                temp.x += Charactor_list[i]->m_Move_pos.x;
                temp.y += Charactor_list[i]->m_Move_pos.y;
                World_Charactor_pos[temp.y][temp.x] = Charactor_list[i]->Chara_num;
                Charactor_list[i]->m_Move_pos = { 0,0 };
                //PostMessage(g_hWnd, WM_CHARA_MOVED, 0, 0);
                return;
            }
            if (Charactor_list[i]->m_Move_pos.x == 1)
            {
                Chara_bit_mgr.m_Obj_list[i]->Setrt(0,4);
                m_jump_step = 1;
                //������ ���� ����
            }
            else if ((Charactor_list[i]->m_Move_pos.x == -1))
            {
                Chara_bit_mgr.m_Obj_list[i]->Setrt(4, 8);
                m_jump_step = 1;
                //���� ���� ����
            }
            else if (Charactor_list[i]->m_Move_pos.y == 1)
            {

                m_jump_step = -1;
            }
            else if (Charactor_list[i]->m_Move_pos.y == -1)
            {
                m_jump_step = 1;
            }
            //for (auto chara : Chara_bit_mgr.m_Obj_list)
            Chara_bit_mgr.m_Obj_list[i]->m_pos.x += (40 * 10 * g_fSecondPerFrame * Charactor_list[i]->m_Move_pos.x);
            if (m_fDelta_time > 0.5f)
            {
                Chara_bit_mgr.m_Obj_list[i]->m_pos.y += (24 * 20 * g_fSecondPerFrame*Charactor_list[i]->m_bJump_flag*m_jump_step);
            }
            else if(m_fDelta_time<1)
            {
                Chara_bit_mgr.m_Obj_list[i]->m_pos.y -= (36 * 20 * g_fSecondPerFrame*Charactor_list[i]->m_bJump_flag*m_jump_step);
            }

    }
   // Player_Move_pos = { 0,0 };
}
Charamgr::Charamgr()
{
}


Charamgr::~Charamgr()
{
}
