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
          //  CHAR_NOTICE(user.name, "~님이 퇴장하였습니다.");
        }

        case PACKET_SOME_BODY_READY:
        {
            User_Info user;
            memcpy(&user, packet.msg, MSG_USER_INFO_SIZE);
            //리소스 준비 마크 flag =1;
           // CHAR_NOTICE(user.name, "님이 준비하였습니다.");
        }
        case PACKET_SOME_BODY_READY_CANCEL:
        {
            User_Info user;
            memcpy(&user, packet.msg, MSG_USER_INFO_SIZE);
            //리소스  준비마크 flag =0;
           // CHAR_NOTICE(user.name, "님이 준비를 취소하였습니다.");
        }
        case PACKET_ALL_PLAYER_READY:
        {
          //  CHAR_NOTICE("모든 유저 준비");
            //리소스 5초후 시작합니다.
        }
        case PACKET_GAME_START:
        {
           // CHAR_NOTICE("게임 시작");
           // Scene->Game_Start;
            //게임 시작 NOTICE.
        }
        case PACKET_SOME_BODY_HIT://
        {
            User_Card_Info card_info;
            memcpy(&card_info, packet.msg, MSG_USER_CARD_SIZE);
            m_Player_list[card_info.UID].Take_Card(card_info.hit_card);//
            //Take_Card에서 카드 비트맵 오브젝트 랜더링해야.. + 버스트, 블랙잭 연산 해야함
        }
        case PACKET_SOME_BODY_STAY://
        {

            User_Info user;
            memcpy(&user, packet.msg, MSG_USER_INFO_SIZE);
            m_Player_list[user.UID].m_bTurn_End_Flag = true;
            //스테이 리소스
        }
        //case PACKET_BURST_OR_BLACK_JACK:  클라에서 계산하기!
        //{
        //
        //}
        case PACKET_GAME_LOSE:
        {
          //  MSGBOX("ㅍ ㅐ 배")
        }
        case PACKET_GAME_WIN:
        {
          //  MessageBox()
           // MSGBOX("승 리 ")
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
//    // 판정만 내기 = 점수화만 시키자.는 유저? 로 가야할듯.
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
//        //hit 성공 draw
//    }
//    //hit 실패 draw
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
