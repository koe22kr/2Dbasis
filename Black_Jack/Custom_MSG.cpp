#include "Custom_MSG.h"

void Custom_MSG::Push_msg(int target,WINT msg)
{
    m_My_msg.insert(make_pair(target, msg ));
}

list<WINT> Custom_MSG::Pop_msg(int target)//����Ʈ �ʱ�ȭ ��, Ÿ��Ű�� �޼����� ��� ���� ����Ʈ�� �־� ����
{
    m_list.clear();

    auto equal = m_My_msg.equal_range(target);
    auto iter = equal.first;
    auto end = equal.second;

    for (; iter != end; iter++)
    {
        m_list.push_back(iter->second);
    }
    return m_list;
    //WINT find = m_My_msg.find(target)->second;
    
    
    
}
void Custom_MSG::Clear_msg()
{
    m_list.clear();
    m_My_msg.clear();
    
}

Custom_MSG::Custom_MSG()
{
}


Custom_MSG::~Custom_MSG()
{
}
