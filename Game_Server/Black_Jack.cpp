#include "Black_Jack.h"

void Black_Jack::Judgement()
{
    // 판정만 내기 = 점수화만 시키자.는 유저? 로 가야할듯.
}

void Black_Jack::Command()
{
    
}

void Black_Jack::Hit()      
{
    Card hit_card = m_Deck.Draw();
    if (hit_card.Check())
    {
        //hit 성공 draw
    }
    //hit 실패 draw
}
void Black_Jack::Stay()
{

}
void Black_Jack::Burst()
{

}



void Black_Jack::Ranking()
{

}

Black_Jack::Black_Jack()
{
}


Black_Jack::~Black_Jack()
{
}
