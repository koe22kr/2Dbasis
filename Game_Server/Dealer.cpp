#include "Dealer.h"
#include <ctime>

bool Dealer::Hit_Card(Card hit_card)//get_score도 내부에서 함
{
    Card_List.push_back(hit_card);
    Set_Score();
}

bool Dealer::Hit_Dummy_card()
{
    Card dummy(DUMMY, 0, 0);
    Card_List.push_back(dummy);
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

bool Dealer::Waiting_Ready()
{
    ///////////////////////Waitting_Ready//////////////////  레디시,취소시, 참가시 처리
    while (m_dwPhase == Waitting_Ready || m_dwPhase == All_Player_Ready)
    {
        if (User_Ready_Check())
        {
            if (m_dwPhase != All_Player_Ready)
            {
                I_SENDER.Broadcast_Packet_Make(PACKET_ALL_PLAYER_READY);
            }
            time_t now = time(NULL);
            if (Delta_Time == 0)
            {
                Delta_Time = now;
                m_dwPhase = All_Player_Ready;

            }
            if (now - Delta_Time > 5)//시간 텀 준 후에.. 타이머
            {
                I_SENDER.Broadcast_Packet_Make(PACKET_GAME_START);
                m_dwPhase = Set_Up_Turn;//Init 에서 카드 리셋 하기.
                Delta_Time = 0;
            }
        }
        else
        {
            m_dwPhase = Waitting_Ready;
            Delta_Time = 0;

        }
    }


}

bool Dealer::User_Ready_Check()
{
    int count = 0;
    for (auto piter : I_PLAYER_MGR.Player_map)
    {
        count += piter.second->m_bBe_Ready;
    }
    if (count == I_PLAYER_MGR.Player_map.size())
    {
        return true;
    }
    return false;
}


Dealer::Dealer()
{
    //m_bTurn_End_Flag = false;
}


Dealer::~Dealer()
{
}
