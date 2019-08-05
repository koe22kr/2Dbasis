#include "Black_Jack.h"

void Black_Jack::Init()
{
    
    I_BITMAPMGR.Load_Bitmap_Script(L"../../data/wp.txt");
    I_CHAT.Init();
    I_SoundMgr.Init();
    I_SoundMgr.Load("simon.mp3");
    I_SoundMgr.PlayBGM("simon.mp3");
}

bool Black_Jack::Frame()
{

    while(g_pConnecter->m_Packet_Pool.begin() != g_pConnecter->m_Packet_Pool.end())
    {
        
        //m_bTurn_End_Flag

        auto packet = g_pConnecter->m_Packet_Pool.begin();
        
        switch (packet->ph.type)
        {
       
        case PACKET_UPDATE:
        {
            User_Info user;
            TCHAR wname[20] = { 0 };
            size_t len;
            memcpy(&user, packet->msg, MSG_USER_INFO_SIZE);
            mbstowcs_s(&len,wname, user.name, strlen(user.name));
            
            
            m_Player_list[user.UID].Name = wname;
            m_Player_list[user.UID].UID = user.UID;
        }break;
        case PACKET_JOIN_NEW_USER:
        {
            
            User_Info user;
            TCHAR wname[20] = { 0 };
            memcpy(&user, packet->msg, MSG_USER_INFO_SIZE);
            mbstowcs(wname, user.name, strlen(user.name));
            m_Player_list[user.UID].Name = wname;
            m_Player_list[user.UID].UID = user.UID;
            I_CHAT.Notice(*packet,"님이 입장하였습니다.");
        }break;

        //case PACKET_UPDATE_END:
        //{
        //   // Scene->In_game;

        //}
        case PACKET_USER_EXIT:
        {
            User_Info user;
            memcpy(&user, packet->msg, MSG_USER_INFO_SIZE);
            m_Player_list.erase(user.UID);
            I_CHAT.Notice(*packet, "님이 퇴장하였습니다.");
        }break;
        case PACKET_CHAT_MSG:
        {
            Packet packet2;
            memcpy(&packet2, packet->msg, packet->ph.len);
                
            I_CHAT.Talk(packet2, m_Player_list[packet2.ph.UID].Name.c_str());
            /////////////////////////////////////////////////
        }break;
        case PACKET_SOME_BODY_READY:
        {
            User_Info user;
            memcpy(&user, packet->msg, MSG_USER_INFO_SIZE);
            //리소스 준비 마크 flag =1;
            I_CHAT.Notice(*packet, "님이 준비하였습니다.");
        }break;
        case PACKET_SOME_BODY_READY_CANCEL:
        {
            User_Info user;
            memcpy(&user, packet->msg, MSG_USER_INFO_SIZE);
            //리소스  준비마크 flag =0;
            I_CHAT.Notice(*packet, "님이 준비를 취소.");
        }break;
        case PACKET_ALL_PLAYER_READY:
        {
            I_CHAT.Notice("모든 유저 준비.");
            I_CHAT.Notice("5초후 시작합니다.");
       
        }break;
        case PACKET_GAME_START:
        {
            I_CHAT.Notice("-게임 시작-");
            SetWindowPos(I_CHAT.m_hReady_Cancel, NULL, 0, 0, 100, 100, SWP_HIDEWINDOW);
            SetWindowPos(I_CHAT.m_hReady, NULL, 0, 0, 100, 100, SWP_HIDEWINDOW);
            
            I_CHAT.Make_Hit_Stay();
           
           // Scene->Game_Start;
        }break;
        case PACKET_SOME_BODY_HIT://
        {
            User_Card_Info card_info;
            memcpy(&card_info, packet->msg, MSG_USER_CARD_SIZE);
            if (m_iUID == card_info.UID)
            {
                m_Player_list[card_info.UID].Take_Card(card_info.hit_card,true);//
                I_CHAT.Notice("-카드받음-");

            }
            else
            {
                m_Player_list[card_info.UID].Take_Card(card_info.hit_card, false);//

            }
            if (m_Player_list[m_iUID].m_bTurn_End_Flag)
            {
                //DWORD newstyle = WS_CHILD | WS_DISABLED;
                //SetWindowLongPtr(I_CHAT.m_hHit, GWL_STYLE, newstyle);
                //SetWindowLongPtr(I_CHAT.m_hStay, GWL_STYLE, newstyle);
                SetWindowPos(I_CHAT.m_hHit, NULL, g_rtClient.left + 300, g_rtClient.top + 200, 100, 100, SWP_HIDEWINDOW);
                SetWindowPos(I_CHAT.m_hStay, NULL, g_rtClient.left + 400, g_rtClient.top + 200, 100, 100, SWP_HIDEWINDOW);

            }
        }break;
        case PACKET_SOME_BODY_STAY://
        {
            User_Info user;
            memcpy(&user, packet->msg, MSG_USER_INFO_SIZE);
            m_Player_list[user.UID].m_bTurn_End_Flag = true;
           
            string msg;
            msg = user.name;
            msg += " 이(가) 스테이!";
            I_CHAT.Notice(msg.c_str());
        }break;
        case PACKET_DEALER_HIT:
        {
            Card card;
            memcpy(&card, packet->msg, 3);
            Dealer.Take_Card(card,1, { 100,0 });
            wstring msg;
            msg = L"딜러 드로우 [ ";
            msg += I_PLAYER.m_Key_Map[card.Get_Num()];
            msg += L" ]";
            I_CHAT.Notice(msg.c_str());
        }break;
        case PACKET_GAME_LOSE:
        {
            User_Info uif;
            memcpy(&uif, packet->msg, MSG_USER_INFO_SIZE);
            if (uif.UID == m_iUID)
            {


                wstring msg;
                //msg = m_Player_list[m_iUID].m_iScore;
                msg = L" 패배";
                MessageBox(g_hWnd, msg.c_str(), L"패 배", MB_OK);

                I_CHAT.Reset_Windows();
                for (auto& player : m_Player_list)
                {
                    Dealer.Reset_Score();
                    player.second.Reset_Score();
                    player.second.Card_obj_list.clear();

                }
            }
        }break;
        case PACKET_GAME_WIN:
        {
            User_Info uif;
            memcpy(&uif, packet->msg, MSG_USER_INFO_SIZE);
            if (uif.UID == m_iUID)
            {

                wstring msg;
                // msg = m_Player_list[m_iUID].m_iScore;
                msg = L" 승리";
                MessageBox(g_hWnd, msg.c_str(), L"승 리", MB_OK);
                I_CHAT.Reset_Windows();

                for (auto& player : m_Player_list)
                {
                    Dealer.Reset_Score();
                    player.second.Reset_Score();
                    player.second.Card_obj_list.clear();
                }
            }//RESET()}
        }break;
        case PACKET_ERROR_CODE:
        {
           // ERROR;
        }break;
        default:
            break;
        }
        g_pConnecter->m_Packet_Pool.erase(packet);
    }//for_end
    g_pConnecter->m_Packet_Pool.clear();
    I_CHAT.Frame();
    I_BITMAPMGR.Frame();
    I_SoundMgr.Frame();

    return true;
}

void Black_Jack::Render()
{
    I_BITMAPMGR.Render();

    //for (auto iter : m_Player_list)
    //{
    //    iter.second.Render();
    //}
}

void Black_Jack::Release()
{
    I_BITMAPMGR.Release();
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
