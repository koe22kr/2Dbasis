#include "Bit.h"

bool Bit::Init() 
{
    
  
    Bitmgr.Load_Bitmap(BIT_file_name);
    
    
    return true;
}
bool Bit::Frame()
{
    BitMake();



    if (m_bBit_maked_flag)
    {

        for (auto data : Bitmgr.m_Obj_list)
        {
            data->Move(1, 0);
        }
        if (Bitmgr.m_Obj_list.size()>1)

            if (Bitmgr.m_Obj_list[0]->m_pos.x > 420)
            {
                Turn_flag = !Turn_flag;//�̽� ��Ȳ
                ;
                Bitmgr.m_Obj_list.erase(Bitmgr.m_Obj_list.begin());
                Bitmgr.m_Obj_list.erase(Bitmgr.m_Obj_list.begin());
               // Bitmgr.m_Obj_list[0]->m_bDead_flag = true; //�浹�� �ΰ� ����
               // Bitmgr.m_Obj_list[1]->m_bDead_flag = true;
                Move_flag = true;
            }
            else if (Bitmgr.m_Obj_list[0]->m_pos.x > 350&& KeyCheck())
            {
               
                Turn_flag = !Turn_flag;
                Move_flag = true;
                Bitmgr.m_Obj_list.erase(Bitmgr.m_Obj_list.begin());
                Bitmgr.m_Obj_list.erase(Bitmgr.m_Obj_list.begin());
            }

    }
    Bitmgr.Frame();
    
    
    return true;
}
bool Bit::KeyCheck()
{


    DWORD dwState = I_Input.KeyCheck('W');
    if (dwState == KEY_PUSH)
    {
        Charactor_list[0]->m_Move_pos = { 0,-1 };
           
            return true;
    }
    dwState = I_Input.KeyCheck('S');
    if (dwState == KEY_PUSH)
    {
        Charactor_list[0]->m_Move_pos = { 0,1 };
            return true;
    }
    dwState = I_Input.KeyCheck('A');
    if (dwState == KEY_PUSH)
    {
        Charactor_list[0]->m_Move_pos = { -1,0 };
            return true;
    }
    dwState = I_Input.KeyCheck('D');
    if (dwState == KEY_PUSH)
    {
        Charactor_list[0]->m_Move_pos = { 1,0 };
            return true;
    }
    return false;
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
        CABitmapObject* newbit1 = Bitmgr.Load_Object(BIT_file_name);
        newbit1->Setobject(L"L_BIT", 1, 100, 550, { 199,9,8,32 }, true,false, 0, 0, m_fBit_Speed, 255, 0);
        CABitmapObject* newbit2 = Bitmgr.Load_Object(BIT_file_name);
        newbit2->Setobject(L"R_BIT", 1, 700, 550, { 199,9,8,32 }, true,false, 0, 0, -m_fBit_Speed, 255, 0);
        m_bBit_maked_flag = true;
        m_fCur_time -= m_fBit_making_term;
        newbit1->Scale(1.5,1.5);
        newbit2->Scale(1.5,1.5);
        
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
