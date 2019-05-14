#include "Sample.h"

//Bitmap-> Bitmap //blit  비트맵은 비트맵에만 뿌릴수있.
//DC->DC 디바이스 컨넥에서.. DC 로만; HDC를 bitmap당 하나씩 만들어야함. memdc도 하나..//device context
#define first

#ifdef first

bool Sample::Init()
{
    m_player.Init();
    m_player.Load(L"bitmap1.bmp");
    m_player.pos = CAPOINT(100, 100);
    m_player.rt = { 90,1,40,60 };
    m_player.fSpeed = 100.0f;

    m_bk.Init();
    m_bk.Load(L"wall.bmp");
    m_bk.pos = CAPOINT(0, 0);
    m_bk.rt = { 0,0,800,600 };
    m_bk.fSpeed = 0.0f;

    return true;
}

bool Sample::Render()
{
    
    m_bk.Render();
    m_player.Render();
    return true;
}

bool Sample::Frame()
{

     DWORD dwState = I_Input.KeyCheck('W');
     if (dwState == KEY_HOLD)
     {
        m_player.pos.y -= 100 * g_fSeoundPerFrame;
     }  dwState = I_Input.KeyCheck('S');
     if (dwState == KEY_HOLD)
     {
         m_player.pos.y += 100 * g_fSeoundPerFrame;
    
     }
     dwState = I_Input.KeyCheck('A');
     if (dwState == KEY_HOLD)
     {
         m_player.pos.x -= 100 * g_fSeoundPerFrame;
    
     }
     dwState = I_Input.KeyCheck('D');
     if (dwState == KEY_HOLD)
     {
         m_player.pos.x += 100 * g_fSeoundPerFrame;
    
     }
    return true;
}


bool Sample::Release()
{
    m_player.Release();
    return true;
}

Sample::Sample()
{
  

}


Sample::~Sample()
{
}

WINRUN_DEFAULT;



#elif second


bool Sample::Init()
{
    m_hScreenDC = GetDC(m_hWnd); //한번만 하면 될거같.
    g_hScreenDC = m_hScreenDC;
    g_hOffScreenDC = CreateCompatibleDC(g_hScreenDC);
    m_hOffScreenBitmap = CreateCompatibleBitmap(
        g_hScreenDC, m_rtClient.right,
        m_rtClient.bottom);
    SelectObject(g_hOffScreenDC, m_hOffScreenBitmap);

    bk_Color = RGB(255, 255, 100);
    bk_hbr = CreateSolidBrush(bk_Color);
    SelectObject(g_hOffScreenDC, bk_hbr);    //여기까지 다 한번만 하면 됨.
    return true;
}


//Release();

//DeleteObject(m_hbrBack);
//ReleaseDC(m_hWnd, m_hScreenDC);

bool Sample::Release()
{

    return true;

}


bool Sample::Frame()
{



    DWORD dwState = I_Input.KeyCheck('W');
    if (dwState == KEY_HOLD)
    {
        BMPMgr.m_dwY -= 100 * g_fSeoundPerFrame;
    }  dwState = I_Input.KeyCheck('S');
    if (dwState == KEY_PUSH)
    {
        BMPMgr.m_dwY += 100 * g_fSeoundPerFrame;

    }
    dwState = I_Input.KeyCheck('A');
    if (dwState == KEY_PUSH)
    {
        BMPMgr.m_dwX -= 100 * g_fSeoundPerFrame;

    }
    dwState = I_Input.KeyCheck('D');
    if (dwState == KEY_PUSH)
    {
        BMPMgr.m_dwX += 100 * g_fSeoundPerFrame;

    }
    return true;
}
//
//BitBlt(g_hOffScreenDC, x, y,
//    rt.right,
//    rt.bottom,
//    m_hMemDC,
//    rt.left,
//    rt.top, SRCCOPY);
//
//
//PatBlt(m_hOffScreenDC,
//    0, 0, m_rtClient.right,
//    m_rtClient.bottom, PATCOPY);

bool Sample::Render()
{
    PatBlt(g_hOffScreenDC,
        0, 0, m_rtClient.right,
        m_rtClient.bottom, PATCOPY);

    BMPMgr.draw(BMPMgr.m_dwX, BMPMgr.m_dwY, BMPMgr.chara.rt);

    BitBlt(g_hScreenDC, 0, 0,
        m_rtClient.right,
        m_rtClient.bottom,
        g_hOffScreenDC,
        0,
        0, SRCCOPY);

    // DC -> DC
   /* PatBlt(m_hOffScreenDC,
        0, 0, m_rtClient.right,
        m_rtClient.bottom, PATCOPY);
    BitBlt(m_hScreenDC, 0, 0,
        m_rtClient.right,
        m_rtClient.bottom,
        m_hOffScreenDC,
        0,
        0, SRCCOPY);*/

    return true;
}

Sample::Sample()
{



}


Sample::~Sample()
{
}

WINRUN_DEFAULT;

#endif