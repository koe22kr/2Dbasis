#include "CAScriptMgr.h"

void CAScriptMgr::Load_File_Script(T_STR name)
{
    //FILE* fp = nullptr;
    T_STR full_file_path = Script_folder + name;
    //_wfopen_s(&fp, full_file_path.c_str, _T("rt"));
    //if (fp == nullptr) return nullptr;
    //
    //int load_script_num = 0;
    //TCHAR buffer[256];
    //TCHAR script_name[256];
    //
    //
    //_fgetts(buffer, _countof(buffer), fp);
    //
    //_stscanf_s(buffer, _T("%d"), &load_script_num);
    //for (int i = 0; i < load_script_num; i++) //��ũ��Ʈ �̸� �ε�
    //{
    //    FILE* script_fp=nullptr;
    //    full_file_path = File_path + script_name;
    //    _fgetts(buffer, _countof(buffer), fp);
    //    _stscanf_s(buffer, _T("%s"), _countof(script_name));
    //    
    //    _wfopen_s(&script_fp, full_file_path.c_str, _T("rt"));//��Ʈ�� �̶�� ��Ʈ�� ��ũ��Ʈ ��...
        
        
        /*if (script_name == _T("bitmap_object.txt"))
            I_BITMAPMGR.Load_Bitmap_Script(_T("bitmap_object.txt"));*/
    I_BITMAPMGR.Load_Bitmap_Script(full_file_path);
    
//    fclose(fp);
}

CAScriptMgr::CAScriptMgr()
{
}


CAScriptMgr::~CAScriptMgr()
{
}
