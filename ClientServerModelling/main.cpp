// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simulator.h"
#include "view.h"

DWORD ValidInput(DWORD min, DWORD max);

// Return values:
// 0 - OK
// 1 - can't create log file
// 2 - other exception
int _tmain(int argc, _TCHAR* argv[])
{
    using std::cout;
    using std::endl;

    try
    {
        cout << "Enter number of clients: ";
        DWORD clients = ValidInput(Constants::MIN_CLIENTS, Constants::MAX_CLIENTS);
        cout << "Start modelling. Enter any char to quit. For results see log file.\n";
        Simulator simulator(clients);
        simulator.Start();
        std::cin.get();
    }
    catch (const std::bad_exception &e)
    {
        cout << e.what() << endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
        return 2;
    }
    return 0;
}

DWORD ValidInput(DWORD min, DWORD max)
{
    using std::cin;
    using std::cout;

    DWORD value{};
    cin >> value;
    while (cin.fail() || value < min || value > max)
    {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cout << "Bad entry. Enter a number in range ["
            << min << ", " << max << "]: ";
        cin >> value;
    }
    cin.ignore(cin.rdbuf()->in_avail());
    return value;
}
