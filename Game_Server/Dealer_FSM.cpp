#include "Dealer_FSM.h"
#include <time.h>
/////////////////////////////////////
bool Waiting_Ready::Action()
{
    ///////////////////////Waitting_Ready//////////////////  레디시,취소시, 참가시 처리
   // while (g_dwPhase == WAITING_READY || g_dwPhase == ALL_PLAYER_READY)
    {
        if (User_Ready_Check())
        {
            g_dwPhase = 102;
            I_SENDER.Broadcast_Packet_Make(PACKET_ALL_PLAYER_READY);
            

            
        }
        else
        {
            g_dwPhase = WAITING_READY;
            I_DEALER.Delta_Time = 0;

        }
    }
    return true;
}


bool Waiting_Ready::User_Ready_Check()
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

Waiting_Ready::Waiting_Ready()
{

}
Waiting_Ready::~Waiting_Ready()
{

}
////////////////////////////////////////
bool All_Player_Ready::Action()
{
    if (User_Ready_Check())
    {


        time_t now = time(NULL);
        if (I_DEALER.Delta_Time == 0)
        {
            I_DEALER.Delta_Time = now;
        }
        if (now - I_DEALER.Delta_Time > 5)//시간 텀 준 후에.. 타이머
        {
            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_START);
            Set_Up();
            I_DEALER.Delta_Time = 0;
            g_start_flag = true;
        }
    }
    else
    {
        g_dwPhase = WAITING_READY;
    }
    return true;
}

bool All_Player_Ready::User_Ready_Check()
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


void All_Player_Ready::Set_Up()
{
    I_DEALER.Reset_Deck();
    Card hit_card = I_DEALER.Draw();
    if (!hit_card.Check())
    {
        throw out_of_range("dealer_card_hit_check_fail");
    }
    I_DEALER.Take_Card(hit_card);
   // I_DEALER.Hit_Dummy_card(); //더미카드를 뒷면 카드로. 매핑

    for (auto Piter : I_PLAYER_MGR.Player_map)
    {
        I_DEALER.Hit(Piter.second);
        I_DEALER.Hit(Piter.second);
    }

    g_dwPhase = PLAYER_TURN;

}

All_Player_Ready::All_Player_Ready()
{
}

All_Player_Ready::~All_Player_Ready()
{
}

/////////////////////////////////////
bool Player_Turn::Action()
{
    m_iTurn_End_Count = 0;
    if (g_dwPhase == PLAYER_TURN)
    {
        for (auto piter : I_PLAYER_MGR.Player_map)
        {
            m_iTurn_End_Count += piter.second->m_bTurn_End_Flag;
        }
        if (m_iTurn_End_Count >= I_PLAYER_MGR.Player_map.size())
        {
            g_dwPhase = DEALER_TURN;
        }
        else
        {
           //대 기
        }

    }
    return true;
}



Player_Turn::Player_Turn()
{
}
Player_Turn::~Player_Turn()
{
}
/////////////////////////////////////
bool Dealer_Turn::Action()
{
    while (g_dwPhase == DEALER_TURN)
    {
       // I_DEALER.Erase_Dummy_Card();
        Card hit_card = I_DEALER.Draw();
        if (hit_card.Check())
        {
            I_DEALER.Take_Card(hit_card);
            /*if (21 == I_DEALER.m_iScore)
            {
                Judgement();
            }
            else*/ 
            if (16 < I_DEALER.m_iScore)
            {
                Judgement();
            }
        }
    }
    return true;

}

void Dealer_Turn::Judgement()
{
    for (auto player : I_PLAYER_MGR.Player_map)//한번만
    {
        if (21 < player.second->m_iScore)
        {
            User_Info pinfo;
            pinfo.UID = player.second->UID;
            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);

            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_LOSE, (char*)&pinfo, MSG_USER_INFO_SIZE);

        }
        else if (21 < I_DEALER.m_iScore && player.second->m_iScore < 21)
        {
            User_Info pinfo;
            pinfo.UID = player.second->UID;
            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);

            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_WIN, (char*)&pinfo, MSG_USER_INFO_SIZE);
        }
        else if (21 == player.second->m_iScore ||
            (I_DEALER.m_iScore <= player.second->m_iScore))
        {
            User_Info pinfo;
            pinfo.UID = player.second->UID;
            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);

            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_WIN, (char*)&pinfo, MSG_USER_INFO_SIZE);
        }
        else if (I_DEALER.m_iScore > player.second->m_iScore)
        {
            User_Info pinfo;
            pinfo.UID = player.second->UID;
            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);

            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_LOSE, (char*)&pinfo, MSG_USER_INFO_SIZE);
        }
    }


    Reset();                   
    g_dwPhase = WAITING_READY;// 재시작
}

void Dealer_Turn::Reset()
{
    I_DEALER.Reset_Deck();
    I_DEALER.Reset_score();
    for (auto piter : I_PLAYER_MGR.Player_map)
    {
        piter.second->Reset_Score();
    }
}
Dealer_Turn::Dealer_Turn()
{
}
Dealer_Turn::~Dealer_Turn()
{
}
//////////////////////////////////

//bool ALL_Turn_Over::Action()//JUDGEMENT
//{
//    for (auto player : I_PLAYER_MGR.Player_map)//한번만
//    {
//        if (21 < player.second->m_iScore)
//        {
//            User_Info pinfo;
//            pinfo.UID = player.second->UID;
//            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);
//
//            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_LOSE, (char*)&pinfo, MSG_USER_INFO_SIZE);
//
//        }
//        else if (21 == player.second->m_iScore ||
//            I_DEALER.m_iScore <= player.second->m_iScore)
//        {
//            User_Info pinfo;
//            pinfo.UID = player.second->UID;
//            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);
//
//            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_WIN, (char*)&pinfo, MSG_USER_INFO_SIZE);
//        }
//        else if (I_DEALER.m_iScore > player.second->m_iScore)
//        {
//            User_Info pinfo;
//            pinfo.UID = player.second->UID;
//            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);
//
//            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_LOSE, (char*)&pinfo, MSG_USER_INFO_SIZE);
//        }
//    }
//
//
//            Reset();                   //
//            g_dwPhase = WAITING_READY;// 재시작
//    
//}
//
//
//ALL_Turn_Over::ALL_Turn_Over()
//{
//}
//ALL_Turn_Over::~ALL_Turn_Over()
//{
//}
//
/////////////////////////////////////

///////////////////////////////
Dealer_FSM::Dealer_FSM()
{
 //  WAITING_READY = 101,
 //  PLAYER_TURN = 104,
 //  DEALER_TURN = 105,
    
    Status_list[WAITING_READY] = new Waiting_Ready;
    Status_list[ALL_PLAYER_READY] = new All_Player_Ready;
    Status_list[PLAYER_TURN] = new Player_Turn;
    Status_list[DEALER_TURN] = new Dealer_Turn;


}

void Dealer_FSM::FSM_Action(int status_num)
{
    Status_list[status_num]->Action();
}

Dealer_FSM::~Dealer_FSM()
{
    for (auto iter : Status_list)
    {
        delete iter.second;
    }
    Status_list.clear();
}
