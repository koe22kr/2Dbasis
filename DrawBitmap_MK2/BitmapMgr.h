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
    
    int m_Player_Num = 1;//플레이어 번호
public:
    bool        Draw();
    bool Collision(CAObject* obj,CAPOINT pos);
    bool Collision(CAObject* obj1, CAObject* obj2);

    bool        Load_Bitmap_Script(T_STR name); 
    CAObject*   Load_Object(T_STR filename);
    CABitmap*   Load_Bitmap(T_STR filename);
    bool        Delete_Dead_Obj();
public:
    bool Init();
    bool Frame();
    bool Render();//// 이거 오브젝트 후 다시.
    bool Release();
    void Move(float xstep, float ystep, int obj_num);
    CABitmapMgr();
    virtual ~CABitmapMgr();
    
};
#define I_BITMAPMGR CABitmapMgr::GetInstance()
