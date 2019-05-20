
#include "CAStd.h"
#include "Sample.h"

//Bitmap-> Bitmap //blit  비트맵은 비트맵에만 뿌릴수있.
//DC->DC 디바이스 컨넥에서.. DC 로만; HDC를 bitmap당 하나씩 만들어야함. memdc도 하나..//device context



bool Sample::Init()
{
    
    mgr.Load_Object(L"wall.bmp");
    mgr.Load_Object(L"bitmap1.bmp");
    mgr.Load_Bitmap_Script(L"../../data/bitmap_object.txt");
    mgr.m_Obj_list[0]->Setobject(L"Backwall", 1, 0, 0, 0, 0, { 0,0,800,600 }, 0);
    mgr.m_Obj_list[1]->Setobject(L"Player", 1, 100, 100, 0, 0, { 90,1,40,60 }, 0);
    
    
    //mgr.m_pPlayer = mgr.Load_File_with_mask(L"bitmap1.bmp");
    //mgr.m_pPlayer->m_pos = CAPOINT(100, 100);
    //mgr.m_pPlayer->m_rt[0] = { 90,1,40,60 };
    //mgr.m_pPlayer->m_fSpeed = 100.0f;
    //
    //m_player.Init();
    //m_player.Load(L"bitmap1.bmp");
    //m_player.m_pos = CAPOINT(100, 100);
    //m_player.m_rt = { 90,1,40,60 };
    //m_player.m_fSpeed = 100.0f;
    //
    //
    //
    //m_bk.Init();
    //m_bk.Load(L"wall.bmp");
    //m_bk.m_pos = CAPOINT(0, 0);
    //m_bk.m_rt = { 0,0,800,600 };
    //m_bk.m_fSpeed = 0.0f;
    mgr.Init();
    return true;
}

bool Sample::Render()
{
    mgr.Render();
    //m_bk.Render();
    //m_player.Render();
    return true;
}

bool Sample::Frame()
{
    mgr.Frame();
    // DWORD dwState = I_Input.KeyCheck('W');
    // if (dwState == KEY_HOLD)
    // {
    //    mgr.Move(0,-100 * g_fSecondPerFrame);
    // }  dwState = I_Input.KeyCheck('S');
    // if (dwState == KEY_HOLD)
    // {
    //     mgr.Move( 0, 100 * g_fSecondPerFrame);
    //     
    //
    // }
    // dwState = I_Input.KeyCheck('A');
    // if (dwState == KEY_HOLD)
    // {
    //     mgr.Move( -100 * g_fSecondPerFrame, 0);
    //
    // }
    // dwState = I_Input.KeyCheck('D');
    // if (dwState == KEY_HOLD)
    // {
    //     mgr.Move( 100 * g_fSecondPerFrame, 0);
    //
    // }
    return true;

}


bool Sample::Release()
{
    mgr.Release();
    // m_player.Release();
    return true;
}

Sample::Sample()
{


}


Sample::~Sample()
{
}

WINRUN_DEFAULT;




