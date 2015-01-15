#pragma once

#include "stdafx.h"
#include "constants.h"

//
// Request
//
typedef struct tagTDATA
{
    // Priority of request 0-255 (0 - highest priority)
    BYTE cPriority;
    // Request's creation time in system clock ticks
    DWORD dwTicks;
    // Unique client ID
    DWORD dwClientId;
    // Abstract data
    char data[Constants::MAX_DATA_SIZE];
} TDATA, *PTDATA;
