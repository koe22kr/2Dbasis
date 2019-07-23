#include "Server_Game.h"
#include "ODBC_Query.h"
#include <ctime>
void Server_Game::Init()
{
    Createthread();
    I_ACCEPTOR.Init();
    I_ACCEPTOR.CreateThread();
    I_IOCP.Init();//�߰� Ȯ�� ���.
    I_IOCP.CreateThread();

}

void Server_Game::I_Wanna_Go_Home()
{
    I_IOCP.Release();
    //Release �迭 �ϱ�.
    
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
        //case PACKET_ACCESS_RQ://2001            //���� on ���� Ȯ��?
        //{//
        //    //Ŭ�� ���� -> ��Ƽ �����Ͽ� ���� ��û
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
               //��� ���� ready Ȯ��
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
        case PACKET_COMMAND_HIT://4001    //Phase�� Player_Turn �ʿ�.
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
    //������ 101,102 ������
    if (Ready_Count >= I_PLAYER_MGR.Player_map.size())//������ �غ������� ������ ��Ȳ Ȯ��, �� �����Ӵ� Ȯ��X
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
        if (now - Delta_Time > 5)//�ð� �� �� �Ŀ�.. Ÿ�̸�
        {
            send(PACKET_GAME_START);// 3002  
            Phase = Dealer_Turn;//Init ���� ī�� ���� �ϱ�.
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

