#include "Server_Game.h"
#include "ODBC_Query.h"

void Server_Game::Init()
{
    I_ACCEPTOR.CreateThread();
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
    for (auto packet : I_Packet_Pool.Get())
    {
        switch (packet.ph.type)
        {
        //case PACKET_ACCESS_RQ://2001
        //{//
        //    //클라 실행 -> 멀티 실행하여 접속 요청
        //    //PACKET_ACCESS_ACK 2002 
        //}break;
        case PACKET_NEW_ACCOUNT_RQ://2003
        {
            
            //PACKET_NEW_ACCOUNT_ACK 2004

        }break;
        case PACKET_LOGIN_RQ://2005
        {
            I_
            //PACKET_LOGIN_ACK 2006
        }
        case PACKET_GAME_READY://3001
        {
            //player_map 순회후 모든유저 준비시
            //PACKET_GAME_START 3002  발송
        }break;
        case PACKET_COMMAND_HIT://4001
        {
            //PACKET_UPDATE 9000 
        }break;
        case PACKET_COMMAND_STAY://4002
        {
            //PACKET_UPDATE 9000 
        }break;

        default:
            break;
        }
    }




}



Server_Game::Server_Game()
{
   
}


Server_Game::~Server_Game()
{
}

