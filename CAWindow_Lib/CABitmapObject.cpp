#include "CABitmapObject.h"


void CABitmapObject::Rotation()
{


    int inewsize = sqrt((m_Src_rt[m_iRt_num ]->right * m_Src_rt[m_iRt_num ]->right)
        + (m_Src_rt[m_iRt_num ]->bottom * m_Src_rt[m_iRt_num ]->bottom));

    HBITMAP bitmap = CreateCompatibleBitmap(g_hScreenDC, inewsize, inewsize);
    if (bitmap == NULL)
        return;


    HDC rotationDC = CreateCompatibleDC(NULL);
    SelectObject(rotationDC, bitmap);
    HBRUSH hbrBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(rotationDC, hbrBrush);
    PatBlt(rotationDC, 0, 0, inewsize, inewsize, PATCOPY);
    DeleteObject(hbrBrush);



    //Angle 180 - > π  변환 cos,sin은 파이값으로 줘야함
    float fradian = m_fAngle * 3.141592f / 180.0f;
    float fCosine = cos(fradian);
    float fSine = sin(fradian);
    XFORM xform;
    xform.eM11 = fCosine; xform.eM12 = fSine;
    xform.eM21 = -fSine; xform.eM22 = fCosine;
    xform.eDx = inewsize / 2;
    xform.eDy = inewsize / 2;

    int iOldGraphic = SetGraphicsMode(rotationDC, GM_ADVANCED);
    SetWorldTransform(rotationDC, &xform);

    BitBlt(rotationDC, -m_Src_rt[m_iRt_num ]->right / 2, -m_Src_rt[m_iRt_num ]->bottom / 2, m_Src_rt[m_iRt_num ]->right, m_Src_rt[m_iRt_num]->bottom,
        m_pbmp->m_dc, m_Src_rt[m_iRt_num ]->left, m_Src_rt[m_iRt_num]->top, SRCCOPY);

    xform.eM11 = 1; xform.eM12 = 0;
    xform.eM21 = 0; xform.eM22 = 1;
    xform.eDx = 0;  xform.eDy = 0;

    SetWorldTransform(rotationDC, &xform);
    SetGraphicsMode(rotationDC, iOldGraphic);


    CAPOINT pos;
    pos.x = m_pos.x - (inewsize / 2);
    pos.y = m_pos.y - (inewsize / 2);




    BITMAP ibmp;
    GetObject(bitmap, sizeof(BITMAP), &ibmp);
    if (ibmp.bmBitsPixel == 32)
    {
        BLENDFUNCTION bf;
        bf.BlendOp = AC_SRC_OVER;
        bf.BlendFlags = 0;
        bf.SourceConstantAlpha = m_fAlpha;
        bf.AlphaFormat = AC_SRC_ALPHA;
        AlphaBlend(g_hOffScreenDC, pos.x, pos.y, inewsize, inewsize,
            rotationDC,
            0, 0, inewsize, inewsize,
            bf);
    }
    else
    {
        BitBlt(g_hOffScreenDC, pos.x, pos.y,
            inewsize, inewsize, rotationDC, 0, 0, SRCCOPY);
    }
    DeleteObject(bitmap);
    DeleteDC(rotationDC);

}



void CABitmapObject::Rt_Operate()
{
    if (m_fSprite_time != 0)
    {

        m_fCur_time += g_fSecondPerFrame;    //현시간 += 프레임당
        m_fDelta_time += g_fSecondPerFrame;   //
        if (m_fDelta_time > m_fSprite_time / m_iMax_rt_num)
        {
            m_fDelta_time -= m_fSprite_time / m_iMax_rt_num;
            m_iRt_num += 1;

        }
        //rt값 초과방지
        if (m_iRt_num == m_iMax_rt_num)  //루프하고 프레임넘버 >사이즈 = 프레임초기화
        {
            if (m_bLoop_flag == true)
                m_iRt_num -= m_iMax_rt_num;
            else
            {
                m_iRt_num = min(m_iRt_num, m_iMax_rt_num-1);
            }
        }
    }

    //del     as
    if (m_fLife_time != 0 && m_fLife_time < m_fCur_time)
    {
        m_bDead_flag = true;
    }
}

