#include "CABitmapMgr.h"


void CABitmapMgr::Draw()
{

}

//void CABitmapMgr::Move( float x,float y)//
//{
//    m_pPlayer->m_pos.x += x;
//    m_pPlayer->m_pos.y += y;
//}
void CABitmapMgr::Set_Obj(float inx, float iny, RECT rt, float fSpeed)
{
    /////
}
CAObject* CABitmapMgr::Load_File(T_STR filename)
{
   
    if (filename.empty())
    {
        return nullptr;
    }
    T_STR fullpath = File_path + filename;
 
   
    CAObject* pobject = new CAObject;
    
    for (ITOR itor = m_Bitmap_Map.begin();   // 중복제거
        itor != m_Bitmap_Map.end();
        itor++)
    {
        if ((*itor).first == filename)
        {
            pobject->m_pbmp = itor->second;
            m_Obj_list.push_back(pobject);
            return pobject;
        }
    
    }
    CABitmap* pbitmap = new CABitmap;

    if (pbitmap->Load(fullpath) == false)
    {
        delete pobject;
        delete pbitmap;
        return nullptr;
    }
    m_Bitmap_Map.insert(make_pair(filename, pbitmap));
    
    pobject->m_pbmp = pbitmap;
    return pobject;

}

bool CABitmapMgr::Load_Bitmap_Script(T_STR fullpathname) //오류시 nullptr 반환
{
    FILE* fp = nullptr;
    
    _wfopen_s(&fp, fullpathname.c_str(), _T("rt"));
    if (fp == nullptr) return false;

    int load_obj_num = 0;
    int m_max_frame_num = 0;
    TCHAR buffer[256] = { 0 };
    TCHAR bmp_file_name[256] = { 0 };
    _fgetts(buffer, _countof(buffer), fp);
    _stscanf_s(buffer, _T("%d"), &load_obj_num); 
    for(int i = 0;i < load_obj_num;i++)
    {
        _fgetts(buffer, _countof(buffer), fp);
        _stscanf_s(buffer, _T("%s"), bmp_file_name,_countof(bmp_file_name));

        CAObject* tmp = Load_File_with_mask(bmp_file_name);
        if (tmp == nullptr) return false;
        assert(tmp != nullptr);
        _fgetts(buffer, _countof(buffer), fp);
        _stscanf_s(buffer, _T("%s %d %f %f %d %f %d"), &tmp->m_Obj_ID,_countof(tmp->m_Obj_ID), &tmp->m_max_frame_num,
                                               &tmp->m_pos.x, &tmp->m_pos.y, &tmp->m_loop_flag, &tmp->m_fLife_time,  &tmp->dead_flag);


        for (int k = 0; k < tmp->m_max_frame_num; k++)
        {
            
            RECT* temp = new RECT;
            _fgetts(buffer, _countof(buffer), fp);
            _stscanf_s(buffer, _T("%d %d %d %d"), &temp->left, &temp->top, &temp->right, &temp->bottom);
            tmp->m_rt.push_back(*temp);
        }

        //bitmap1.bmp 
        //rtExplosion 12    100  100   1         0          1
        //name        frame posx posy  loop_flag life_time  dummy[dead_flag]


    }
    return true;
}

CAObject* CABitmapMgr::Load_File_with_mask(T_STR filename)
{
    T_STR maskfile_name = File_path + mask_key + filename;
    
    CAObject* first;
    first = Load_File(File_path + filename);
    if (first == nullptr)
        return nullptr;
    
  //  CAObject* first = new CAObject;
  //  first = temp;

    CAObject* second;
    second = Load_File(maskfile_name);
    if (second == nullptr)
    {
        return first;
    }
 
   // CAObject* second = new CAObject;
   // second = temp;

    first->m_pmask = second->m_pbmp;
    second->mask_flag = true;
    
    
    return first;
}


//bool CABitmapMgr::Delete(T_STR key)// 리리스 할때 델리트 할듯? 있어도 안쓸것 같다.
//{
//    ITOR itor = m_Bitmap_Map.find(key);
//    if (itor == m_Bitmap_Map.end())
//    {
//        return false;
//    }
//    CABitmap* pdata = itor->second;
//    pdata->Release();
//    delete pdata;
//    m_Bitmap_Map.erase(itor);
//    return true;
//}

bool CABitmapMgr::Init()
{
    return true;
}
//for (m_loop_flag)
//

bool CABitmapMgr::Delete_Dead_Obj()
{
    for (int i = 0; i < m_Obj_list.size(); i++)
    {
    }
    return true;
}
bool CABitmapMgr::Frame()
{
    
    for (int i = 0; i < m_Obj_list.size(); i++)
    {
        m_Obj_list[i]->m_fCur_time += g_fSecondPerFrame;    //현시간 += 프레임당시간
        if(m_Obj_list[i]->m_fCur_time > (m_Obj_list[i]->m_rt_num * m_Obj_list[i]->m_fLife_time / m_Obj_list[i]->m_max_frame_num))   //현시간이 프레임당 걸리는 시간*현 프레임 보다 크면+1;
        m_Obj_list[i]->m_rt_num += 1;
        
        
        //루프,오버 = 초기화,노 루프 오버 = 최대값 유지.
        if (m_Obj_list[i]->m_rt_num > m_Obj_list.size())  //루프하고 프레임넘버 >사이즈 = 프레임초기화
        {
            if (m_Obj_list[i]->m_loop_flag == true)
                m_Obj_list[i]->m_rt_num -= m_Obj_list[i]->m_max_frame_num;
            else
            {
                m_Obj_list[i]->m_rt_num =min(m_Obj_list[i]->m_rt_num, m_Obj_list.size());
            }
        }
            
        //
        {
            if (m_Obj_list[i]->m_fLife_time != 0 && m_Obj_list[i]->m_fLife_time < m_Obj_list[i]->m_fCur_time) ////라이프 타임 !=0 && 라이프타임<현타임
                m_fLife_time!= 0 && m_fLife_time< m_fCur_time
            {
                m_Obj_list[i]->m_rt.clear();
                m_Obj_list.erase(m_Obj_list.begin() + i);
            }
        }
       
        
    }
    return true;
}
bool CABitmapMgr::Render()
{
    for (int i = 0; i < m_Obj_list.size(); i++)
    {
        if (m_Obj_list[i]->m_rt.size() > 1)
            m_Obj_list[i]->Render(m_Obj_list[i]->m_rt_num);
        

        else
        {
            m_Obj_list[i]->Render();
        }
    }
    
    return true;    
    //this->Draw(m_pos.x,m_pos.y,m_rt);
}
bool CABitmapMgr::Release()
{
//    for (ITOR itor = m_Bitmap_Map.begin(); itor != m_Bitmap_Map.end();)
//    {
//        CABitmap* pdata = itor->second;
//        pdata->Release();
//        delete pdata;
//        m_Bitmap_Map.erase(itor);
//        
//    }
//    for (int i = 0; i < m_Obj_list.size(); i++)
//    {
//        m_Obj_list[i]->m_rt.clear();
//        m_Obj_list.erase(m_Obj_list.begin() + i);
//    }
    return true;

}

CABitmapMgr::CABitmapMgr()
{

}
CABitmapMgr::~CABitmapMgr()
{

}