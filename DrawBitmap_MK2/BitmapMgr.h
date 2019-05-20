#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "Object.h"



class CABitmapMgr : public CASingleton<CABitmapMgr>
{
    friend CASingleton<CABitmapMgr>;


public:
    CAObject* m_pPlayer;
    CAObject* m_pBk;
    vector <CAObject*> m_Obj_list;
    std::map<T_STR, CABitmap*> m_Bitmap_Map;
    using ITOR = map<T_STR, CABitmap*>::iterator;

    T_STR mask_key = L"Mask_";
    T_STR File_path = L"../../data/bitmap/";


    //void Move(float x, float y);
    //    void SetPos();
public:
    bool        Draw();
    
    // == �ε��� ������ ������Ʈ�� �ٷ��ϱ�.

    bool         Load_Bitmap_Script(T_STR name); 
    // ���� ��ũ��Ʈ ����, �� �ȿ� ���� ��ũ��Ʈ�� �б�.
    CAObject*   Load_Object(T_STR filename);
    
    CABitmap*   Load_Bitmap(T_STR filename);

    //void        Set_Obj(float inx, float iny, RECT rt, float fSpeed);
    bool        Delete_Dead_Obj();

    //bool        Delete(T_STR filename);

public:
    bool Init();
    bool Frame();
    bool Render();//// �̰� ������Ʈ �� �ٽ�.
    bool Release();
    CABitmapMgr();
    virtual ~CABitmapMgr();
    
};
#define I_BITMAPMGR CABitmapMgr::GetInstance()
