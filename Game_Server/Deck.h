#pragma once
#include "Card.h"
#include "Server_std.h"
using namespace std;

class Deck
{ 
    

    map<int, Card> Cards; //[51] 카드 이름, 번호, 점수?숫자. 는 함수로, 매번 계산 후 맴버변수 저장.
    
    //map<int, Card> Spade[13];
    //map<int, Card> Clover[13];
    //map<int, Card> Heart[13];
    //map<int, Card> Daiamond[13];
public:
    void Reset_Deck();
    //void Shuffle();
    Card Draw(); //랜덤 카드 드로우!
    bool Check_Card(Card target);
    
    Deck();
   virtual ~Deck();
};
