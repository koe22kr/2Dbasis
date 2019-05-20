#pragma once
//#include "CAStd.h"
//#include "CACore.h"
//#include "CAObject.h"



class CABitmapMgr : public CASingleton<CABitmapMgr>
{
    friend CASingleton<CABitmapMgr>;

    
public:
    CAObject* m_pPlayer;
    vector <CAObject*> m_Obj_list;
    std::map<T_STR, CABitmap*> m_Bitmap_Map;
    using ITOR = map<T_STR, CABitmap*>::iterator;

    T_STR mask_key = L"Mask_";
    T_STR File_path = L"../../data/bitmap/";

    
    void Move(float x,float y);
//    void SetPos();
public:
    void        Draw();
    void        Set_Obj(float inx, float iny, RECT rt, float fSpeed);// == 로딩시 내부의 오브젝트로 바로하기.

   bool         Load_Bitmap_Script(T_STR name); // 메인 스크립트 열고, 그 안에 적힌 스크립트들 읽기.
    CAObject*   Load_File(T_STR filename);
    CAObject*   Load_File_with_mask(T_STR filename);

    bool        Delete_Dead_Obj();
    //bool        Delete(T_STR filename);
    
public:
    bool Init();
    bool Frame();
    bool Render();//// 이거 오브젝트 후 다시.
    bool Release();
    CABitmapMgr();
    virtual ~CABitmapMgr();
};
#define I_BITMAPMGR CABitmapMgr::GetInstance()
