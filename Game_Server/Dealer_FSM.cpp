#include "Dealer_FSM.h"

Waitting_Ready::Waitting_Ready()
{
}

Waitting_Ready::~Waitting_Ready()
{
}


bool Waitting_Ready::Action_Selector()
{


}
//////////////////////////////

Dealer_Turn::Dealer_Turn()
{

}

Dealer_Turn::~Dealer_Turn()
{

}

bool Dealer_Turn::Action_Selector()
{

}
/////////////////////////////

Player_Turn::Player_Turn()
{
}

Player_Turn::~Player_Turn()
{
}


bool Player_Turn::Action_Selector()
{

}
////////////////////////////

Last_Dealer_Turn::Last_Dealer_Turn()
{
}

Last_Dealer_Turn::~Last_Dealer_Turn()
{
}

bool Last_Dealer_Turn::Action_Selector()
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


Dealer_FSM::~Dealer_FSM()
{
    Status_list.clear();
}
