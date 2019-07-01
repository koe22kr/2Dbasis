#pragma once
#include "CAServerStd.h"
#pragma pack(push,1)
struct PacketHeader
{
    WORD len;
    WORD type;
};

struct PACKET
{
    PacketHeader ph;
    char msg[2048];
};
#define PACKET_MAX_DATA_SIZE 2048
#define PACKET_HEADER_SIZE 4


///////////////////////////////
#define PACKET_TYPE_CHAT 1000
#define PACKET_CHAR_NAME_REQ 1001;
#define PACKET_CHAR_NAME_ACK 1002;
//#define PACKET_TYPE_
//#define PACKET_TYPE_
//#define PACKET_TYPE_
//#define PACKET_TYPE_
//#define PACKET_TYPE_
//#define PACKET_TYPE_
#define PACKET_CHAR_MSG			 1000 // DATA
#define PACKET_CHAR_NAME_SC_REQ  1001 // DATA
#define PACKET_CHAR_NAME_CS_ACK  1002 // DATA
#define PACKET_JOIN_SIGNIN_SC	 1003 // x
#define PACKET_JOIN_USER_SC		 1004 // DATA
#define PACKET_DRUP_CS_REQ		 1005 // x
#define PACKET_DRUP_SC_ACK		 1006 // x
#define PACKET_DRUP_USERS_SC	 1007 // DATA

typedef struct {
    int   iIndex;
    char  szName[20];
}USER_BASE;

typedef struct {
    char  szName[20];
    char  msg[PACKET_MAX_DATA_SIZE - 20];// 메세지 실제 크기
}USER_CHAT_MSG;



#pragma pack(pop)