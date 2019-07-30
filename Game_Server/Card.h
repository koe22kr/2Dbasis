#pragma once
#include <stdexcept>
#include "Protocol.h"

enum Card_Num
{
   JACK=11,QUEEN=12,KING=13,ACE=1
};
enum Card_Type
{
    SPADE=1,CLOVER=2,HEART=3,DIAMOND=4, DUMMY=10
};
//  SPADE=1,CLOVER=2,HEART=3,DIAMOND=4
// 1 ACE 2345678910 JACK=11 QUEEN=12 KING=13



class Card
{
    char m_Card_type;
    char m_Card_num;
    char m_Card_Score;
    
public:
    bool Check() const;
   // int Get_Score() const;
    char Get_Type() const { return m_Card_type; };
    char Get_Num() const { return m_Card_num; };
    char Get_Score() const { return m_Card_Score; };
public:
    Card();
    Card(int type, int num, int score);
    ~Card();
};


struct User_Card_Info  //15
{
    WORD UID;        //2
    char name[MAX_NAME_SIZE];  //10
    Card hit_cards;             //3
};
