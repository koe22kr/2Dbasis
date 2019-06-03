#include "Bit.h"

bool Bit::Init() 
{
    Bitmgr.Load_Bitmap(BIT_file_name);
    Bitmgr.Init();
    return true;
}
bool Bit::Frame()
{

    Bitmgr.Frame();
    if (!Bitmgr.m_Obj_list.empty())
    {
        for (CABitmapObject* data : Bitmgr.m_Obj_list)
        {
            data->Move(1, 0);
        }
        if (Bitmgr.Collision(Bitmgr.m_Obj_list[0], Bitmgr.m_Obj_list[0]))
        {
            Bitmgr.m_Obj_list.erase(Bitmgr.m_Obj_list.begin()); //충돌시 두개 삭재
            Bitmgr.m_Obj_list.erase(Bitmgr.m_Obj_list.begin());
        }
    }
    BitMake();
    return true;
}

bool Bit::Render()
{
    Bitmgr.Render();
    return true;
}
bool Bit::Release()
{
    Bitmgr.Release();
    return true;
}

void Bit::BitMake()
{
    
        m_fCur_time += g_fSecondPerFrame;
    if (m_fBit_making_term <m_fCur_time)
    {
        //    I_BITMAPMGR.m_Obj_list[1].      make new object 를 해야할듯. 비트 생성하고 지우고 반복하면서.
        CABitmapObject* newbit1 = Bitmgr.New_Object(BIT_file_name);
        newbit1->Setobject(L"L_BIT", 1, 100, 500, { 199,9,8,32 }, false, 0, 0, 100, 1, 0);
        CABitmapObject* newbit2 = Bitmgr.New_Object(BIT_file_name);
        newbit2->Setobject(L"R_BIT", 1, 700, 500, { 199,9,8,32 }, false, 0, 0, -100, 1, 0);

        m_fCur_time -= m_fBit_making_term;
    }
}
bool Bit::BitCheck()
{


    return false;//false 시 라이프-1


    return true; //false 시 라이프-1
}

Bit::Bit()
{
}


Bit::~Bit()
{
}
