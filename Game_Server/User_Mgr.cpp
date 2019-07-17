#include "User_Mgr.h"

void User_Mgr::Add_User()
{



}
void User_Mgr::Del_User()
{



}

void User_Mgr::Dispatch()
{



}

void User_Mgr::Packet_Cutting(User target_user, char* pBuffer, DWORD dwByte)
{
    //char* pBuffer, DWORD dwByte
    //m_dwWritePos 다음 버퍼 위치
    //m_dwStartPos 패킷의 시작 위치
    //m_dwReadPos  받은 데이터 크기
    if (target_user.m_dwWrite_Pos + dwByte >= MAX_STREAM_SIZE)
    {
        char strTemp[] = { 0, };
        memcpy(target_user.m_szPackStream, 
               &target_user.m_szPackStream[target_user.m_dwWrite_Pos],
               MAX_STREAM_SIZE- target_user.m_dwWrite_Pos);

        //memcpy(strTemp, &m_szPackStream[m_dwStartPos], m_dwReadPos);
        //ZeroMemory(m_szPackStream, sizeof(char)*MAX_STREAM_SIZE);
        //memcpy(m_szPackStream, &strTemp, m_dwReadPos);
        target_user.m_dwStart_Pos = 0;
        target_user.m_dwWrite_Pos = target_user.m_dwByte_To_Read;
    }
    memcpy(&target_user.m_szPackStream[target_user.m_dwWrite_Pos], pBuffer, dwByte);
    target_user.m_dwWrite_Pos += dwByte;
    target_user.m_dwByte_To_Read += dwByte;

    if (target_user.m_dwByte_To_Read >= PACKET_HEADER_SIZE)
    {
        Packet* pPacket =
            (Packet*)&target_user.m_szPackStream[target_user.m_dwStart_Pos];
        // 받은 데이터 크기(1개의 패킷보다 크면)
        if (pPacket->ph.len <= target_user.m_dwByte_To_Read)
        {
            do {
                
                Packet newPacket;
                ZeroMemory(&newPacket, sizeof(newPacket));
                // UID 는 허가 패킷에서 MAP 의 키값UID 던져주고 그걸로 받아서 유저 맵에.
                memcpy(&newPacket, pPacket, pPacket->ph.len);
                //newPacket을 패킷 풀? 에 투입 하고  pos들 수정해주고..

                //memcpy(&tPacket.packet,
                //    &m_szPackStream[m_dwStartPos],
                //    pPacket->ph.len);
                I_PackPool.Push(tPacket);

                m_dwReadPos -= pPacket->ph.len;
                m_dwStartPos += pPacket->ph.len;

                if (m_dwReadPos < PACKET_HEADER_SIZE)
                {
                    break;
                }
                pPacket =
                    (UPACKET*)&m_szPackStream[m_dwStartPos];

            } while (pPacket->ph.len <= m_dwReadPos);
        }
    }
    
}

User_Mgr::User_Mgr()
{
}


User_Mgr::~User_Mgr()
{
}
