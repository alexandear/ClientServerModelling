#pragma once

#include <mutex>

//
// RAII wrapper for locking and unlocking the mutex
//
class Lock {
public:
    Lock(std::mutex &mutex) : m_mutex(mutex)
    {
        m_mutex.lock();
    }
    ~Lock()
    {
        m_mutex.unlock();
    }

    Lock() = delete;
private:
    std::mutex &m_mutex;
};