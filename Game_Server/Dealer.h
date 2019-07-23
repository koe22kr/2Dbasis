#pragma once
#include "Deck.h"
#include "Dealer_FSM.h"



class Dealer :public Deck
{
public:
    Dealer_FSM FSM;
  
    Dealer();
    virtual ~Dealer();
};

