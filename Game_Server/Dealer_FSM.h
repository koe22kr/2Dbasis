#pragma once
#include "Status.h"
#include "Server_std.h"
#include "Dealer.h"

//Waitting_Ready = 101,
//All_Player_Ready = 102,
//Set_Up_Turn = 103,
//Player_Turn = 104,
//Dealer_Turn = 105,
//ALL_Turn_Over = 106,


class Waiting_Ready :public Status
{
public:
   bool Action();
   bool User_Ready_Check();
   void Set_Up();
   Waiting_Ready();
   ~Waiting_Ready();


};

class Player_Turn :public Status
{
    int m_iTurn_End_Count;
    
public:
    bool Action();
    Player_Turn();
    ~Player_Turn();

private:

};
class Dealer_Turn :public Status
{
public:
    bool Action();
    void Judgement();
    void Reset();
    Dealer_Turn();
    ~Dealer_Turn();

private:

};
//
//class ALL_Turn_Over :public Status
//{
//public:
//   bool Action();
//   bool Reset();
//   ALL_Turn_Over();
//   ~ALL_Turn_Over();
//
//private:
//
//};
//


class Dealer_FSM
{
public:
    map<int,Status*> Status_list;
    Status* pFSM;
    void FSM_Action(int status_num);
    Dealer_FSM();
    virtual ~Dealer_FSM();
};

