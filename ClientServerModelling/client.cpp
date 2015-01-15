#include "stdafx.h"
#include "client.h"
#include "priorityqueue.h"

std::atomic<DWORD> Client::m_id;

void Client::Start()
{
    m_thread = std::thread(&Client::Run, this);
    m_thread.detach();
}

void Client::Run()
{
    while (true)
    {
        SendRequest();
        DWORD dwMilliseconds = m_randomDelay(m_engine);
        std::this_thread::sleep_for(std::chrono::milliseconds(dwMilliseconds));
    }
}

void Client::SendRequest()
{
    TDATA tdRequest { };
    tdRequest.cPriority = GetPriority();
    tdRequest.dwClientId = m_dwClientId;
    tdRequest.dwTicks = GetTickCount();
    std::memcpy(tdRequest.data, GetData(), Constants::MAX_DATA_SIZE);

    m_priorityQueue.Add(tdRequest);
}
