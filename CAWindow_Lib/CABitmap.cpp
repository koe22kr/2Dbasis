#include "CABitmap.h"

bool	CABitmap::Init()
{
    return true;
}
bool	CABitmap::Frame()
{
    return true;
}
bool	CABitmap::Render()
{
    return true;
}
bool	CABitmap::Release()
{
  
    //DeleteObject(m_bmp);
    return true;
}

bool    CABitmap::Load(T_STR filename)
{
    
    // API 파일입출력
    HANDLE hFile = CreateFile(filename.c_str(),
        GENERIC_READ, 0,
        NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    BITMAPFILEHEADER m_bitFileHeader;
    DWORD dwRead;
    ReadFile(hFile, &m_bitFileHeader,
        sizeof(BITMAPFILEHEADER), &dwRead, NULL);

    DWORD dwDataSize;
    dwDataSize = m_bitFileHeader.bfOffBits -
        sizeof(BITMAPFILEHEADER);
    BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(dwDataSize);
    ReadFile(hFile, bitInfo,
        dwDataSize, &dwRead, NULL);

    PVOID pRaster = nullptr;
    m_bmp = CreateDIBSection(
        g_hScreenDC, bitInfo, DIB_RGB_COLORS, &pRaster, NULL, 0);
    ReadFile(hFile, pRaster,
        m_bitFileHeader.bfSize - m_bitFileHeader.bfOffBits,
        &dwRead, NULL);
    free(bitInfo);
    CloseHandle(hFile);

    // BITMAPFILEHEADER             내부 순서|
    // BITMAPINFO                            |
    //    BITMAPFILEHEADER                   |
    //    RGB...                             |
    // PIXELDATA 

        //m_bmp = (HBITMAP)LoadImage(
        //    g_hInstance,
        //    filename.c_str(),
        //    IMAGE_BITMAP,
        //    0, 0,
        //    LR_DEFAULTSIZE | LR_LOADFROMFILE);
        //if (m_bmp == NULL)return false;

    m_dc = CreateCompatibleDC(g_hScreenDC);
    SelectObject(m_dc, m_bmp);

    GetObject(m_bmp, sizeof(BITMAP), &m_BitmapInfo);
    return true;
}

bool    CABitmap::Draw(float inx, float iny, RECT rt, DWORD imode, bool draw_center)
{
    if (draw_center)
    {
        BitBlt(g_hOffScreenDC, inx - (rt.right / 2), iny - (rt.bottom / 2),
            rt.right,
            rt.bottom,
            m_dc,
            rt.left,
            rt.top, imode);
        return true;
    }
    else
    {
        BitBlt(g_hOffScreenDC, inx, iny,
            rt.right,
            rt.bottom,
            m_dc,
            rt.left,
            rt.top, imode);
        return true;
    }
}
bool    CABitmap::Draw(float inx, float iny, RECT rt, BLENDFUNCTION bf, bool draw_center)
{
    if (draw_center)
    {
        // DC -> DC
        AlphaBlend(g_hOffScreenDC, inx - (rt.right / 2), iny - (rt.bottom / 2), rt.right, rt.bottom,
            m_dc,
            rt.left, rt.top, rt.right, rt.bottom,
            bf);
        return true;
    }
    else
    {
        AlphaBlend(g_hOffScreenDC, inx, iny, rt.right, rt.bottom,
            m_dc,
            rt.left, rt.top, rt.right, rt.bottom,
            bf);
        return true;
    }
}
bool    CABitmap::Draw(float inx, float iny, RECT Srcrt, RECT Deskrt, BLENDFUNCTION bf, bool draw_center)
{
    if (draw_center)
    {// DC -> DC
        AlphaBlend(g_hOffScreenDC, inx - (Deskrt.right / 2), iny - (Deskrt.bottom / 2), Deskrt.right, Deskrt.bottom,
            m_dc,
            Srcrt.left, Srcrt.top, Srcrt.right, Srcrt.bottom,
            bf);
        return true;
    }
    else
    {
        AlphaBlend(g_hOffScreenDC, inx , iny , Deskrt.right, Deskrt.bottom,
            m_dc,
            Srcrt.left, Srcrt.top, Srcrt.right, Srcrt.bottom,
            bf);
        return true;
    }
}



CABitmap::CABitmap()
{
}


CABitmap::~CABitmap()
{
}