void        CABitmapObject::Player_Render()
{
    if (m_bPlayer_flag == true)
    {

        if (m_fplayer_action_flag < -0.2)
        {
            if (m_fplayer_action_flag < -0.7)
                m_iRt_num = LL;
            else
            {
                m_iRt_num = L;
            }
        }
        else if (m_fplayer_action_flag > 0.2)
        {
            if (m_fplayer_action_flag > 0.7)
                m_iRt_num = RR;
            else
            {
                m_iRt_num = R;
            }
        }
        else

        {
            m_iRt_num = Mid;

        }
    }
}
bool CABitmapObject::Init()
{
    return true;
}
bool CABitmapObject::Render()
{
    
    if (m_iMax_rt_num > 0)
    {
        
        Draw(m_iRt_num);
    }
    return true;
}
bool CABitmapObject::Draw(int rt_num)// 1start;
{
    
    if (m_fAngle != 0)
    {
        Rotation();
    }
    else if (m_pbmp->m_BitmapInfo.bmBitsPixel == 32)
    {
        BLENDFUNCTION bf;
        bf.BlendOp = AC_SRC_OVER;
        bf.BlendFlags = 0;
        bf.SourceConstantAlpha = m_fAlpha;
        bf.AlphaFormat = AC_SRC_ALPHA;
        
        m_pbmp->Draw(m_pos.x, m_pos.y,*m_Src_rt[rt_num ], *m_Desk_rt[rt_num ], bf, m_bCenter_draw_flag);
    }
    //else if (m_fAlpha != 1)
    // {
    //     AlphaBlendRender(*m_Src_rt[rt_num - 1]);
    // }
    else if (m_pmask != nullptr)
    {
        m_pmask->Draw(m_pos.x, m_pos.y, *m_Src_rt[rt_num ], SRCAND, m_bCenter_draw_flag);       //NEED
        m_pbmp->Draw(m_pos.x, m_pos.y, *m_Src_rt[rt_num ], SRCINVERT, m_bCenter_draw_flag);
        m_pmask->Draw(m_pos.x, m_pos.y, *m_Src_rt[rt_num ], SRCINVERT, m_bCenter_draw_flag);
    }
    else
    {
        m_pbmp->Draw(m_pos.x, m_pos.y, *m_Src_rt[rt_num ], SRCCOPY, m_bCenter_draw_flag);
    }
    return true;
}
bool CABitmapObject::Frame()
{
    if (m_bPlayer_flag == true)
    {
        Player_Render();// 비행기 경우만 사용.
    }
    return true;
}
bool CABitmapObject::Release()
{
    //for (int i = 0; i < m_Src_rt.size(); i++)
    //{
    //    //delete m_Src_rt[i]();
    //    //delete m_Desk_rt[i]();
    //}
    m_Src_rt.clear();
    m_Desk_rt.clear();

    return true;
}


void CABitmapObject::Move(float xstep, float ystep)//기울기
{
    if (m_fSpeed != 0)
    {
        m_pos.x += xstep * m_fSpeed * g_fSecondPerFrame;
        m_pos.y += ystep * m_fSpeed * g_fSecondPerFrame;

      // if (m_pos.x + m_Src_rt[m_iRt_num]->right > g_rtClient.right)
      // {
      //     m_pos.x = g_rtClient.right - m_Src_rt[m_iRt_num]->right;
      // }
      // if (m_pos.y + m_Src_rt[m_iRt_num]->bottom > g_rtClient.bottom)
      // {
      //     m_pos.y = g_rtClient.bottom - m_Src_rt[m_iRt_num]->bottom;
      // }
      // m_pos.x < 0 ? m_pos.x = 0 : m_pos.x;
      // m_pos.y < 0 ? m_pos.y = 0 : m_pos.y;

    }

}

