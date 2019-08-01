#include "IOCP.h"
DWORD WINAPI Worker_Thread(LPVOID param)
{
    IOCP* pIOCP = (IOCP*)param;
    HANDLE hIOCP = pIOCP->m_hIOCP;
    
    BOOL bReturn;
    DWORD dwTransfer;
    ULONG_PTR uKeyValue;
    OVERLAPPED2* ov;

    while (1)
    {
        bReturn = ::GetQueuedCompletionStatus(hIOCP,
            &dwTransfer,
            &uKeyValue,
            (LPOVERLAPPED*)&ov, INFINITE);


        Player* pPlayer = (Player*)uKeyValue;
        if (ov != nullptr && ov->dw_Flag == PACK_END)
        {
            I_PLAYER_MGR.Del_User(pPlayer->UID);
            continue;
        }
        if (bReturn == TRUE && dwTransfer != 0)
        {
            if (I_PLAYER_MGR.Dispatch(pPlayer,dwTransfer, ov) == false)  // 분배 부분만 수정하기.
            {
                ov->dw_Flag = PACK_END;
                PostQueuedCompletionStatus(hIOCP, 0, uKeyValue, (LPOVERLAPPED)ov);
            }
        }
        else
        {
            ov->dw_Flag = PACK_END;
            PostQueuedCompletionStatus(hIOCP, 0, uKeyValue, (LPOVERLAPPED)ov);
        }
       
    }
    return 1;
}

void IOCP::SetSocketBind(SOCKET sock, ULONG_PTR key)
{
    ::CreateIoCompletionPort((HANDLE)sock,
        m_hIOCP,
        key,
        0);
}

bool IOCP::Init()
{
    m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

    DWORD threadID;
    for (int iThread = 0; iThread < MAX_IOCP_THREAD; iThread++)
    {
        m_hWorkThread[iThread] =
            ::CreateThread(0, 0, Worker_Thread,
                this,
                0, &threadID);
    }
    return true;
}
bool IOCP::Release()
{
    WaitForMultipleObjects(MAX_IOCP_THREAD, m_hWorkThread, TRUE, INFINITE);

    for (int iThread = 0;
        iThread < MAX_IOCP_THREAD;
        iThread++)
    {
        CloseHandle(m_hWorkThread[iThread]);
    }
    return true;
}

IOCP::IOCP()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
}


IOCP::~IOCP()
{
}
