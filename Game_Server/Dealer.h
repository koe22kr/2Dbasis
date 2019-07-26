#pragma once
#include "Deck.h"
#include "Dealer_FSM.h"
#include "Player_Mgr.h"
#include "Sender.h"
enum Game_Phase
{
    Waitting_Ready = 101,
    All_Player_Ready = 102,
    Set_Up_Turn = 103,
    Player_Turn = 104,
    Dealer_Turn = 105,
    ALL_Turn_Over = 106,
    Re_Set = 107
};

class Dealer :public Deck
{
public:
    Dealer_FSM FSM;

public:
    int m_iScore;
    int m_iAce_Counter;
    
    DWORD m_dwPhase;
    
    time_t Ready_Timer;
    time_t Delta_Time;

    bool Waiting_Ready();
    bool Players_Turn_Check();
    bool User_Ready_Check();


public:
    bool Hit_Card(Card hit_card);//get_score도 내부에서 함
    bool Hit_Dummy_card();//250/250/0
    void Set_Score();
    
    vector<Card> Card_List;

    Dealer();
    virtual ~Dealer();
};

