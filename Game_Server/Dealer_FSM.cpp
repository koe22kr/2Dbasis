#include "Dealer_FSM.h"

Waitting_Ready::Waitting_Ready()
{
}

Waitting_Ready::~Waitting_Ready()
{
}


bool Waitting_Ready::Action()
{


}
//////////////////////////////

Dealer_Turn::Dealer_Turn()
{

}

Dealer_Turn::~Dealer_Turn()
{

}

bool Dealer_Turn::Action()
{

}
/////////////////////////////

Player_Turn::Player_Turn()
{
}

Player_Turn::~Player_Turn()
{
}


bool Player_Turn::Action()
{

}
////////////////////////////

Last_Dealer_Turn::Last_Dealer_Turn()
{
}

Last_Dealer_Turn::~Last_Dealer_Turn()
{
}

bool Last_Dealer_Turn::Action()
{

}
////////////////////////////



Dealer_FSM::Dealer_FSM()
{
    auto wait = make_shared<Waitting_Ready>();
    auto dealer_turn = make_shared<Dealer_Turn>();
    auto player_turn = make_shared<Player_Turn>();
    auto last_dealer_turn = make_shared<Last_Dealer_Turn>();
    
    Status_list.push_back(wait.get());
    Status_list.push_back(dealer_turn.get());
    Status_list.push_back(player_turn.get());
    Status_list.push_back(last_dealer_turn.get());

}

void Dealer_FSM::Action_Select(int status_num)
{
    Status_list[status_num]->Action();
}

Dealer_FSM::~Dealer_FSM()
{
    Status_list.clear();
}
