#pragma once

#include "Protocol.h"


class Msg_Box : public Singleton<Msg_Box>
{
    friend Singleton<Msg_Box>;
public:
    Msg_Box();
    ~Msg_Box();
public:
    multimap<int, WINT>  m_My_msg;
    list<WINT>           m_list;
public:
    void Push_Msg(int Key, WINT msg);
    list<WINT>* Pop_msg(int target);//m_list초기화후 push_back
    void Clear_msg();
};

#define I_MSG Msg_Box::GetInstance()