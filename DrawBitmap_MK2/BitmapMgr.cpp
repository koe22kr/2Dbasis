#include "BitmapMgr.h"



CABitmapMgr::CABitmapMgr()
{
}


CABitmapMgr::~CABitmapMgr()
{
}

bool CABitmapMgr::Init()
{
    return true;
}
bool CABitmapMgr::Draw()
{
    for (int i = 0; i < m_Obj_list.size(); i++)
    {
        if (m_Obj_list[i]->m_rt.size() > 1)
            m_Obj_list[i]->Draw(m_Obj_list[i]->m_rt_num);
         

        else
        {
            m_Obj_list[i]->Draw();
        }
    }

    return true;
    //this->Draw(m_pos.x,m_pos.y,m_rt);
}
bool CABitmapMgr::Frame()
{
    //rt_num +1 , life_time!=0 && cur_time > lifetime  => erase
    for (int i = 0; i < m_Obj_list.size(); i++)
    {
        //rt++
        if (m_Obj_list[i]->m_rt_num == 0)
            m_Obj_list[i]->m_rt_num++;
        if (m_Obj_list[i]->m_max_frame_num != 1)
        {

            m_Obj_list[i]->m_fCur_time += g_fSecondPerFrame;    //현시간 += 프레임당
            m_Obj_list[i]->m_Delta_time += g_fSecondPerFrame;
            if (m_Obj_list[i]->m_Delta_time > g_fSecondPerFrame * m_Obj_list[i]->m_fLife_time)
            {
                m_Obj_list[i]->m_Delta_time -= m_Obj_list[i]->m_fLife_time / m_Obj_list[i]->m_max_frame_num;
                m_Obj_list[i]->m_rt_num += 1;
            }



            //if (m_Obj_list[i]->m_fCur_time > (m_Obj_list[i]->m_rt_num * 
            //    m_Obj_list[i]->m_fLife_time / m_Obj_list[i]->m_max_frame_num))
            //    m_Obj_list[i]->m_rt_num += 1;
            //현시간이 프레임당 걸리는 시간*현 프레임 보다 크면+1;


            //rt값 초과방지
            if (m_Obj_list[i]->m_rt_num > m_Obj_list[i]->m_max_frame_num)  //루프하고 프레임넘버 >사이즈 = 프레임초기화
            {
                if (m_Obj_list[i]->m_loop_flag == true)
                    m_Obj_list[i]->m_rt_num -= m_Obj_list[i]->m_max_frame_num;
                else
                {
                    m_Obj_list[i]->m_rt_num = min(m_Obj_list[i]->m_rt_num, m_Obj_list.size());
                }
            }
            //del
            //if (m_Obj_list[i]->m_fLife_time != 0 && m_Obj_list[i]->m_fLife_time < m_Obj_list[i]->m_fCur_time) ////라이프 타//임 !=0 && 라이프타임<현타임
            //{
            //    m_Obj_list[i]->m_rt.clear();
            //    m_Obj_list.erase(m_Obj_list.begin() + i);
            //}
        }
    }
    return true;
}
bool CABitmapMgr::Render()
{
    Draw();
    return true;
}
bool CABitmapMgr::Release()
{
        for (ITOR itor = m_Bitmap_Map.begin(); itor != m_Bitmap_Map.end();)
        {
            CABitmap* pdata = itor->second;
            pdata->Release();
            delete pdata;
            itor =m_Bitmap_Map.erase(itor);
            
        }
        for (int i = 0; i < m_Obj_list.size(); i++)
        {
            m_Obj_list[i]->m_rt.clear();
            m_Obj_list.erase(m_Obj_list.begin() + i);
        }
    return true;

}



CAObject* CABitmapMgr::Load_Object(T_STR filename)//++ 맴버 데이터 입력 필요.
{
    if (filename.empty())
    {
        return nullptr;
    }

    
    T_STR maskfile_name =  mask_key + filename;

    CAObject* NewObject = new CAObject;
    NewObject->m_pbmp = Load_Bitmap(filename);//
    if (NewObject->m_pbmp == nullptr)
    {
        delete NewObject;
        return nullptr;
    }
    NewObject->m_pmask = Load_Bitmap(maskfile_name);//

    m_Obj_list.push_back(NewObject);

    return NewObject;
}
CABitmap* CABitmapMgr::Load_Bitmap(T_STR filename)
{

    // 중복제거
    for (ITOR itor = m_Bitmap_Map.begin();
        itor != m_Bitmap_Map.end();
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
    m_Bitmap_Map.insert(make_pair(filename, pbitmap));
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

        CAObject* tmp = Load_Object(bmp_file_name);
        if (tmp == nullptr) return false;
        assert(tmp != nullptr);

        _fgetts(buffer, _countof(buffer), fp);
        _stscanf_s(buffer, _T("%s %d %f %f %d %f"), name, _countof(name), &tmp->m_max_frame_num,
            &tmp->m_pos.x, &tmp->m_pos.y, &tmp->m_loop_flag, &tmp->m_fLife_time);
        tmp->m_Obj_Name = name;

        for (int k = 0; k < tmp->m_max_frame_num; k++)
        {
            RECT* temp = new RECT;
            _fgetts(buffer, _countof(buffer), fp);
            _stscanf_s(buffer, _T("%d %d %d %d"), &temp->left, &temp->top, &temp->right, &temp->bottom);
            tmp->m_rt.push_back(temp);
        }

        //bitmap1.bmp 
        //rtExplosion 12    100  100   1         0          1
        //name        frame posx posy  loop_flag life_time  dummy[dead_flag]


    }
    return true;
}
