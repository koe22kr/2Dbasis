#pragma once
#include "Server_std.h"


#define PACKET_MAX_DATA_SIZE 2048
#define PACKET_HEADER_SIZE 4
#define MAX_USER_BUFFER_SIZE PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE
#define MAX_STREAM_SIZE (MAX_USER_BUFFER_SIZE) * 10

#define PACK_RECV 101
#define PACK_SEND 102
#define PACK_END 103
#define PACK_ERROR 104

#define PACKET_NEW_ACCOUNT 2004                 // msg 에 이름 or 닉네임?
#define PACKET_JOIN_RQ 2001                     // msg 에 이름 or 닉네임 일치하는거 확인 해야하니 보내야.
#define PACKET_JOIN_ACK 2002                    // 채팅서버 포트 번호 보내줘야함 블랙잭의 맵의 int 값을 UID로 사용하여 보내주기.
#define PACKET_GAME_READY 3001                  // 해더의 UID 읽고, 데이터X
#define PACKET_GAME_START 3002                  // 데이터 X
#define PACKET_COMMAND_HIT 4001                 // 패킷 보내면   
#define PACKET_COMMAND_STAY 4002                //
#define PACKET_UPDATE 9000                      //
#define PACKET_EXIT 9999                        //

#define PACKET_CHAT_MSG 1001
#define PACKET_CHAT_JOIN_RQ 1002
#define PACKET_CHAT_JOIN_ACK 1003
#define PACKET_CHAT_EXIT 9999

#pragma pack(push,1)
////////////////////
//패킷 구조체 
struct PacketHeader //해더 사이즈는 6 .
{
    WORD len;
    WORD type;
    WORD UID;
};
struct Packet //패킷 사이즈는 2046 + 6 .
{
    PacketHeader ph;
    char msg[2046];
};














////////////////////
#pragma pack(pop)