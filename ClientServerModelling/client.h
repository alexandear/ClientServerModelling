#pragma once

#include "stdafx.h"
#include "constants.h"
#include "request.h"
#include "lock.h"
#include "priorityqueue.h"

//
// Represent client. Send request to PriorityQueue.
// Each client run in separate "daemon" thread and has own ID.
//
class Client
{
public:
    Client(PriorityQueue &priorityQueue)
        : m_dwClientId(++m_id),
        m_thread(),
        m_priorityQueue(priorityQueue),
        //m_mutex(),
        m_engine(static_cast<DWORD>(std::time(nullptr)) + m_dwClientId),
        m_randomDelay(Constants::MIN_REQUEST, Constants::MAX_REQUEST),
        m_randomPriority(Constants::MIN_REQUEST_PRIORITY, Constants::MAX_REQUEST_PRIORITY)
    {
    }

    // Start client thread.
    void Start();

    DWORD GetId()
    {
        return m_dwClientId;
    }
     
private:
    DWORD m_dwClientId;
    static std::atomic<DWORD> m_id;

    PriorityQueue &m_priorityQueue;

    std::thread m_thread;
    //std::mutex m_mutex;
    // Random number engine.
    std::default_random_engine m_engine;
    // Random number generator for delay.
    std::uniform_int_distribution<DWORD> m_randomDelay;
    // Random number generator for priority.
    std::uniform_int_distribution<DWORD> m_randomPriority;

    // Send requests infinity times.
    void Run();
    // Send request to PriorityQueue.
    void SendRequest();

    // Generate request priority.
    BYTE GetPriority()
    {
        return static_cast<BYTE>(m_randomPriority(m_engine));
    }

    // Generate request data.
    const char* GetData() const
    {
        return "data";
    }
};
