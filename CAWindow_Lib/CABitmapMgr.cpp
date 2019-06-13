#include "CABitmapMgr.h"

bool CABitmapMgr::Collision(CABitmapObject* obj, CAPOINT pos)
{
    if (obj->m_pos.x < pos.x && pos.x < obj->m_pos.x + obj->m_Desk_rt[obj->m_iRt_num]->right)
    {
        if (obj->m_pos.y < pos.y && pos.y < obj->m_pos.y + obj->m_Desk_rt[obj->m_iRt_num]->bottom)
        {
            return true;
        }
    }
    return false;
}
bool CABitmapMgr::Collision(CABitmapObject* main_obj, CABitmapObject* target_obj)
{
    POINT main;
    main.x = main_obj->m_Desk_rt[main_obj->m_iRt_num]->right / 2;
    main.y = main_obj->m_Desk_rt[main_obj->m_iRt_num]->bottom / 2;;

    POINT target;
    target.x = target_obj->m_Desk_rt[target_obj->m_iRt_num]->right / 2;
    target.y = target_obj->m_Desk_rt[target_obj->m_iRt_num]->bottom / 2;

    POINT distance;
    distance.x = abs((main_obj->m_pos.x + main.x) - (target_obj->m_pos.x + target.x));
    distance.y = abs((main_obj->m_pos.y + main.y) - (target_obj->m_pos.y + target.y));

    if (distance.x < (main.x + target.x) && distance.y < (main.y + target.y))
    {
        return true;
    }
    return false;
}

CABitmapMgr::CABitmapMgr()
{
}


CABitmapMgr::~CABitmapMgr()
{
}

void CABitmapMgr::Move(int obj_num, float xstep, float ystep)
{
    m_Obj_list[obj_num]->Move(xstep, ystep);
}

