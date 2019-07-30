#include "Server_Game.h"
#include "ODBC_Query.h"
#include "Card.h"//
void Server_Game::Init()
{
    CreateThread();
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

bool Server_Game::New_Account(Packet packet)
{
    TCHAR buf[20] = { 0 };
    mbstowcs(buf, packet.msg, sizeof(buf));
    ODBC.Stproc_New(buf);
    return true; //�ٲ�����
}
//
//void Server_Game::Pre_Frame()   
//{
//  //  Recv();
//    //������ ��Ŷ �з��ؼ� �����ͷ� ������? MSG �� �ְ� �����Ϳ��� MSG ��� Ȯ���ϴ� ������� �ϴ°͵� ������ ������ �ʹ�.
//    //�ϴ� ��ó�� �� ������
//}
//
//void Server_Game::Post_Frame()
//{
//   // Send();
//    //ó���� ��Ŷ ������ ��Ʈ.
//    //
//}
void Server_Game::Frame()
{
    while (true)
    {
        byte alpha = 9;
        char flag;
        while (I_Packet_Pool.Get().begin() != I_Packet_Pool.Get().end())
        {
            auto iter = I_Packet_Pool.Get().begin();

            Packet packet = I_Packet_Pool.Pop();
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
                if (New_Account(packet))
                {
                    I_SENDER.Single_Packet_Make(target_iter->second, PACKET_NEW_ACCOUNT_ACK);
                }
            }break;
            case PACKET_LOGIN_RQ://2005
            {


               // if (Login_Successs)//g_dwPhase == WAITING_READY
               // {
               //     User_Info new_user_info;
               //     //new_user_info.UID = target_iter->second->UID; DB���� �޾ƿ;���
               //     wcstombs(new_user_info.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
               //     I_SENDER.Broadcast_Packet_Make(PACKET_JOIN_NEW_USER, (char*)&new_user_info, MSG_USER_INFO_SIZE); //���� ���� ���� �˸�
               //     flag = 1;   //1 ���� 
               //     I_SENDER.Single_Packet_Make(target_iter->second, PACKET_LOGIN_ACK, &flag, 1); //�α��� �¶�
               //     for (auto players : I_PLAYER_MGR.Player_map)//���� ���� �÷��̾� ���� �۽�
               //     {
               //         User_Info user_infos;
               //         user_infos.UID = players.second->UID;
               //         wcstombs(user_infos.name, players.second->Name.c_str(), MAX_NAME_SIZE * 2);
               //         I_SENDER.Single_Packet_Make(target_iter->second, PACKET_UPDATE, (char*)&user_infos, MSG_USER_INFO_SIZE);
               //     }
               //     I_SENDER.Single_Packet_Make(target_iter->second, PACKET_UPDATE_END); //������Ʈ �� �˸� ��Ŷ
               //     FSM.FSM_Action(g_dwPhase);
               //
               // }
               // else
               // {
               //     flag = 0; //�α��� ����
               //     I_SENDER.Single_Packet_Make(target_iter->second, PACKET_LOGIN_ACK, &flag, 1); //�α��� �ź�
               // }
            case PACKET_USER_EXIT:
            {

                User_Info exit_user;
                wcstombs(exit_user.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                exit_user.UID = target_iter->second->UID;
                I_SENDER.Broadcast_Packet_Make(PACKET_USER_EXIT, (char*)&exit_user, MSG_USER_INFO_SIZE);
                closesocket(target_iter->second->Sock);

                I_PLAYER_MGR.Del_User(packet);
                if (g_dwPhase == WAITING_READY || g_dwPhase == PLAYER_TURN)
                {
                    FSM.FSM_Action(g_dwPhase);
                }
            }

            }break;
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�� ���� ���
            if (g_dwPhase == WAITING_READY)
            {
            case PACKET_GAME_READY://3001
            {
                if (target_iter->second->m_bBe_Ready == false)
                {
                    //��� ���� ready Ȯ��
                    target_iter->second->m_bBe_Ready = true;

                    User_Info ready_user;
                    ready_user.UID = target_iter->second->UID;
                    wcstombs(ready_user.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                    I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_READY, (char*)&ready_user, MSG_USER_INFO_SIZE);
                    FSM.FSM_Action(g_dwPhase);
                }
            }break;

            case PACKET_GAME_READY_CANCEL://3003
            {
                if (target_iter->second->m_bBe_Ready == true)
                {
                    target_iter->second->m_bBe_Ready = false;

                    User_Info cancel_user;
                    cancel_user.UID = target_iter->second->UID;
                    wcstombs(cancel_user.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                    I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_READY_CANCEL, (char*)&cancel_user, MSG_USER_INFO_SIZE);
                    FSM.FSM_Action(g_dwPhase);
                }
            }break;
            }
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////������� ������

            //Set_Up_Turn
            ///////////////////////////////////////////////////////////////////////
            //Player_Turn->
            if (g_dwPhase == PLAYER_TURN)
            {
            case PACKET_COMMAND_HIT://4001   
            {
                I_DEALER.Hit(target_iter->second);
                FSM.FSM_Action(g_dwPhase);
            }break;
            case PACKET_COMMAND_STAY://4002
            {
                User_Info stay_user;
                wcstombs(stay_user.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                stay_user.UID = target_iter->second->UID;

                I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_STAY, (char*)&stay_user, MSG_USER_INFO_SIZE);
                target_iter->second->m_bTurn_End_Flag = true;
                FSM.FSM_Action(g_dwPhase);
            }break;
            }

           

            default:
                break;
            }
           // �̸� ���� �߰� �� �ð� ������.
                I_SENDER.Send();
            I_Packet_Pool.Get().erase(iter);
            
        }//for_end
    }//while_end
    I_Wanna_Go_Home();
}
    
Server_Game::Server_Game()
{
   
}


Server_Game::~Server_Game()
{
}

