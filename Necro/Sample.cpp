#include "Sample.h"
#include "CAStd.h"
#include "Scene_Title.h"
#include "Scene_Dungeon.h"

POINT start_pos;

bool Sample::Init()
{
    //BGM
    I_SoundMgr.Load("zone1_2.ogg");
    I_SoundMgr.Load("zone1_1.ogg");
    I_SoundMgr.Load("zone3_2c.ogg");
    //UI
    I_SoundMgr.Load("select2.mp3");
    I_SoundMgr.Load("select.mp3");
    //ACT
    I_SoundMgr.Load("parry.ogg");
    I_SoundMgr.Load("vo_cad_melee_2_02.ogg");
    I_SoundMgr.Load("vo_cad_melee_3_04.ogg");
    I_SoundMgr.Load("vo_cad_melee_4_01.ogg");
    //+
    I_SoundMgr.Load("vo_cad_hurt_06.ogg");
    I_SoundMgr.Load("vo_cad_death_01.ogg");
    //DIG
    I_SoundMgr.Load("mov_dig_fail.ogg");
    I_SoundMgr.Load("mov_dig_dirt.ogg");
    //ENEMY
    I_SoundMgr.Load("en_skel_attack_melee.ogg");
    I_SoundMgr.Load("en_skel_death.ogg");
    I_SoundMgr.Load("main.mp3");
    Cur_scene = new Scene_Title;
    Cur_scene->Init();
    return true;
}

void Sample::Scene_change(int scene_num)
{
    if (m_iCur_Scene_num != scene_num)
    {
        if (scene_num == 1)
        {
            Cur_scene->Release();
            delete Cur_scene;
            Cur_scene = new Scene_Title;
            Cur_scene->Init();
            Cur_scene->m_iphase_num = 0;
            Cur_scene->Frame();
        }
        if (scene_num == 2)
        {
            Cur_scene->Release();
            delete Cur_scene;
            Cur_scene = new Scene_Dungeon;
            Cur_scene->Init();
            Cur_scene->m_iphase_num = 0;
            Cur_scene->Frame();
        }
    }

}
bool Sample::Frame() 
{

    Scene_change(Cur_scene->m_iNext_Scene_num);
    if (!Charactor_list.empty())
    {
        Cur_scene->ui.dis_count_hp = 10-Charactor_list[0]->m_iHp;
        if (Charactor_list[0]->m_iHp <= 0)
        {
            Scene_change(1);
        }
    }
    Cur_scene->Frame();
    return true;
}
bool Sample::Render()
{
    Cur_scene->Render();
    return true;
}
bool Sample::Release()
{

    Cur_scene->Release();
    return true;
}
//LRESULT		Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    //PostMessage(g_hWnd, WM_UICONTRLMSG, dwWParam, dwLParam);
//    DWORD dwWParam=0;
//    DWORD dwLParam=0;
//    PostMessage(g_hWnd, WM_CAMERA_MOVE, dwWParam, dwLParam);
//        return 1;
//}

//void Sample::KeyCheck()
//{
//
//
//    DWORD dwState = I_Input.KeyCheck('W');
//    if (dwState == KEY_PUSH)
//    {
//        if (bit.Bit_success_flag)
//        {
//            Player_Move_pos = { 0,-1 };
//            Move();
//            bit.Bit_success_flag = false;
//        }
//    }
//    dwState = I_Input.KeyCheck('S');
//    if (dwState == KEY_PUSH)
//    {
//        if (bit.Bit_success_flag)
//        {
//            Player_Move_pos = { 0,1 };
//            Move();
//            bit.Bit_success_flag = false;
//        }
//    }
//    dwState = I_Input.KeyCheck('A');
//    if (dwState == KEY_PUSH)
//       
//    {
//        if (bit.Bit_success_flag)
//        {
//            Player_Move_pos = { -1,0 };
//            Move();
//            bit.Bit_success_flag = false;
//        }
//    }
//    dwState = I_Input.KeyCheck('D');
//    if (dwState == KEY_PUSH)
//    {
//        if (bit.Bit_success_flag)
//        {
//            Player_Move_pos = { 1,0 };
//            Move();
//            bit.Bit_success_flag = false;
//        }
//    }
//    
//}


Sample::Sample()
{
    int a = 0;
}

Sample::~Sample()
{
}

WINRUN_DEFAULT;
