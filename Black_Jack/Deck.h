#pragma once
#include "Card.h"
class Deck
{ 
    //  SPADE=1,CLOVER=2,HEART=3,DIAMOND=4
    // 1 ACE 2345678910 JACK=11 QUEEN=12 KING=13

    map<int, Card> Cards; //[51] ī�� �̸�, ��ȣ, ����?����. �� �Լ���, �Ź� ��� �� �ɹ����� ����.
    
    //map<int, Card> Spade[13];
    //map<int, Card> Clover[13];
    //map<int, Card> Heart[13];
    //map<int, Card> Daiamond[13];
public:
    void Reset();
    //void Shuffle();
    Card Draw(); //���� ī�� ��ο�!
    bool Check_Card(Card target);
    
    Deck();
   virtual ~Deck();
};
