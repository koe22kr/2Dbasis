#pragma once
#include "Card.h"
#include "Server_std.h"
using namespace std;

class Deck
{ 
    

    map<int, Card> Cards; //[51] ī�� �̸�, ��ȣ, ����?����. �� �Լ���, �Ź� ��� �� �ɹ����� ����.
    
    //map<int, Card> Spade[13];
    //map<int, Card> Clover[13];
    //map<int, Card> Heart[13];
    //map<int, Card> Daiamond[13];
public:
    void Reset_Deck();
    //void Shuffle();
    Card Draw(); //���� ī�� ��ο�!
    bool Check_Card(Card target);
    
    Deck();
   virtual ~Deck();
};
