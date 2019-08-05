#pragma once
#include "Deck.h"
#include "Player_Mgr.h"
#include "Sender.h"
//FSM 연계.........................

enum Game_Phase
{
    WAITING_READY = 101,
    ALL_PLAYER_READY = 102,
    /*SET_UP_TURN = 103,*/
    PLAYER_TURN = 104,
    DEALER_TURN = 105,
    //ALL_TURN_OVER = 106,

};

class Dealer :public Deck , public Singleton<Dealer>
{
    friend Singleton<Dealer>;
public:
    int m_iScore;
    int m_iAce_Counter;
    vector<Card> Card_List;

    
    time_t Ready_Timer;
    time_t Delta_Time;
public:
    bool Wait_Sec(int sec);
    bool Waiting_Ready();
    bool Players_Turn_Check();
    void Hit(Player* pPlayer);
    void Reset_score();

public:
    bool Take_Card(Card hit_card);//get_score도 내부에서 함
    bool Hit_Dummy_card();//10/0/0
    bool Erase_Dummy_Card();
    void Set_Score();
    

    Dealer();
    virtual ~Dealer();
};

#define I_DEALER Dealer::GetInstance()