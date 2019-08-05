#include "Player.h"
#include "Chat.h"
bool Player::Take_Card(Card hit_card, bool flag,POINT pos)//get_score도 내부에서 함
{
    int pos_step = 50;
    shared_ptr<CABitmapObject> card_obj = make_shared<CABitmapObject>();
    auto iter = m_Key_Map.find(hit_card.Get_Num());
    if (iter != m_Key_Map.end())
    {
        wstring temp = iter->second;

        /*auto iter2 = m_Rect_Map.find(temp);
        if (iter2 != m_Rect_Map.end())
        {
            RECT test = m_Rect_Map[temp];*/
            card_obj->Setobject(temp.c_str(),
                1,
                pos.x + (Card_List.size() * pos_step),
                pos.y,
                m_Rect_Map[temp]);

            card_obj->m_pbmp = Bitmap;
            Card_List.push_back(hit_card);
            Card_obj_list.push_back(*card_obj.get());
            
            if (flag)
            {
                I_BITMAPMGR.m_Obj_list.push_back(card_obj);
            }
            Set_Score();
            int a = 0;
            return true;
     /*   }
        
        return false;*/
    }
    //.c_str();
    return false;
   
}
void Player::Set()
{
   
}

bool Player::Render()
{
    for (auto iter : Card_obj_list)
    {
        iter.Draw(0);
    }
    return true;
}

void Player::Set_Score()
{
    if (UID == 0)
    {
        Name = L"딜러";
     }
    m_iScore = 0;
    m_iAce_Counter = 0;
    for (Card cards : Card_List)
    {
        if (cards.Get_Score() == 11)
        {
            m_iAce_Counter++;
        }
        m_iScore += cards.Get_Score();
    }
    while (m_iAce_Counter > 0 && m_iScore > 21)
    {
        m_iScore -= 10;
        m_iAce_Counter--;
    }

    if (m_iScore > 21)
    {
        wstring msg;
        msg = Name;
        msg += L" 이(가) 버스트!";
        I_CHAT.Notice(msg.c_str());
        m_bTurn_End_Flag = true;
    }
    else if (m_iScore == 21)
    {
        wstring msg;
        msg = Name;
        msg += L" 이(가) 블랙잭!";
        I_CHAT.Notice(msg.c_str());
        m_bTurn_End_Flag = true;
    }
}

void Player::Reset_Score()
{
    m_bTurn_End_Flag = false;
    m_bBe_Ready = false;
    m_iScore = 0;
    m_iAce_Counter = 0;
    Card_List.clear();
    Card_obj_list.clear();
    I_BITMAPMGR.m_Obj_list.clear();
    
    DWORD newstyle = WS_CHILD ;
    SetWindowLongPtr(I_CHAT.m_hHit, GWL_STYLE, newstyle);
    SetWindowLongPtr(I_CHAT.m_hStay, GWL_STYLE, newstyle);
    SetWindowPos(I_CHAT.m_hHit, NULL, g_rtClient.left + 300, g_rtClient.top + 200, 100, 100, SWP_HIDEWINDOW);
    SetWindowPos(I_CHAT.m_hStay, NULL, g_rtClient.left + 400, g_rtClient.top + 200, 100, 100, SWP_HIDEWINDOW);

    I_BITMAPMGR.Load_Bitmap_Script(L"../../data/wp.txt");

}

