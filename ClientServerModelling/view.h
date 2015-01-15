#pragma once
#include "constants.h"
#include "request.h"

//
// Class for work with console representation of modelling.
//
class View
{
public:
    View(DWORD clients);

    ~View()
    {
        SetConsoleCursorPosition(m_console, COORD{ 0, m_bottomY });
    }

    void ShowRequest(const TDATA &request, DWORD size);
    void ShowLog(const TDATA &request, DWORD size);

private:
    HANDLE m_console;
    DWORD m_clients;
    SHORT m_topY;
    SHORT m_topX;
    SHORT m_bottomY;

    void ShowSize(DWORD size);
    void Paint(const std::vector<std::wstring> &figure, const COORD &coord);
    void PaintServer();
    void PaintLog();
    void PaintQueue();
    void PaintClient(DWORD id, const COORD &coord);
    void PaintClients();
    void PaintConnects();
    void Write(const std::wstring &msg, const COORD &coord);

    SHORT GetTopY() const
    {
        return m_topY;
    }

    SHORT GetTopX() const
    {
        return m_topX;
    }

    COORD GetLogShapeCoord() const
    {
        return COORD{ GetTopX(), GetTopY() + 5 };
    }

    COORD GetLogFlushCoord() const
    {
        return COORD{ GetTopX() + 13, GetTopY() + 1 };
    }

    COORD GetQueueCoord() const
    {
        return COORD{ GetTopX() + 25, GetTopY() };
    }

    COORD GetSizeFlushCoord() const
    {
        return COORD{ GetTopX() + 33, GetTopY() + 1 };
    }

    COORD GetClientCoord(DWORD id)
    {
        return COORD{ GetTopX() + 62, GetTopY() + 3 * static_cast<SHORT>(id) + 1 };
    }

    COORD GetConnectsCoord(DWORD id)
    {
        return COORD{ GetTopX() + 38, GetClientCoord(id).Y };
    }
};
