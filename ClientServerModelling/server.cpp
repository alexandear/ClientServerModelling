#include "stdafx.h"
#include "server.h"
#include "request.h"
#include "priorityqueue.h"

Server::Server(PriorityQueue &priorityQueue, const std::wstring &logFileName)
    : m_thread(),
    m_logFileName(logFileName),
    m_logFile(m_logFileName, std::ios::app),
    m_priorityQueue(priorityQueue),
    m_engine(static_cast<DWORD>(std::time(nullptr))),
    m_randomInt(Constants::MIN_SERVER_RESPONSE, Constants::MAX_SERVER_RESPONSE)
{
    if (!m_logFile.is_open())
    {
        throw std::bad_exception("Couldn't create or write log file");
    }
}

void Server::Start()
{
    m_thread = std::thread(&Server::Run, this);
    m_thread.detach();
}

void Server::Run()
{
    while (true)
    {
        ProcessRequest();
        std::this_thread::sleep_for(std::chrono::milliseconds(m_randomInt(m_engine)));
    }
}

void Server::ProcessRequest()
{
    TDATA tdRequest {};
    bool isRequestsInQueue = m_priorityQueue.Get(tdRequest);
    if (isRequestsInQueue)
    {
        m_logFile << L"LT: " << GetTickCount()
            << L"\tID: " << tdRequest.dwClientId
            << "\tPR: " << tdRequest.cPriority
            << "\tRT: " << tdRequest.dwTicks << std::endl;
    }
}
