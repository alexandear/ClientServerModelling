#pragma once

#include "stdafx.h"
#include "client.h"
#include "server.h"
#include "priorityqueue.h"

//
// Modeling interaction between server and clients.
//
class Simulator
{
public:
    explicit Simulator(DWORD dwClients);

    // Start server and clients.
    void Start();

    DWORD GetClients()
    {
        return m_dw—lients;
    }

    void SetClient(DWORD dwClients)
    {
        m_dw—lients = dwClients;
    }

    Simulator& operator=(const Simulator &) = delete;
private:
    void Run();

    std::thread m_thread;

    DWORD m_dw—lients;
    View m_view;
    PriorityQueue m_priorityQueue;
    Server m_server;
    std::vector<std::auto_ptr<Client>> m_clients;
};
