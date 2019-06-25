#pragma once
#include "CAServerStd.h"

struct PacketHeader 
{
    WORD len;
    WORD type;
};

struct PACKET
{
    PacketHeader ph;
    WORD msg[2044];
};

#define PACKET_HEADER_SIZE 4


///////////////////////////////
#define PACKET_TYPE_CHAT 1000
//#define PACKET_TYPE_
//#define PACKET_TYPE_
//#define PACKET_TYPE_
//#define PACKET_TYPE_
//#define PACKET_TYPE_
//#define PACKET_TYPE_