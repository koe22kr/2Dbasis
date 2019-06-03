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
            Bitmgr.m_Obj_list.erase(Bitmgr.m_Obj_list.begin()); //�浹�� �ΰ� ����
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
        //    I_BITMAPMGR.m_Obj_list[1].      make new object �� �ؾ��ҵ�. ��Ʈ �����ϰ� ����� �ݺ��ϸ鼭.
        CABitmapObject* newbit1 = Bitmgr.New_Object(BIT_file_name);
        newbit1->Setobject(L"L_BIT", 1, 100, 500, { 199,9,8,32 }, false, 0, 0, 100, 1, 0);
        CABitmapObject* newbit2 = Bitmgr.New_Object(BIT_file_name);
        newbit2->Setobject(L"R_BIT", 1, 700, 500, { 199,9,8,32 }, false, 0, 0, -100, 1, 0);

        m_fCur_time -= m_fBit_making_term;
    }
}
bool Bit::BitCheck()
{


    return false;//false �� ������-1


    return true; //false �� ������-1
}

Bit::Bit()
{
}


Bit::~Bit()
{
}
