#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "CABitmapObject.h"



class CABitmapMgr : public CABitmapObject, public CASingleton<CABitmapMgr>
{
    friend CASingleton<CABitmapMgr>;
public:
    vector <CABitmapObject*> m_Obj_list; //0번 =bk, 1번은 player 로 고정 되어 있다. //플레이어 변경시 frame의 player계산, object의 player_render 변경or 삭제 해야함
    map<T_STR, CABitmap*> m_Bitmap_Map;
    using ITOR = map<T_STR, CABitmap*>::iterator;

    T_STR mask_key = L"Mask_";
    T_STR File_path = L"../../data/bitmap/";

    int m_Player_Num = 1;//플레이어 번호
public:
    bool        Draw();
    bool Collision(CABitmapObject* obj, CAPOINT pos);
    bool Collision(CABitmapObject* obj1, CABitmapObject* obj2);

    bool        Load_Bitmap_Script(T_STR name);                     //bitmap 스크립트 인자 추가되면 수정 요망
    CABitmapObject*   Load_Object(T_STR filename);
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
