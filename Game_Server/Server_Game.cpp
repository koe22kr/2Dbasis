#include "Server_Game.h"
#include "ODBC_Query.h"

void Server_Game::Init()
{
    I_ACCEPTOR.CreateThread();
}

void Server_Game::Pre_Frame()   
{
  //  Recv();
    //������ ��Ŷ �з��ؼ� �����ͷ� ������? MSG �� �ְ� �����Ϳ��� MSG ��� Ȯ���ϴ� ������� �ϴ°͵� ������ ������ �ʹ�.
    //�ϴ� ��ó�� �� ������
}

void Server_Game::Post_Frame()
{
   // Send();
    //ó���� ��Ŷ ������ ��Ʈ.
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
        //    //Ŭ�� ���� -> ��Ƽ �����Ͽ� ���� ��û
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
            //player_map ��ȸ�� ������� �غ��
            //PACKET_GAME_START 3002  �߼�
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

