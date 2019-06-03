#pragma once
#include "CAStd.h"
#include "CACore.h"
#include "CABitmapObject.h"



class CABitmapMgr : public CASingleton<CABitmapMgr>
{
    friend CASingleton<CABitmapMgr>;
public:
    vector <CABitmapObject*> m_Obj_list; //0�� =bk, 1���� player �� ���� �Ǿ� �ִ�. //�÷��̾� ����� frame�� player���, object�� player_render ����or ���� �ؾ���
    map<T_STR, CABitmap*> m_Bitmap_Map;
    using ITOR = map<T_STR, CABitmap*>::iterator;

    T_STR mask_key = L"Mask_";
    T_STR File_path = L"../../data/bitmap/";

    int m_Player_Num = 1;//�÷��̾� ��ȣ
public:
    bool                 Draw();
    bool                 Collision(CABitmapObject* obj, CAPOINT pos);
    bool                 Collision(CABitmapObject* obj1, CABitmapObject* obj2);
    CABitmapObject*      New_Object(T_STR filename);
    bool                 Load_Bitmap_Script(T_STR name);                     //bitmap ��ũ��Ʈ ���� �߰��Ǹ� ���� ���
    CABitmapObject*      Load_Object(T_STR filename);
    CABitmap*            Load_Bitmap(T_STR filename);
    bool                 Delete_Dead_Obj();
public:
    bool Init();
    bool Frame();
    bool Render();//// �̰� ������Ʈ �� �ٽ�.
    bool Release();
    void Move(int obj_num, float xstep = 1, float ystep = 1);
    CABitmapMgr();
    virtual ~CABitmapMgr();

};
#define I_BITMAPMGR CABitmapMgr::GetInstance()
