#pragma once
#include "stdafx.h"

namespace Constants
{
    const DWORD MAX_DATA_SIZE = 255;

    const BYTE MIN_REQUEST_PRIORITY = 0;
    const BYTE MAX_REQUEST_PRIORITY = 255;

    const DWORD MIN_CLIENTS = 1;
    const DWORD MAX_CLIENTS = 10;
    const DWORD DEFAULT_CLIENTS = 1;

    // In milliseconds.
    const DWORD MIN_REQUEST = 6000;
    // In milliseconds.
    const DWORD MAX_REQUEST = 8000;

    // In milliseconds.
    const DWORD MIN_SERVER_RESPONSE = 1000;
    // In milliseconds.
    const DWORD MAX_SERVER_RESPONSE = 2000;

    const std::wstring DEFAULT_LOG_FILE_NAME = L"file.log";

    // In milliseconds.
    const DWORD FLASHING_TIME = 300;
}
