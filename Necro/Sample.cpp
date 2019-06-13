#include "Sample.h"
#include "CAStd.h"
#include "CABitmapObject.h"
#include "CABitmapMgr.h"


bool Sample::Init()//모든 세팅은 이곳에서 하는게 나을듯.
{
    //I_BITMAPMGR.Load_Bitmap_Script(L"../../data/bitmap_object.txt");
    ////I_SoundMgr.
    ////UI = START EXIT OPTION.
    //I_BITMAPMGR.m_Obj_list[7]->m_bScale_flag = true;
    //// 
    //I_BITMAPMGR.m_Obj_list[7]->m_Desk_rt[0]->right = 400;
    //I_BITMAPMGR.m_Obj_list[7]->m_Desk_rt[0]->bottom = 400;
    dun.Init();
   // scene.Init();
   
    cha.Init();
    ui.Init();
    bit.Init();
    Make();
    return true;
}

bool Sample::Frame() //프래임은 Scene별
{
   
    dun.Frame();
    //scene.Frame();
    
    //    Cur_Scene->Frame();
    cha.Frame();
    ui.Frame();
    bit.Frame();
        

        if (cha.Move_done)
        {
            Make();
        }
    return true;
}
bool Sample::Render()
{
    
    dun.Render();
    cha.Render();
    //scene.Render();
   
    // Cur_Scene->Render();
   
   
    bit.Render();
    ui.Render();
    return true;
}
bool Sample::Release()
{
   dun.Release();
    //scene.Release();
   
    bit.Release();
    ui.Release();
    // title.Release(); //신 전환시 릴리즈 할지는 생각해보기
    // game.Release();
    cha.Release();
    return true;
}
//
//LRESULT		Sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//    //PostMessage(g_hWnd, WM_UICONTRLMSG, dwWParam, dwLParam);
//    DWORD dwWParam=0;
//    DWORD dwLParam=0;
//    PostMessage(g_hWnd, WM_CAMERA_MOVE, dwWParam, dwLParam);
//        return 1;
//}
void Sample::Move()
{
    //cha.Move_flag =1;  //이거 관리만... 이동 리던값으로 참 거짓 처리하면 되려나?

    //////////////////////////////Charactor_list[0]->m_bChara_move_flag = true;
   //if (cha.m_Chara_pos.x > dun.m_Camera_pos.x + 2 
   //    || cha.m_Chara_pos.x < dun.m_Camera_pos.x - 2 
   //    || cha.m_Chara_pos.y>dun.m_Camera_pos.y + 2 
   //    || cha.m_Chara_pos.y < dun.m_Camera_pos.y - 2)
   //{
   //    dun.m_bCamera_move_flag = true;
   //    cha.m_bChara_move_flag = 3;  //3은 좌우 이동 없음
   //}
    
   // Make();
}
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
void    Sample::Make()
{
    //void Dungeon::Make_dungeon()
    {


        ZeroMemory(rending_arr, sizeof(rending_arr));
        for (int i = 0; i < dun.Dunmgr.m_Obj_list.size(); i++)
        {
            dun.Dunmgr.m_Obj_list[i]->Release();
        }
        dun.Dunmgr.m_Obj_list.clear();

        dun.Map_check(Charactor_list[0]->m_Chara_pos.x, Charactor_list[0]->m_Chara_pos.y);

        POINT start_pos = { Charactor_list[0]->m_Chara_pos.x - (rending_arr_size.x / 2), Charactor_list[0]->m_Chara_pos.y - (rending_arr_size.y / 2) };

        for (int i = 0; i < 16; i++)
        {
            for (int k = 0; k < 18; k++)
            {
                if (start_pos.x + k > 49 || start_pos.x + k < 0 || start_pos.y + i > 39 || start_pos.y + i < 0)
                    continue;
                else if (rending_arr[start_pos.y + i][start_pos.x + k] == true)
                {
                    dun.Load(start_pos.x, start_pos.y, i, k);
                   ////Dungeon_world[start_pos.y+i][start_pos.x+k]
                   //if (Dungeon_world[start_pos.y + i][start_pos.x + k] != WALL1 &&
                   //    Dungeon_world[start_pos.y + i][start_pos.x + k] != WALL2 &&
                   //    Dungeon_world[start_pos.y + i][start_pos.x + k] != WALL3 &&
                   //    Dungeon_world[start_pos.y + i][start_pos.x + k] != IRONWALL1 &&
                   //    Dungeon_world[start_pos.y + i][start_pos.x + k] != IRONWALL2)
                   //{
                   //    CABitmapObject* floors = dun.Dunmgr.Load_Object(L"floors.bmp");
                   //    floors->Setobject(L"tile", 1, (k * 48), (i * 48), { 0,0,24,24 }, false, false);
                   //    floors->m_iRt_num = FLOOR;
                   //    floors->Scale(2, 2);
                   //    //wall->m_bDraw_flag = false;
                   //    if (Dungeon_world[start_pos.y + i][start_pos.x + k] == 6 ||
                   //        Dungeon_world[start_pos.y + i][start_pos.x + k] == 7)
                   //    {
                   //        CABitmapObject* floors = dun.Dunmgr.Load_Object(L"walls.bmp");
                   //        floors->Setobject(L"door", 8, (k * 48), (i * 48) -30, dun.rt_list, false, false);
                   //        floors->m_iRt_num = Dungeon_world[start_pos.y + i][start_pos.x + k];
                   //        floors->Scale(2, 2);
                   //    }
                   //}
                   //else
                   //{
                   //    CABitmapObject* wall = dun.Dunmgr.Load_Object(L"walls.bmp");
                   //    wall->Setobject(L"wall", 8, (k * 48), (i * 48) - 30, dun.rt_list, false, false);
                   //    wall->m_iRt_num = Dungeon_world[start_pos.y + i][start_pos.x + k];
                   //    wall->Scale(2, 2);
                   //}
                }
                cha.Load(start_pos.x, start_pos.y, i, k);
                //if (cha.World_Charactor_pos[start_pos.y + i][start_pos.x + k]>0)
                //{
                //    int chara_index = cha.World_Charactor_pos[start_pos.y + i][start_pos.x + k];
                //    if (cha.World_Charactor_pos[start_pos.y + i][start_pos.x + k] == 1)
                //    {
                //        cha.Chara_bit_mgr.m_Obj_list[0]->m_pos = { k * 48.f,i * 48.f - 30 };
                //        cha.Chara_bit_mgr.m_Obj_list[1]->m_pos = { k * 48.f,i * 48.f - 30 };
                //    }
                //    else
                //    {
                //        cha.Chara_bit_mgr.m_Obj_list[chara_index]->m_pos = { k * 48.f,i * 48.f - 30 };// m_pos 에서 케릭터의 m_chara_pos 로 바꾸자
                //    }
                //}


            }
        }
    }
    cha.Move_done = false;
    //cha.Move_flag = false;
}

Sample::Sample()
{
}


Sample::~Sample()
{
}

WINRUN_DEFAULT;
