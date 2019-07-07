#include "Deck.h"
void Deck::Reset()
{
    int index = 0;
    for (int k = 1;k <= 4;k++) 
    {

        for (int i = 1;i <= 13;i++)
        {
            
            Cards[index] = Card({ k,i }); // 맵의 [] 연산자가 이미 있으면 덮어쓰고, 없으면 추가하니 그냥사용
            ++index;
        }
    }
  
}

Card Deck::Draw()
{
    random_device rd;
    mt19937 random(rd());
    int ran;
    do
    {
        uniform_int_distribution<> rand_card(0, Cards.size()-1);
         ran = rand_card(random);
    } while (Cards.find(ran) == Cards.end() && Cards.size() > 0);
    if (Cards.size() == 0)
    {
        throw out_of_range("Cards_size_zero_in_Draw");
    }
    Card ret = Cards[ran];
    Cards.erase(ran);
    return ret;
    
}

Deck::Deck()
{
}


Deck::~Deck()
{
}
