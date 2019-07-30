#pragma once
#include "Server_std.h"

class Custom_MSG : public Singleton<Custom_MSG>
{
    friend Singleton<Custom_MSG>;
    
   multimap<int, WINT>  m_My_msg;
   list<WINT>           m_list;

    Custom_MSG();
public:
    


public:
    virtual ~Custom_MSG();
    
    void Push_msg(int target,WINT msg);
    list<WINT> Pop_msg(int target);//m_list초기화후 push_back
    void Clear_msg();

};

#define CA_MSG Custom_MSG::GetInstance()