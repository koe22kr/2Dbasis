#include "Card.h"

Card::Card(byte type, byte num, byte score): m_Card_type(type),m_Card_num(num),m_Card_Score(score)
{
}

bool Card::Check() const
{
    if (this->m_Card_num == 0 || this->m_Card_type == 0)
    {
        return false;
    }
    return true;
}
//
//int Card::Get_Score() const
//{
//    return m_Card_Score;
//}


Card::Card()
{
}


Card::~Card()
{
}
