#include "Black_Jack.h"

void Black_Jack::Init()
{
    m_BitmapMgr.Load_Bitmap_Script(L"../../data/wp.txt");
}

void Black_Jack::Frame()
{
    
    for(Packet packet : g_pConnecter->m_Packet_Pool)
    {
        switch (packet.ph.type)
        {
       
        case PACKET_UPDATE:
        {
            User_Info user;
            TCHAR wname;
            mbstowcs(&wname, user.name, MSG_USER_NAME_SIZE);
            memcpy(&user, packet.msg, MSG_USER_INFO_SIZE);
            
            
            m_Player_list[user.UID].Name = wname;
            m_Player_list[user.UID].UID = user.UID;
        }
        //case PACKET_UPDATE_END:
        //{
        //   // Scene->In_game;

        //}
        case PACKET_USER_EXIT:
        {
            User_Info user;
            memcpy(&user, packet.msg, MSG_USER_INFO_SIZE);
            m_Player_list.erase(user.UID);
          //  CHAR_NOTICE(user.name, "~���� �����Ͽ����ϴ�.");
        }

        case PACKET_SOME_BODY_READY:
        {
            User_Info user;
            memcpy(&user, packet.msg, MSG_USER_INFO_SIZE);
            //���ҽ� �غ� ��ũ flag =1;
           // CHAR_NOTICE(user.name, "���� �غ��Ͽ����ϴ�.");
        }
        case PACKET_SOME_BODY_READY_CANCEL:
        {
            User_Info user;
            memcpy(&user, packet.msg, MSG_USER_INFO_SIZE);
            //���ҽ�  �غ�ũ flag =0;
           // CHAR_NOTICE(user.name, "���� �غ� ����Ͽ����ϴ�.");
        }
        case PACKET_ALL_PLAYER_READY:
        {
          //  CHAR_NOTICE("��� ���� �غ�");
            //���ҽ� 5���� �����մϴ�.
        }
        case PACKET_GAME_START:
        {
           // CHAR_NOTICE("���� ����");
           // Scene->Game_Start;
            //���� ���� NOTICE.
        }
        case PACKET_SOME_BODY_HIT://
        {
            User_Card_Info card_info;
            memcpy(&card_info, packet.msg, MSG_USER_CARD_SIZE);
            m_Player_list[card_info.UID].Take_Card(card_info.hit_card);//
            //Take_Card���� ī�� ��Ʈ�� ������Ʈ �������ؾ�.. + ����Ʈ, ���� ���� �ؾ���
        }
        case PACKET_SOME_BODY_STAY://
        {

            User_Info user;
            memcpy(&user, packet.msg, MSG_USER_INFO_SIZE);
            m_Player_list[user.UID].m_bTurn_End_Flag = true;
            //������ ���ҽ�
        }
        //case PACKET_BURST_OR_BLACK_JACK:  Ŭ�󿡼� ����ϱ�!
        //{
        //
        //}
        case PACKET_GAME_LOSE:
        {
          //  MSGBOX("�� �� ��")
        }
        case PACKET_GAME_WIN:
        {
          //  MessageBox()
           // MSGBOX("�� �� ")
        }
        case PACKET_ERROR_CODE:
        {
           // ERROR;
        }
        default:
            break;
        }
    }//for_end
    g_pConnecter->m_Packet_Pool.clear();
    
    m_BitmapMgr.Frame();
}

void Black_Jack::Render()
{
    m_BitmapMgr.Render();
}

void Black_Jack::Release()
{

}

//void Black_Jack::Judgement()
//{
//    // ������ ���� = ����ȭ�� ��Ű��.�� ����? �� �����ҵ�.
//}
//
//void Black_Jack::Command()
//{
//    
//}
//
//void Black_Jack::Hit()      
//{
//    Card hit_card = m_Deck.Draw();
//    if (hit_card.Check())
//    {
//        //hit ���� draw
//    }
//    //hit ���� draw
//}
//void Black_Jack::Stay()
//{
//
//}
//void Black_Jack::Burst()
//{
//
//}
//
//
//
//void Black_Jack::Ranking()
//{
//
//}

Black_Jack::Black_Jack()
{
    g_pConnecter = &I_CONNECTER;

}


Black_Jack::~Black_Jack()
{
}
