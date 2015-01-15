#pragma once

#include "request.h"
#include "lock.h"
#include "view.h"

// Comparator for TDATA (ascending order).
bool CompareTDATA(const TDATA &lhs, const TDATA &rhs);

//
// Thread-safe wrapper on the std::priority_queue for hold TDATA requests
//
class PriorityQueue
{
public:
    
    PriorityQueue(View &view)
        : m_queue(&CompareTDATA), 
        m_view(view)
    {
    }

    // Add request to queue.
    void Add(const TDATA &request)
    {
        Lock l(m_mutex);
        m_queue.push(request);
        m_view.ShowRequest(request, m_queue.size());
    }

    // Get request from queue.
    // Return false if queue empty and true otherwise.
    bool Get(TDATA &request)
    {
        Lock l(m_mutex);
        if (m_queue.empty())
        {
            return false;
        }
        request = m_queue.top();
        m_queue.pop();
        m_view.ShowLog(request, m_queue.size());
        return true;
    }

private:
    View &m_view;
    std::mutex m_mutex;

    // Queue in ascending order of request's priority.
    std::priority_queue<TDATA, std::vector<TDATA>, decltype(&CompareTDATA)> m_queue;
};