bool CABitmapMgr::Init()
{
    return true;
}
bool CABitmapMgr::Draw()
{
    m_Obj_list[0]->Draw();
    m_Obj_list[1]->Draw(m_Obj_list[1]->m_iRt_num);

    return true;
}
bool CABitmapMgr::Frame()
{
    /*for (int i = 0; i < m_Obj_list.size(); i++)
    {
        m_Obj_list[i]->Rt_Operate();
        if (m_Obj_list[i]->m_bDead_flag) 
        {
            m_Obj_list[i]->m_Src_rt.clear();
            m_Obj_list[i]->m_Desk_rt.clear();
        }
        m_Obj_list
    }*/

    for (auto iter = m_Obj_list.begin(); iter != m_Obj_list.end();)
    {
        (*iter)->Rt_Operate();
        if ((*iter)->m_bDead_flag) {
            (*iter)->m_Src_rt.clear();
            (*iter)->m_Desk_rt.clear();
            iter = m_Obj_list.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
 //   int i = 0;
 //  vITOR itor;
 //   for (itor = m_Obj_list.begin(); itor != m_Obj_list.end();)
 //   {
 //       //rt++
 //       
 //       m_Obj_list[i]->Rt_Operate();
 //
 //       if (m_Obj_list[i]->m_bDead_flag)
 //       {
 //           m_Obj_list[i]->m_Src_rt.clear();
 //           m_Obj_list[i]->m_Desk_rt.clear();
 //           itor = m_Obj_list.erase(m_Obj_list.begin() + i);
 //       
 //       }
 //       i++;
 //   }
    
    ////player 비행기 이동 계산
    //if (m_Obj_list[m_Player_Num]->m_before_pos.x < m_Obj_list[m_Player_Num]->m_pos.x)
    //{
    //    m_Obj_list[m_Player_Num]->m_fplayer_action_flag += 3 * g_fSecondPerFrame;
    //    if (m_Obj_list[m_Player_Num]->m_fplayer_action_flag > 1)
    //        m_Obj_list[m_Player_Num]->m_fplayer_action_flag = 1;
    //}
    //if (m_Obj_list[m_Player_Num]->m_before_pos.x ㅠ> m_Obj_list[m_Player_Num]->m_pos.x)
    //{
    //    m_Obj_list[m_Player_Num]->m_fplayer_action_flag -= 3 * g_fSecondPerFrame;
    //    if (m_Obj_list[m_Player_Num]->m_fplayer_action_flag < -1)
    //        m_Obj_list[m_Player_Num]->m_fplayer_action_flag = -1;
    //}
    //if (m_Obj_list[m_Player_Num]->m_before_pos.x == m_Obj_list[m_Player_Num]->m_pos.x)
    //{
    //    if (m_Obj_list[m_Player_Num]->m_fplayer_action_flag > 0)
    //        m_Obj_list[m_Player_Num]->m_fplayer_action_flag -= 5 * g_fSecondPerFrame;
    //    if (m_Obj_list[m_Player_Num]->m_fplayer_action_flag < 0)
    //        m_Obj_list[m_Player_Num]->m_fplayer_action_flag += 5 * g_fSecondPerFrame;
    //}
    //m_Obj_list[m_Player_Num]->m_before_pos.x = m_Obj_list[m_Player_Num]->m_pos.x;



    return true;
}
bool CABitmapMgr::Render()
{
    
    for (int i = 0; i < m_Obj_list.size(); i++) //모든 오브젝트 랜더(드로우)
    {
        if (m_Obj_list[i]->m_bDraw_flag = true)
        {
            m_Obj_list[i]->Render();
        }
    }


    return true;
}
bool CABitmapMgr::Release()
{
     /*for (ITOR itor = m_Bitmap_Map.begin(); itor != m_Bitmap_Map.end();)
    {
        CABitmap* pdata = itor->second;
        pdata->Release();
        delete pdata;
        itor = m_Bitmap_Map.erase(itor);
    }*/

    for (auto& element : m_Bitmap_Map) {
        element.second->Release();
        delete element.second; element.second = nullptr;
    }
    m_Bitmap_Map.clear();
    for (int i = 0; i < m_Obj_list.size(); i++)
    {
        m_Obj_list[i]->Release();
        
    }
    m_Obj_list.clear();
    return true;

}


CABitmapObject* CABitmapMgr::Load_Object(T_STR filename)//++ 맴버 데이터 입력 필요.
{
    if (filename.empty())
    {
        return nullptr;
    }

    T_STR maskfile_name = mask_key + filename;
    shared_ptr<CABitmapObject> temp_obj = make_shared<CABitmapObject>();
    //CABitmapObject temp;//삭제할 방법을 찾자.
    //CABitmapObject* temp_obj = &temp;//자식 포인터 받아서 배열 넣기 위한...
    //temp_obj = temp_obj->Clone();
    temp_obj->m_pbmp = Load_Bitmap(filename);//
    if (temp_obj->m_pbmp == nullptr)
    {
        //delete temp_obj;
        return nullptr;
    }
    temp_obj->m_pmask = Load_Bitmap(maskfile_name);//

    m_Obj_list.push_back(temp_obj);

    return temp_obj.get();
}
CABitmap* CABitmapMgr::Load_Bitmap(T_STR filename)
{

    // 중복제거
    for (ITOR itor = I_BITMAPMGR.m_Bitmap_Map.begin();
        itor != I_BITMAPMGR.m_Bitmap_Map.end();
        itor++)
    {
        if ((*itor).first == filename)
        {
            return itor->second;
        }
    }

    T_STR fullpath = File_path + filename;

    CABitmap* pbitmap = new CABitmap;
    //비트맵 로드 실패시
    if (pbitmap->Load(fullpath) == false)
    {
        delete pbitmap;
        return nullptr;
    }
    I_BITMAPMGR.m_Bitmap_Map.insert(make_pair(filename, pbitmap));
    return pbitmap;
}
bool CABitmapMgr::Load_Bitmap_Script(T_STR fullpathname) //오류시 nullptr 반환
{
    FILE* fp = nullptr;

    _wfopen_s(&fp, fullpathname.c_str(), _T("rt"));
    if (fp == nullptr) return false;

    int load_obj_num = 0;
    TCHAR name[256];
    TCHAR buffer[256] = { 0 };
    TCHAR bmp_file_name[256] = { 0 };
    _fgetts(buffer, _countof(buffer), fp);
    _stscanf_s(buffer, _T("%d"), &load_obj_num);
    for (int i = 0; i < load_obj_num; i++)
    {
        _fgetts(buffer, _countof(buffer), fp);
        _stscanf_s(buffer, _T("%s"), bmp_file_name, _countof(bmp_file_name));

        CABitmapObject* tmp = Load_Object(bmp_file_name);
        if (tmp == nullptr) return false;
        assert(tmp != nullptr);

        _fgetts(buffer, _countof(buffer), fp);
        _stscanf_s(buffer, _T("%s %d %f %f %d %f %f %f %d"), name, _countof(name), &tmp->m_iEnd_rt_num,
            &tmp->m_pos.x, &tmp->m_pos.y, &tmp->m_bLoop_flag, &tmp->m_fSprite_time, &tmp->m_fLife_time, &tmp->m_fAlpha, &tmp->m_bPlayer_flag);
        tmp->m_Obj_Name = name;

        for (int k = 0; k < tmp->m_iEnd_rt_num; k++)
        {
            shared_ptr<RECT> temp = make_shared<RECT>();
            shared_ptr<RECT> temp2 = make_shared<RECT>();
           // RECT* temp = new RECT;
           // RECT* temp2 = new RECT;
            _fgetts(buffer, _countof(buffer), fp);
            _stscanf_s(buffer, _T("%d %d %d %d"), &temp->left, &temp->top, &temp->right, &temp->bottom);
            
            *temp2 = *temp;
            tmp->m_Src_rt.push_back(temp);
            tmp->m_Desk_rt.push_back(temp2);


        }



    }
    return true;
}
