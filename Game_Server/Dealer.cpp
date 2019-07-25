#include "Dealer.h"

bool Dealer::Hit_Card(Card hit_card)//get_score도 내부에서 함
{
    Card_List.push_back(hit_card);
    Set_Score();
}

void Dealer::Set_Score()
{
    m_iScore = 0;
    m_iAce_Counter = 0;
    for (Card cards : Card_List)
    {
        if (cards.Get_Score() == 11)
        {
            m_iAce_Counter++;
        }
        m_iScore += cards.Get_Score();
    }
    while (m_iAce_Counter > 0 && m_iScore > 21)
    {
        m_iScore -= 10;
        m_iAce_Counter--;
    }

}

Dealer::Dealer()
{
    m_bTurn_End_Flag = false;
}


Dealer::~Dealer()
{
}
