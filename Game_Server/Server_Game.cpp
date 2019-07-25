#include "Server_Game.h"
#include "ODBC_Query.h"
#include <ctime>
#include "Card.h"//
void Server_Game::Init()
{
    CreateThread();
    I_ACCEPTOR.Init();
    I_ACCEPTOR.CreateThread();
    I_IOCP.Init();//추가 확인 요망.
    I_IOCP.CreateThread();
    

}

void Server_Game::I_Wanna_Go_Home()
{
    I_IOCP.Release();
    //Release 계열 하기.
    
}

void Server_Game::Pre_Frame()   
{
  //  Recv();
    //수신한 패킷 분류해서 데이터로 보내기? MSG 로 넣고 데이터에서 MSG 열어서 확인하는 방식으로 하는것도 나쁘지 않을듯 싶다.
    //일단 전처리 용 프래임
}

void Server_Game::Post_Frame()
{
   // Send();
    //처리후 패킷 보내는 파트.
    //
}
void Server_Game::Frame()
{
    byte alpha = 9;
    char flag;
    for (auto packet : I_Packet_Pool.Get())
    {
        auto target_iter = I_PLAYER_MGR.Player_map.find(packet.ph.UID);//
        if (target_iter == I_PLAYER_MGR.Player_map.end())
        {
            continue;
        }
        switch (packet.ph.type)
        {
            //case PACKET_ACCESS_RQ://2001            //서버 on 여부 확인?
            //{//
            //    //클라 실행 -> 멀티 실행하여 접속 요청
            //    //PACKET_ACCESS_ACK 2002 
            //}break;
        case PACKET_NEW_ACCOUNT_RQ://2003
        {
            if (New_Account_Success)
            {
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_NEW_ACCOUNT_ACK);
            }
        }break;
        case PACKET_LOGIN_RQ://2005
        {


            if (Login_Successs)
            {
                User_Info new_user_info;
                new_user_info.UID = target_iter->second->UID;
                wcstombs(new_user_info.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                I_SENDER.Broadcast_Packet_Make(PACKET_JOIN_NEW_USER, (char*)&new_user_info, MSG_USER_INFO_SIZE); //임의 유저 접속 알림
                flag = 1;   //1 성공 
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_LOGIN_ACK, &flag, 1); //로그인 승락
                for (auto players : I_PLAYER_MGR.Player_map)//현재 접속 플레이어 정보 송신
                {
                    User_Info user_infos;
                    user_infos.UID = players.second->UID;
                    wcstombs(user_infos.name, players.second->Name.c_str(), MAX_NAME_SIZE * 2);
                    I_SENDER.Single_Packet_Make(target_iter->second, PACKET_UPDATE, (char*)&user_infos, MSG_USER_INFO_SIZE);
                }
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_UPDATE_END); //업데이트 끝 알림 패킷
            }
            else
            {
                flag = 0; //로그인 실패
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_LOGIN_ACK, &flag, 1); //로그인 거부
            }

        }break;
        case PACKET_GAME_READY://3001
        {
            if (target_iter->second->m_bBe_Ready == false)
            {
                //모든 유저 ready 확인
                target_iter->second->m_bBe_Ready = true;
                m_iReady_Count++;
                User_Info ready_user;
                ready_user.UID = target_iter->second->UID;

                wcstombs(ready_user.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_READY, (char*)&ready_user, MSG_USER_INFO_SIZE);
            }
        }break;

        case PACKET_GAME_READY_CANCEL://3003
        {
            if (target_iter->second->m_bBe_Ready == true)
            {
                target_iter->second->m_bBe_Ready = false;
                m_iReady_Count--;
                Delta_Time = 0;
                User_Info cancel_user;
                cancel_user.UID = target_iter->second->UID;
                wcstombs(cancel_user.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_READY_CANCEL, (char*)&cancel_user, MSG_USER_INFO_SIZE);
            }
        }break;
        case PACKET_COMMAND_HIT://4001    //m_dwPhase가 Player_Turn 필요.
        {
            Card hit_card = m_Dealer.Draw();
            if (hit_card.Check())
            {
                target_iter->second->Hit_Card(hit_card);
                User_Card_Info user_card;
                user_card.UID = target_iter->second->UID;
                wcstombs(user_card.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                user_card.hit_card.m_Card_num = hit_card.Get_Num;
                user_card.hit_card.m_Card_type = hit_card.Get_Type;
                user_card.hit_card.m_Card_Score = hit_card.Get_Score;

                if (21 == target_iter->second->m_iScore)
                {
                    flag = 1;
                    I_SENDER.Broadcast_Packet_Make(PACKET_BURST_OR_BLACK_JACK, &flag, 1); //블랙잭
                    target_iter->second->m_bTurn_End_Flag = true;
                }
                else if (21 < target_iter->second->m_iScore)
                {
                    flag = 0;
                    I_SENDER.Broadcast_Packet_Make(PACKET_BURST_OR_BLACK_JACK, &flag, 1); //버스트
                    target_iter->second->m_bTurn_End_Flag = true;
                }
                else
                {
                    I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_HIT, (char*)&user_card, MSG_USER_CARD_SIZE); //히트 성공
                }
            }
            else
            {
                flag = HIT_FAIL;
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_ERROR_CODE, &flag, 1); //히트 실패//디버그용? 쓸일 없을 수도
            }
        }break;
        case PACKET_COMMAND_STAY://4002
        {
            User_Info stay_user;
            wcstombs(stay_user.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
            stay_user.UID = target_iter->second->UID;

            I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_STAY, (char*)&stay_user, MSG_USER_INFO_SIZE);
            target_iter->second->m_bTurn_End_Flag = true;
        }break;

        default:
            break;
        }
        이름 변경 추가 하기
            I_SENDER.Send();


    }//for_end





    ///////////////////////Waitting_Ready//////////////////
    if (m_dwPhase == Waitting_Ready &&
        m_iReady_Count >= I_PLAYER_MGR.Player_map.size())//유저가 준비했을때 현재의 상황 확인, 매 프레임당 확인X
    {
        if (m_dwPhase != All_Player_Ready)
        {
            I_SENDER.Broadcast_Packet_Make(PACKET_ALL_PLAYER_READY);
        }
        time_t now = time(NULL);
        if (Delta_Time == 0)
        {
            Delta_Time = now;
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
    }
    //////////////////////////////////////////////////////
    ///////////////////Set_Up_Turn;//////////////////////
    SET_UP_TURN();

    ////////////////////////////////////////////////////
    //////////////////Player_Turn///////////////////////
    if (m_dwPhase == Player_Turn)
    {
        if (m_iTurn_End_Count >= I_PLAYER_MGR.Player_map.size())
        {
            m_dwPhase = Dealer_Turn;
            //플레이어 턴 종료
        }
        else
        {
            //플레이어 턴 해야할것?


        }

    }
    /////////////////////////////////////////////////////
    /////////////////Dealer_Turn///////////////////////// 딜러 FSM 에 집어 넣어도 될듯.
    while (m_dwPhase == Dealer_Turn)
    {
        Card hit_card = m_Dealer.Draw();
        if (hit_card.Check())
        {
            m_Dealer.Hit_Card(hit_card);
            if (21 == m_Dealer.m_iScore)
            {
                m_dwPhase = ALL_Turn_Over;
            }
            else if (16 < m_Dealer.m_iScore)
            {
                m_dwPhase = ALL_Turn_Over;
            }

        }
    }
    ////////////////////////////////////////////////////////
    /////////////////ALL_Turn_Over////////////////////// Judgement();
    for (auto player : I_PLAYER_MGR.Player_map)
    {

        if (21 < player.second->m_iScore)
        {
            User_Info pinfo;
            pinfo.UID = player.second->UID;
            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);

            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_LOSE, (char*)&pinfo, MSG_USER_INFO_SIZE);

        }
        else if (21 == player.second->m_iScore ||
                 m_Dealer.m_iScore <= player.second->m_iScore)
        {
            User_Info pinfo;
            pinfo.UID = player.second->UID;
            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);

            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_WIN, (char*)&pinfo, MSG_USER_INFO_SIZE);
        }
        else if (m_Dealer.m_iScore > player.second->m_iScore)
        {
            User_Info pinfo;
            pinfo.UID = player.second->UID;
            wcstombs(pinfo.name, player.second->Name.c_str(), MAX_NAME_SIZE * 2);

            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_LOSE, (char*)&pinfo, MSG_USER_INFO_SIZE);
        }
    }


    time_t now = time(NULL);
    if (Delta_Time == 0)
    {
        m_dwPhase = Re_Set; // 게임 리셋 
        Delta_Time = now;
    }
    if (now - Delta_Time > 5)//시간 텀 준 후에.. 
    {

        m_dwPhase = Waitting_Ready;// 이어서.
        Delta_Time = 0;
    }
    
}

   
    /////////////////////////////////////////////////////




    





Server_Game::Server_Game()
{
   
}


Server_Game::~Server_Game()
{
}

