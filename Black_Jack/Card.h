#pragma once
#include "CAStd.h"
#include "Std.h"
enum Card_Num
{
   JACK=11,QUEEN=12,KING=13,ACE=1
};
enum Card_Type
{
    SPADE=1,CLOVER=2,HEART=3,DIAMOND=4
};
//  SPADE=1,CLOVER=2,HEART=3,DIAMOND=4
// 1 ACE 2345678910 JACK=11 QUEEN=12 KING=13
class Card
{
    int m_Card_type;
    int m_Card_num;

public:
    bool Check() const;

public:
    Card();
    Card(int type, int num);
    virtual ~Card();
};

