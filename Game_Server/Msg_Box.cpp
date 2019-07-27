#include "Msg_Box.h"

void Msg_Box::Push_Msg(int key,WINT msg)
{

    m_My_msg.insert(make_pair(key, msg));

}

list<WINT>* Msg_Box::Pop_msg(int target)
{
    m_list.clear();

    auto equal = m_My_msg.equal_range(target);
    auto iter = equal.first;
    auto end = equal.second;

    for (; iter != end; iter++)
    {
        m_list.push_back(iter->second);
    }
    return &m_list;

}

void Msg_Box::Clear_msg()
{
    m_list.clear();
    m_My_msg.clear();
}


Msg_Box::Msg_Box()
{
}


Msg_Box::~Msg_Box()
{
}
