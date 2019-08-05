#include "Card.h"

Card::Card(int type, int num, int score): m_Card_type(type),m_Card_num(num),m_Card_Score(score)
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

Card::Card()
{

}


Card::~Card()
{
}
