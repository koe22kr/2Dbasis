#pragma once
#include <random>
#include <list>
#include <exception>

//메세지 룰, 등 이곳에 서술 예정.
//  SPADE=1,CLOVER=2,HEART=3,DIAMOND=4
// 1 ACE 2345678910 JACK=11 QUEEN=12 KING=13
//
//Card {0,0} == 에러 드로우 실패
//