#include "Sample.h"
#include "CAStd.h"

//Bitmap-> Bitmap //blit  비트맵은 비트맵에만 뿌릴수있.
//DC->DC 디바이스 컨넥에서.. DC 로만; HDC를 bitmap당 하나씩 만들어야함. memdc도 하나..//device context



bool Sample::Init()
{
    mgr.Load_Bitmap_Script(L"../../data/bitmap_object.txt");
    //CAObject* bk = mgr.Load_File_with_mask(L"wall.bmp");//로드시 필요값 읽어오게 하기. + 스크립트 /+스/프라이트 한번에 읽어오는거 만듦기
    //mgr.m_Obj_list[0]->m_pos = CAPOINT(0, 0);
    //mgr.m_Obj_list[0]->m_rt[0] = { 0,0,800,800 };
    //mgr.m_Obj_list[0]->m_fSpeed = 0;
    //
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




