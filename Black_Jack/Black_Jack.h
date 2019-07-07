#pragma once
#include "CAStd.h"
#include "User.h"
#include "Card.h"
#include "Deck.h"


class Black_Jack
{
public:
    map<int,User> Player;//플레이어 = > 이름, 소지 카드 정보
    Deck          m_Deck;
    UINT          Time;
public:

    Black_Jack();
    virtual ~Black_Jack();
    
    void Resetgame();
    void Hit();
    void Stay();
    //void Shuffle();
    void Judgement();


};

