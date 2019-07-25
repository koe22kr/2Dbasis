#include "Server_Game.h"
#include "ODBC_Query.h"
#include <ctime>
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
            //case PACKET_ACCESS_RQ://2001            //���� on ���� Ȯ��?
            //{//
            //    //Ŭ�� ���� -> ��Ƽ �����Ͽ� ���� ��û
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
                I_SENDER.Broadcast_Packet_Make(PACKET_JOIN_NEW_USER, (char*)&new_user_info, MSG_USER_INFO_SIZE); //���� ���� ���� �˸�
                flag = 1;   //1 ���� 
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_LOGIN_ACK, &flag, 1); //�α��� �¶�
                for (auto players : I_PLAYER_MGR.Player_map)//���� ���� �÷��̾� ���� �۽�
                {
                    User_Info user_infos;
                    user_infos.UID = players.second->UID;
                    wcstombs(user_infos.name, players.second->Name.c_str(), MAX_NAME_SIZE * 2);
                    I_SENDER.Single_Packet_Make(target_iter->second, PACKET_UPDATE, (char*)&user_infos, MSG_USER_INFO_SIZE);
                }
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_UPDATE_END); //������Ʈ �� �˸� ��Ŷ
            }
            else
            {
                flag = 0; //�α��� ����
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_LOGIN_ACK, &flag, 1); //�α��� �ź�
            }

        }break;
        case PACKET_GAME_READY://3001
        {
            if (target_iter->second->m_bBe_Ready == false)
            {
                //��� ���� ready Ȯ��
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
        case PACKET_COMMAND_HIT://4001    //m_dwPhase�� Player_Turn �ʿ�.
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
                    I_SENDER.Broadcast_Packet_Make(PACKET_BURST_OR_BLACK_JACK, &flag, 1); //����
                    target_iter->second->m_bTurn_End_Flag = true;
                }
                else if (21 < target_iter->second->m_iScore)
                {
                    flag = 0;
                    I_SENDER.Broadcast_Packet_Make(PACKET_BURST_OR_BLACK_JACK, &flag, 1); //����Ʈ
                    target_iter->second->m_bTurn_End_Flag = true;
                }
                else
                {
                    I_SENDER.Broadcast_Packet_Make(PACKET_SOME_BODY_HIT, (char*)&user_card, MSG_USER_CARD_SIZE); //��Ʈ ����
                }
            }
            else
            {
                flag = HIT_FAIL;
                I_SENDER.Single_Packet_Make(target_iter->second, PACKET_ERROR_CODE, &flag, 1); //��Ʈ ����//����׿�? ���� ���� ����
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
        �̸� ���� �߰� �ϱ�
            I_SENDER.Send();


    }//for_end





    ///////////////////////Waitting_Ready//////////////////
    if (m_dwPhase == Waitting_Ready &&
        m_iReady_Count >= I_PLAYER_MGR.Player_map.size())//������ �غ������� ������ ��Ȳ Ȯ��, �� �����Ӵ� Ȯ��X
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
        if (now - Delta_Time > 5)//�ð� �� �� �Ŀ�.. Ÿ�̸�
        {
            I_SENDER.Broadcast_Packet_Make(PACKET_GAME_START);
            m_dwPhase = Set_Up_Turn;//Init ���� ī�� ���� �ϱ�.
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
            //�÷��̾� �� ����
        }
        else
        {
            //�÷��̾� �� �ؾ��Ұ�?


        }

    }
    /////////////////////////////////////////////////////
    /////////////////Dealer_Turn///////////////////////// ���� FSM �� ���� �־ �ɵ�.
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
        m_dwPhase = Re_Set; // ���� ���� 
        Delta_Time = now;
    }
    if (now - Delta_Time > 5)//�ð� �� �� �Ŀ�.. 
    {

        m_dwPhase = Waitting_Ready;// �̾.
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