void Player::Rect_Map_Init()
{
    //  SPADE=1,CLOVER=2,HEART=3,DIAMOND=4
    // 1 ACE 2345678910 JACK=11 QUEEN=12 KING=13
    int NO = 0;
    wstring CN;
    RECT RT;
    ///////////////////////////////
   
    NO = 1;
    CN = L"S_A";
    RT = { 0,300,71,96 };
    auto ret = m_Rect_Map.insert(make_pair(CN, RT));
    if (!ret.second)
    {
        throw out_of_range("Rect_Map_Init, insert_fail");
    }
    auto ret2 = m_Key_Map.insert(make_pair(NO, CN));
    if (!ret.second)
    {
        throw out_of_range("Rect_Map_Init, insert_fail");
    }

    NO = 2;
    CN = L"S_2";
    RT = { 0, 400, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 3;
    CN = L"S_3";
    RT = { 0 ,500, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));    
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 4;
    CN = L"S_4";
    RT = { 0 ,600, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));       
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 5;
    CN = L"S_5";
    RT = { 0 ,700 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));       
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 6;
    CN = L"S_6";
    RT = { 0 ,800 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));       
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 7;
    CN = L"S_7";
    RT = { 0 ,900, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));       
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 8;
    CN = L"S_8";
    RT = { 0 ,1000 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));       
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 9;
    CN = L"S_9";
    RT = { 0 ,1100, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 10;
    CN = L"S_10";
    RT = { 0 ,1200, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 11;
    CN = L"S_J";
    RT = { 0 ,200, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));       
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 12;
    CN = L"S_Q";
    RT = { 0 ,100 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 13;
    CN = L"S_K";
    RT = { 0 ,0 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));



    NO = 14;
    CN = L"C_A";
    RT = { 75 ,300, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 15;
    CN = L"C_2";
    RT = { 75, 400, 71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 16;
    CN = L"C_3";
    RT = { 75, 500 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 17;
    CN = L"C_4";
    RT = { 75, 600, 71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 18;
    CN = L"C_5";
    RT = { 75, 700 ,71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 19;
    CN = L"C_6";
    RT = { 75, 800, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 20;
    CN = L"C_7";
    RT = { 75, 900, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 21;
    CN = L"C_8";
    RT = { 75, 1000, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 22;
    CN = L"C_9";
    RT = { 75 ,1100, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 23;
    CN = L"C_10";
    RT = { 75, 1200 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 24;
    CN = L"C_J";
    RT = { 75 ,200 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 25;
    CN = L"C_Q";
    RT = { 75 ,100, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 26;
    CN = L"C_K";
    RT = { 75, 0 ,71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));

    
    NO = 27;
    CN = L"H_A";
    RT = { 150 ,300 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));       
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 28;
    CN = L"H_2";
    RT = { 150, 400 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 29;
    CN = L"H_3";
    RT = { 150 ,500, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 30;
    CN = L"H_4";
    RT = { 150 ,600 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 31;
    CN = L"H_5";
    RT = { 150, 700, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 32;
    CN = L"H_6";
    RT = { 150 ,800 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 33;
    CN = L"H_7";
    RT = { 150, 900, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 34;
    CN = L"H_8";
    RT = { 150, 1000, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 35;
    CN = L"H_9";
    RT = { 150 ,1100 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 36;
    CN = L"H_10";
    RT = { 150, 1200, 71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 37;
    CN = L"H_J";
    RT = { 150 ,200 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 38;
    CN = L"H_Q";
    RT = { 150 ,100, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));   
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 39;
    CN = L"H_K";
    RT = { 150 ,0 ,71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));


    NO = 40;
    CN = L"D_A";
    RT = { 225, 300, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 41;
    CN = L"D_2";
    RT = { 225, 400, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 42;
    CN = L"D_3";
    RT = { 225 ,500 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 43;
    CN = L"D_4";
    RT = { 225 ,600 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 44;
    CN = L"D_5";
    RT = { 225, 700, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 45;
    CN = L"D_6";
    RT = { 225, 800, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 46;
    CN = L"D_7";
    RT = { 225 ,900 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 47;
    CN = L"D_8";
    RT = { 225, 1000 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 48;
    CN = L"D_9";
    RT = { 225 ,1100 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 49;
    CN = L"D_10";
    RT = { 225 ,1200, 71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 50;
    CN = L"D_J";
    RT = { 225 ,200 ,71 ,96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 51;
    CN = L"D_Q";
    RT = { 225, 100, 71, 96 };
    m_Rect_Map.insert(make_pair(CN, RT));
    m_Key_Map.insert(make_pair(NO, CN));
    NO = 52;
    CN = L"D_K";
    RT = { 225 ,0 ,71 ,96 };
    ret = m_Rect_Map.insert(make_pair(CN, RT));
    if (!ret.second)
    {
        throw out_of_range("Rect_Map_Init, insert_fail");
    }
    ret2 = m_Key_Map.insert(make_pair(NO, CN));
    if (!ret.second)
    {
        throw out_of_range("Rect_Map_Init, insert_fail");
    }

}


Player::Player()
{
    m_bTurn_End_Flag = false;
    m_bBe_Ready = false;
    m_iScore = 0;
    m_iAce_Counter = 0;
    Bitmap = Card_Bit_Mgr.Load_Bitmap(Card_Bitmap_File_Name);
    Rect_Map_Init();
}


Player::~Player()
{
}
