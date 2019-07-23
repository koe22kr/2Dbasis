#include "Player.h"

bool Player::Hit_Card(Card hit_card)//get_score도 내부에서 함
{
    Card_List.push_back(hit_card);
    Set_Score();
}

void Player::Set_Score()
{
    Score = 0;
    Ace_Counter = 0;
    for (Card cards : Card_List)
    {
        if (cards.Get_Score() == 11)
        {
            Ace_Counter++;
        }
        Score += cards.Get_Score();
    }
    while (Ace_Counter > 0 && Score > 21)
    {
        Score -= 10;
        Ace_Counter--;
    }

}

Player::Player()
{
    m_bBe_Ready = false;
    Score = 0;
    Ace_Counter = 0;
}


Player::~Player()
{
}
