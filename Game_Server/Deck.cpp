#include "Deck.h"

void Deck::Reset_Deck()
{
    unsigned int index = 0;
    for (unsigned char k = 1;k <= 4;k++) 
    {

        for (unsigned char i = 1;i <= 13;i++)
        {
            if (i == 1)
            {
                Cards[index] = Card({ k ,(unsigned char)(index + 1),11 });
            }
            else if (i > 1 && i < 11)
            {
                Cards[index] = Card({ k,(unsigned char)(index + 1),i }); // 맵의 [] 연산자가 이미 있으면 덮어쓰고, 없으면 추가하니 그냥사용
            }
            else if (i >= 11)
            {
                Cards[index] = Card({ k,(unsigned char)(index + 1),10 });
            }
            ++index;
        }
    }
  
}

bool Deck::Check_Card(Card target)
{
    return target.Check();
}

Card Deck::Draw()
{
    random_device rd;
    mt19937 random(rd());
    int ran;
    do
    {
        uniform_int_distribution<> rand_card(0, Cards.size() - 1);
        ran = rand_card(random);
    } while (Cards.find(ran) == Cards.end() && Cards.size() > 0);

    Card ret = Cards[ran];
    if (Cards.size() == 0)
    {
        throw out_of_range("Cards_size_zero_in_Draw");
        ret = { 0,0,0 };
    }
    else
    {
        Cards.erase(ran);
    }
    return ret;
    
}

Deck::Deck()
{
}


Deck::~Deck()
{
}
