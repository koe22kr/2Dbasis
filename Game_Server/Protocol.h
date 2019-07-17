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

#define PACKET_NEW_ACCOUNT 2004                 // msg �� �̸� or �г���?
#define PACKET_JOIN_RQ 2001                     // msg �� �̸� or �г��� ��ġ�ϴ°� Ȯ�� �ؾ��ϴ� ������.
#define PACKET_JOIN_ACK 2002                    // ä�ü��� ��Ʈ ��ȣ ��������� ������ ���� int ���� UID�� ����Ͽ� �����ֱ�.
#define PACKET_GAME_READY 3001                  // �ش��� UID �а�, ������X
#define PACKET_GAME_START 3002                  // ������ X
#define PACKET_COMMAND_HIT 4001                 // ��Ŷ ������   
#define PACKET_COMMAND_STAY 4002                //
#define PACKET_UPDATE 9000                      //
#define PACKET_EXIT 9999                        //

#define PACKET_CHAT_MSG 1001
#define PACKET_CHAT_JOIN_RQ 1002
#define PACKET_CHAT_JOIN_ACK 1003
#define PACKET_CHAT_EXIT 9999

#pragma pack(push,1)
////////////////////
//��Ŷ ����ü 
struct PacketHeader //�ش� ������� 6 .
{
    WORD len;
    WORD type;
    WORD UID;
};
struct Packet //��Ŷ ������� 2046 + 6 .
{
    PacketHeader ph;
    char msg[2046];
};














////////////////////
#pragma pack(pop)