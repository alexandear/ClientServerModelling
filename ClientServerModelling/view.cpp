#include "stdafx.h"
#include "view.h"

View::View(DWORD clients)
    : m_clients(clients)
{
    m_console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (m_console == INVALID_HANDLE_VALUE)
    {
        throw std::runtime_error("Couldn't get console.");
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(m_console, &csbi))
    {
        throw std::runtime_error("Couldn't get cursor position.");
    }
    m_topX = 1;
    m_topY = csbi.dwCursorPosition.Y + 1;
    m_bottomY = m_topY + 8;

    PaintServer();
    PaintLog();
    PaintQueue();
    PaintClients();
    PaintConnects();

    Write(L"0", GetSizeFlushCoord());
}

void View::ShowRequest(const TDATA &request, DWORD size)
{
    COORD coord{ 44, static_cast<SHORT>(GetTopY() + 1 + 3 * (request.dwClientId - 1)) };
    Write(L"REQ " + std::to_wstring(request.cPriority), coord);
    ShowSize(size);
    std::this_thread::sleep_for(std::chrono::milliseconds(Constants::FLASHING_TIME));
    Write(L"───────", coord);
}

void View::ShowSize(DWORD size)
{
    Write(L"   ", GetSizeFlushCoord());
    Write(std::to_wstring(size), GetSizeFlushCoord());
}

void View::ShowLog(const TDATA &request, DWORD size)
{
    std::wstring log(L"LOG");
    Write(log + L"(" + std::to_wstring(request.dwClientId) + L", "
        + std::to_wstring(request.cPriority) + L")", GetLogFlushCoord());
    ShowSize(size);
    std::this_thread::sleep_for(std::chrono::milliseconds(Constants::FLASHING_TIME));
    Write(L"────────────", GetLogFlushCoord());
}

void View::Paint(const std::vector<std::wstring> &figure, const COORD &coord)
{
    for (size_t i = 0; i < figure.size(); ++i)
    {
        Write(figure[i], COORD{ coord.X, coord.Y + i });
    }
}

void View::PaintServer()
{
    std::vector<std::wstring> server = {
        L"┌────────┐",
        L"│ SERVER │",
        L"└───┬────┘",
        L"    │     ",
        L"    ↓     "
    };
    Paint(server, COORD{ GetTopX(), GetTopY() });
}

void View::PaintLog()
{
    std::vector<std::wstring> logFile = {
        L"┌────────┐",
        L"│        │",
        L"└─────<d>┘"
    };
    Paint(logFile, GetLogShapeCoord());
    Write(Constants::DEFAULT_LOG_FILE_NAME, 
        COORD{ GetLogShapeCoord().X + 1, GetLogShapeCoord().Y + 1 });
}

void View::PaintQueue()
{
    std::vector<std::wstring> queue = {
        L"┌───────────┐",
        L"│ QUEUE     │"
    };
    std::wstring queueBody = L"│           │";
    for (size_t i = 0; i < m_clients; ++i)
    {
        queue.push_back(queueBody);
        queue.push_back(queueBody);
        queue.push_back(queueBody);
    }
    queue.pop_back();
    std::wstring queueBottom = L"└───────────┘";
    queue.push_back(queueBottom);

    if (m_clients > 1)
    {
        m_bottomY = GetQueueCoord().Y + queue.size();
    }
    Paint(queue, GetQueueCoord());

}

void View::PaintClient(DWORD id, const COORD &coord)
{
    std::vector<std::wstring> client = {
        L"┌──────────┐",
        L"│ CLIENT   │",
        L"└──────────┘"
    };
    Paint(client, COORD{ coord.X - 9, coord.Y - 1 });
    Write(std::to_wstring(id), coord);
}

void View::PaintClients()
{
    for (DWORD i = 0; i < m_clients; ++i)
        PaintClient(i + 1, GetClientCoord(i));
}

void View::PaintConnects()
{
    std::wstring connection(L"←──────────────");
    Write(connection, COORD{ GetLogFlushCoord().X - 3, GetLogFlushCoord().Y });
    for (DWORD i = 0; i < m_clients; ++i)
        Write(connection, GetConnectsCoord(i));
}

void View::Write(const std::wstring &msg, const COORD &coord)
{
    SetConsoleCursorPosition(m_console, coord);
    WriteConsole(m_console, msg.c_str(), msg.size(), nullptr, nullptr);
}
