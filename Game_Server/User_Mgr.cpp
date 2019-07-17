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
    //m_dwWritePos ���� ���� ��ġ
    //m_dwStartPos ��Ŷ�� ���� ��ġ
    //m_dwReadPos  ���� ������ ũ��
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
        // ���� ������ ũ��(1���� ��Ŷ���� ũ��)
        if (pPacket->ph.len <= target_user.m_dwByte_To_Read)
        {
            do {
                
                Packet newPacket;
                ZeroMemory(&newPacket, sizeof(newPacket));
                // UID �� �㰡 ��Ŷ���� MAP �� Ű��UID �����ְ� �װɷ� �޾Ƽ� ���� �ʿ�.
                memcpy(&newPacket, pPacket, pPacket->ph.len);
                //newPacket�� ��Ŷ Ǯ? �� ���� �ϰ�  pos�� �������ְ�..

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
