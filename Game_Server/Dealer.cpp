#include "Dealer.h"
#include <ctime>

bool Dealer::Take_Card(Card hit_card)
{
    Card_List.push_back(hit_card);
    Set_Score();
}

bool Dealer::Hit_Dummy_card()
{
    Card dummy(DUMMY, 0, 0);
    Card_List.push_back(dummy);
}

bool Dealer::Erase_Dummy_Card()
{
    for (auto iter = Card_List.begin(); iter != Card_List.end();)
    {
        if (iter->Get_Type == 10)
        {
            Card_List.erase(iter);

        }
        else
        {
            iter++;
        }
    }
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


void Dealer::Hit(Player* pPlayer)
{
    char flag = 0;
    Card hit_card = Draw();
    if (hit_card.Check())
    {
        pPlayer->Take_Card(hit_card);
        User_Card_Info user_card;
        user_card.UID = pPlayer->UID;
        wcstombs(user_card.name, pPlayer->Name.c_str(), MAX_NAME_SIZE * 2);
        user_card.hit_card.m_Card_num = hit_card.Get_Num;
        user_card.hit_card.m_Card_type = hit_card.Get_Type;
        user_card.hit_card.m_Card_Score = hit_card.Get_Score;

        if (21 == pPlayer->m_iScore)
        {
            flag = 1;
            I_SENDER.Broadcast_Packet_Make(PACKET_BURST_OR_BLACK_JACK, &flag, 1); //블랙잭
            pPlayer->m_bTurn_End_Flag = true;
        }
        else if (21 < pPlayer->m_iScore)
        {
            flag = 0;
            I_SENDER.Broadcast_Packet_Make(PACKET_BURST_OR_BLACK_JACK, &flag, 1); //버스트
            pPlayer->m_bTurn_End_Flag = true;
        }
        else
        {
            I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_HIT, (char*)&user_card, MSG_USER_CARD_SIZE); //히트 성공
        }
    }
    else
    {
        flag = HIT_FAIL;
        I_SENDER.Single_Packet_Make(pPlayer, PACKET_ERROR_CODE, &flag, 1); //히트 실패//디버그용? 쓸일 없을 수도
    }
}

bool Dealer::Players_Turn_Check()
{
    int count = 0;
    for (auto piter : I_PLAYER_MGR.Player_map)
    {
        count += piter.second->m_bTurn_End_Flag;
    }
    if (count == I_PLAYER_MGR.Player_map.size())
    {
        return true;
    }
    return false;
}
bool Dealer::Wait_Sec(int sec)
{
    time_t now = time(NULL);
    if (Delta_Time == 0)
    {
        Delta_Time = now;
    }
    if (now - Delta_Time > 5)//시간 텀 준 후에.. 
    {
        Delta_Time = 0;
        return true;
    }
}

void Dealer::Reset_score()
{
    m_iScore = 0;
    m_iAce_Counter = 0;
    Card_List.clear();
}

bool Dealer::Waiting_Ready()
{
  //FSM으로


}



Dealer::Dealer()
{
    //m_bTurn_End_Flag = false;
}


Dealer::~Dealer()
{
}