//bool CAObject::AlphaBlendRender(RECT rt)
//{
//    BITMAPINFO bmi;
//    ZeroMemory(&bmi, sizeof(BITMAPINFO));
//    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
//    bmi.bmiHeader.biWidth = rt.right ;
//    bmi.bmiHeader.biHeight = rt.bottom;
//    bmi.bmiHeader.biPlanes = 1;
//    bmi.bmiHeader.biBitCount = 32;
//    bmi.bmiHeader.biCompression = BI_RGB;
//    bmi.bmiHeader.biSizeImage = (rt.right)*(rt.bottom) * 4;
//    
//    
//    void* pvBits = 0;//비트맵 시작주소  {아래서 반환됨}
//    HBITMAP hBitmap = CreateDIBSection(g_hScreenDC, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0);
//    HDC bmpdc = CreateCompatibleDC(NULL);
//    SelectObject(bmpdc, hBitmap);
//    BitBlt(bmpdc, 0,0, rt.right, rt.bottom, m_pbmp->m_dc, rt.left, rt.top, SRCCOPY);
//    DeleteDC(bmpdc);
//
//    void* pvMaskBits = 0;
//    HBITMAP hMaskBitmap = CreateDIBSection(g_hScreenDC, &bmi, DIB_RGB_COLORS, &pvMaskBits, NULL, 0);
//    HDC maskdc = CreateCompatibleDC(NULL);
//    SelectObject(maskdc, hMaskBitmap);
//    BitBlt(maskdc, 0,0, rt.right, rt.bottom, m_pmask->m_dc, rt.left, rt.top, SRCCOPY);
//    DeleteDC(maskdc);
//
//    void* pvOffBits = 0;
//    HBITMAP hoffscreen = CreateDIBSection(g_hScreenDC, &bmi, DIB_RGB_COLORS, &pvOffBits, NULL, 0);
//    HDC offdc = CreateCompatibleDC(NULL);
//    SelectObject(offdc, hoffscreen);
//    BitBlt(offdc,0,0, rt.right, rt.bottom, g_hOffScreenDC, m_pos.x, m_pos.y, SRCCOPY); /// 예제에서는 마지막2개의 x y 값이 pos x,y 값 들어가 있는데 이유 모르겠슴
//    DeleteDC(offdc);
//    for (int y = 0; y < rt.bottom - rt.top; y++)
//    {
//        
//        byte* pRGB = (byte*)&((DWORD*)pvBits)[y*(rt.right )];
//        byte* pMaskRGB = (byte*)&((DWORD*)pvMaskBits)[y*(rt.right )];
//        byte* pOffRGB = (byte*)&((DWORD*)pvOffBits)[y*(rt.right )];
//        for (int x = 0; x < rt.right ; x++)
//        {
//            // 한 픽쉘의 RGBA 값 0xaarrggbb    바이트 단위 배열로 읽어서? 거꾸로.
//            byte  A = pRGB[3]; //Alpha 값
//            byte  R = pRGB[2];
//            byte  G = pRGB[1];
//            byte  B = pRGB[0];
//            if (pMaskRGB[0] == 255 && pMaskRGB[1] == 255 && pMaskRGB[2] == 255)
//            {
//                pRGB[3] = pOffRGB[3];
//                pRGB[2] = pOffRGB[2];
//                pRGB[1] = pOffRGB[1];
//                pRGB[0] = pOffRGB[0];
//
//            }
//            else
//            {
//                pRGB[3] = 0xff;// m_fAlpha; 
//                pRGB[2] = pOffRGB[2] * (1.0f - (m_fAlpha/255)) + R * (m_fAlpha/255);// 0~1
//                pRGB[1] = pOffRGB[1] * (1.0f - (m_fAlpha/255)) + G * (m_fAlpha/255);
//                pRGB[0] = pOffRGB[0] * (1.0f - (m_fAlpha/255)) + B * (m_fAlpha/255);
//            }
//            pRGB += 4;
//            pMaskRGB += 4;
//            pOffRGB += 4;
//        }
//    }
//
//    bmpdc = CreateCompatibleDC(NULL);
//    SelectObject(bmpdc, hBitmap);
//
//    SetStretchBltMode(g_hOffScreenDC, HALFTONE);
//    StretchBlt(g_hOffScreenDC, m_pos.x, m_pos.y, rt.right, rt.bottom, bmpdc, 0, 0, rt.right, rt.bottom, SRCCOPY);// NEED
//
//    DeleteObject(hBitmap);
//    DeleteObject(hMaskBitmap);
//    DeleteObject(hoffscreen);
//    DeleteDC(bmpdc);
//
//    return true;
//}


