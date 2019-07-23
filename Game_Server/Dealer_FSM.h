#pragma once
#include "Status.h"
#include "Server_std.h"
//Waitting_Ready   = 1,
//Dealer_Turn = 2,
//Player_Turn = 3,
//Last_Dealer_Turn = 4


class Waitting_Ready :public Status
{
public:
    bool Action_Selector();
    Waitting_Ready();
    ~Waitting_Ready();

private:

};

class Dealer_Turn :public Status
{
public:
    bool Action_Selector();
    Dealer_Turn();
    ~Dealer_Turn();

private:

};

class Player_Turn : public Status
{
public:
    bool Action_Selector();
    Player_Turn();
    ~Player_Turn();

private:

};

class Last_Dealer_Turn : public Status
{
public:
    bool Action_Selector();
    Last_Dealer_Turn();
    ~Last_Dealer_Turn();

private:

};

class Dealer_FSM
{
public:
    vector<Status*> Status_list;
    Status* pFSM;
    Dealer_FSM();
    virtual ~Dealer_FSM();
};

