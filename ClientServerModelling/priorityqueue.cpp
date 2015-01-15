#include "stdafx.h"
#include "priorityqueue.h"

bool CompareTDATA(const TDATA &lhs, const TDATA &rhs)
{
    return lhs.cPriority > rhs.cPriority;
}
