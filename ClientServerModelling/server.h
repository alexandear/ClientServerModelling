#pragma once

#include "constants.h"
#include "priorityqueue.h"

//
// Represent server. Get request from PriorityQueue and write information about to log file.
// Run in separate "daemon" thread.
//
// Information in logging file:
// LT - log time in system ticks
// ID - client identificator
// PR - priority of request (0-255)
// RT - time of creation request in system ticks
//
class Server
{
public:
    // If constructor cann't create log file it exits program.
    Server(PriorityQueue &priorityQueue,
        const std::wstring &logFileName = Constants::DEFAULT_LOG_FILE_NAME);

    // Start server in new thread.
    void Start();

    std::wstring GetLogFileName()
    {
        return m_logFileName;
    }
    
    void SetLogFileName(const std::wstring &logFileName)
    {
        m_logFileName = logFileName;
    }

    Server& operator=(const Server &) = delete;
private:
    std::thread m_thread;
    std::wstring m_logFileName;
    std::wofstream m_logFile;

    PriorityQueue &m_priorityQueue;

    // Random number engine.
    std::default_random_engine m_engine;
    // Random int generator for delay.
    std::uniform_int_distribution<DWORD> m_randomInt;

    // Run ProcessRequest infinity times.
    void Run();
    // Get queue from PriorityQueue and log to file.
    void ProcessRequest();

};

