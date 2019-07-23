#include "Server_Game.h"
#include "ODBC_Query.h"
#include <ctime>
void Server_Game::Init()
{
    Createthread();
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
            Send(PACKET_NEW_ACCOUNT_ACK, Player target_iter->second) 2004
        }break;
        case PACKET_LOGIN_RQ://2005
        {
            Broadcast(PACKET_JOIN_NEW_USER, UID);
            Send(PACKET_LOGIN_ACK,Player target_iter->second);// 2006 
        }
        case PACKET_GAME_READY://3001
        {
            if (target_iter->second->m_bBe_Ready == false)
            {
               //모든 유저 ready 확인
                target_iter->second->m_bBe_Ready = true;
                Ready_Count++;
                Broadcast(PACKET_SOME_BODY_READY, UID);
            }
            
        }break;
        case PACKET_GAME_READY_CANCEL://3003
        {
            if (target_iter->second->m_bBe_Ready == true)
            {
                target_iter->second->m_bBe_Ready = false;
                Ready_Count--;
                Broadcast(PACKET_SOME_BODY_READY_CANCEL, UID);
            }
        }
        case PACKET_COMMAND_HIT://4001    //Phase가 Player_Turn 필요.
        {
            Card hit_card = m_Dealer.Draw();
            if (hit_card.Check())
            {
                target_iter->second->Hit_Card(hit_card);

                Broadcast(PACKET_SOME_BODY_HIT, hit_card);
            }
        }break;
        case PACKET_COMMAND_STAY://4002
        {
            Broadcast(PACKET_SOME_BODY_STAY, UID);
        }break;

        default:
            break;
        }
    }
    //페이즈 101,102 시작전
    if (Ready_Count >= I_PLAYER_MGR.Player_map.size())//유저가 준비했을때 현재의 상황 확인, 매 프레임당 확인X
    {
        if (Phase != All_Player_Ready)
        {
            Broadcast(PACKET_ALL_PLAYER_READY);
        }
        time_t now = time(NULL);
        if (Delta_Time == 0)
        {
            Delta_Time = now;
        }
        if (now - Delta_Time > 5)//시간 텀 준 후에.. 타이머
        {
            send(PACKET_GAME_START);// 3002  
            Phase = Dealer_Turn;//Init 에서 카드 리셋 하기.
        }
    }
    else
    {
        Phase = Waitting_Ready;
    }


}



    





Server_Game::Server_Game()
{
   
}


Server_Game::~Server_Game()
{
}

