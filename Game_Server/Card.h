#pragma once
#include <stdexcept>

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
    byte m_Card_type;
    byte m_Card_num;
    byte m_Card_Score;
    
public:
    bool Check() const;
    int Get_Score() const;
public:
    Card();
    Card(int type, int num, int score);
    virtual ~Card();
};

