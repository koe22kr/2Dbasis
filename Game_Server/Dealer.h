#pragma once
#include "Deck.h"
#include "Dealer_FSM.h"



class Dealer :public Deck
{
public:
    Dealer_FSM FSM;

public:
    int m_iScore;
    int m_iAce_Counter;
    bool Hit_Card(Card hit_card);//get_score도 내부에서 함
    void Set_Score();
    
    vector<Card> Card_List;

    Dealer();
    virtual ~Dealer();
};