bool CABitmapObject::Draw_ColorKey(RECT rt, COLORREF color)
{
    //DC->DC
    TransparentBlt(g_hOffScreenDC, rt.left, rt.top, rt.right, rt.bottom,
        m_pbmp->m_dc, rt.left, rt.top, rt.right, rt.bottom,
        color);
    return true;
}


void CABitmapObject::Setobject(T_STR name, int max_rt_num, float inx, float iny, RECT rt, bool center_draw,
    bool loop_flag, float sprite_time, float life_time, float fSpeed, float alpha, int player_flag)
{
    m_Obj_Name = name;
    m_iMax_rt_num = max_rt_num;
    m_pos = { inx,iny };
    m_bCenter_draw_flag = center_draw;
    m_bLoop_flag = loop_flag;
    m_fSprite_time = sprite_time;
    m_fLife_time = life_time;
    m_fSpeed = fSpeed;
    m_fAlpha = alpha;
    m_bPlayer_flag = player_flag;
    shared_ptr<RECT> NewRect = make_shared<RECT>();
    shared_ptr<RECT> NewRect2 = make_shared<RECT>();
    //RECT* NewRect = new RECT;
    //RECT* NewRect2 = new RECT;
    NewRect->left = rt.left;
    NewRect->top = rt.top;
    NewRect->right = rt.right;
    NewRect->bottom = rt.bottom;
    *NewRect2 = *NewRect;
   
    m_Src_rt.push_back(NewRect);
    m_Desk_rt.push_back(NewRect2);
}
void CABitmapObject::Setobject(T_STR name, int max_rt_num, float inx, float iny, vector<RECT> rt_array, bool center_draw,
    bool loop_flag, float sprite_time, float life_time, float fSpeed, float alpha, int player_flag)
{
    m_Obj_Name = name;
    m_iMax_rt_num = max_rt_num;
    m_pos = { inx,iny };
    m_bCenter_draw_flag = center_draw;
    m_bLoop_flag = loop_flag;
    m_fSprite_time = sprite_time;
    m_fLife_time = life_time;
    m_fSpeed = fSpeed;
    m_fAlpha = alpha;
    m_bPlayer_flag = player_flag;

    
    for (int i = 0; rt_array.begin() + i != rt_array.end(); i++)
    {
        shared_ptr<RECT> NewRect = make_shared<RECT>();
        shared_ptr<RECT> NewRect2 = make_shared<RECT>();
        //RECT* NewRect = new RECT;
        //RECT* NewRect2 = new RECT;
        NewRect->left = rt_array[i].left;
        NewRect->top = rt_array[i].top;
        NewRect->right = rt_array[i].right;
        NewRect->bottom = rt_array[i].bottom;
        *NewRect2 = *NewRect;
        //NewRect2->top = inx;
        //NewRect2->left = iny;
        m_Src_rt.push_back(NewRect);
        m_Desk_rt.push_back(NewRect2);
    }
    
}

void CABitmapObject::Scale(float xscale, float yscale)
{
    for (int i = 0; i < m_Src_rt.size(); i++)
    {
        m_Desk_rt[i]->right = xscale * m_Src_rt[i]->right;
        m_Desk_rt[i]->bottom = yscale * m_Src_rt[i]->bottom;
    }
}

void CABitmapObject::Scale(int rt_num, float xscale, float yscale)
{
    m_Desk_rt[rt_num]->right = xscale * m_Src_rt[rt_num]->right;
    m_Desk_rt[rt_num]->bottom = yscale * m_Src_rt[rt_num]->bottom;
}

CABitmapObject::CABitmapObject()
{

}


CABitmapObject::~CABitmapObject()
{
}
