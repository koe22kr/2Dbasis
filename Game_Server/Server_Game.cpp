#include "Server_Game.h"
#include "ODBC_Query.h"
#include "Card.h"//
bool g_start_flag = 0;
void Server_Game::Init()
{
    CreateThread();
    I_ACCEPTOR.Init();
    I_ACCEPTOR.CreateThread();
    I_IOCP.Init();//�߰� Ȯ�� ���.
    I_IOCP.CreateThread();
    ODBC.Init();
    g_dwPhase = WAITING_READY;

}

void Server_Game::I_Wanna_Go_Home()
{
    I_IOCP.Release();
    //Release �迭 �ϱ�.
}

bool Server_Game::New_Account(Packet packet)
{
    
    if (ODBC.New(packet.msg) == 0)
    

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

            Packet2 packet = I_Packet_Pool.Pop();
            auto target_iter = I_PLAYER_MGR.Player_map.find(packet.ph.UID);//

            switch (packet.ph.type)
            {
                //case PACKET_ACCESS_RQ://2001            //���� on ���� Ȯ��?
                //{//
                //    //Ŭ�� ���� -> ��Ƽ �����Ͽ� ���� ��û
                //    //PACKET_ACCESS_ACK 2002 
                //}break;
                case PACKET_NEW_ACCOUNT_RQ://2003
                {
                    int uid = ODBC.New(packet.msg);
                    if (uid != 0)//�̹� ������ 0����
                    {
                            I_SENDER.Single_Packet_Make(packet.pPlayer, PACKET_NEW_ACCOUNT_ACK);
                    }
                }break;
                case PACKET_LOGIN_RQ://2005
                {
                    if (g_dwPhase == WAITING_READY|| ALL_PLAYER_READY)
                    {
                        User_Info new_user_info = ODBC.Login(packet.msg);
                        if (new_user_info.UID != 0 && I_PLAYER_MGR.Player_map.size() <= 5)//g_dwPhase == WAITING_READY
                        {

                            TCHAR name[10];
                            mbstowcs(name, new_user_info.name, sizeof(new_user_info.name));
                            if (I_PLAYER_MGR.Add_User(packet, name, new_user_info.UID))
                            {
                                I_SENDER.Broadcast_Packet_Make(PACKET_JOIN_NEW_USER, (char*)&new_user_info, MSG_USER_INFO_SIZE); //���� ���� ���� �˸�


                                flag = 1;   //1 ���� 
                                I_SENDER.Single_Packet_Make(packet.pPlayer, PACKET_LOGIN_ACK, &flag, 1); //�α��� �¶�

                                if (I_PLAYER_MGR.Player_map.size() != 0)
                                {
                                    for (auto players : I_PLAYER_MGR.Player_map)//���� ���� �÷��̾� ���� �۽�
                                    {
                                        User_Info user_infos;
                                        user_infos.UID = players.second->UID;
                                        wcstombs(user_infos.name, players.second->Name.c_str(), MAX_NAME_SIZE * 2);
                                        I_SENDER.Single_Packet_Make(packet.pPlayer, PACKET_UPDATE, (char*)&user_infos, MSG_USER_INFO_SIZE);
                                    }
                                    I_SENDER.Single_Packet_Make(packet.pPlayer, PACKET_UPDATE_END); //������Ʈ �� �˸� ��Ŷ
                                    FSM.FSM_Action(g_dwPhase);//----------------------------------------
                                }
                            }
                        }
                        else
                        {
                            flag = 0; //�α��� ����
                            I_SENDER.Single_Packet_Make(packet.pPlayer, PACKET_LOGIN_ACK, &flag, 1); //�α��� �ź�
                        }
                    }
               
                }break;
               
                if (I_PLAYER_MGR.Player_map.size() != 0)
                {
                    case PACKET_CHAT_MSG:
                    {
                        I_SENDER.Broadcast_Packet_Make(PACKET_CHAT_MSG, (char*)&packet, strlen(packet.msg)+PACKET_HEADER_SIZE);
                        
                    }break;
                    case PACKET_USER_EXIT://
                    {

                        User_Info exit_user;
                        wcstombs(exit_user.name, target_iter->second->Name.c_str(), MAX_NAME_SIZE * 2);
                        exit_user.UID = target_iter->second->UID;
                        I_SENDER.Broadcast_Packet_Make(PACKET_USER_EXIT, (char*)&exit_user, MSG_USER_INFO_SIZE);
                        closesocket(target_iter->second->Sock);

                        I_PLAYER_MGR.Del_User(packet);
                        if (g_dwPhase == WAITING_READY || g_dwPhase == PLAYER_TURN|| ALL_PLAYER_READY)
                        {
                            FSM.FSM_Action(g_dwPhase);
                        }

                    }break;
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////�� ���� ���
                    if (g_dwPhase == WAITING_READY||ALL_PLAYER_READY)
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
                }

            }//switch_end
           // �̸� ���� �߰� �� �ð� ������.
           
            
           // I_Packet_Pool.Get().erase(iter);
            
        }//��Ŷ��ȸ end

            FSM.FSM_Action(g_dwPhase);
        I_SENDER.Send();
        if (g_start_flag == true && I_PLAYER_MGR.Player_map.size() == 0)
        {
            Reset();
            g_start_flag = false;
            g_dwPhase = WAITING_READY;

        }
    }//while_end
    I_Wanna_Go_Home();
    return;
}

void Server_Game::Reset()
{
    I_DEALER.Reset_Deck();
    I_DEALER.Reset_score();
    for (auto piter : I_PLAYER_MGR.Player_map)
    {
        piter.second->Reset_Score();
    }
}
Server_Game::Server_Game()
{
   
}


Server_Game::~Server_Game()
{
}

