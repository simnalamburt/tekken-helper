#include "StdAfx.h"
#include "uclock.h"
#include "CoreDef.h"

uclock_t uclock()
{
    static _LARGE_INTEGER frequency;
    static const BOOL isAvailable = QueryPerformanceFrequency(&frequency);
    FALSE_THROW_MSG ( isAvailable, "current CPU do not support Precise Performance Counter" );
    _LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return uclock_t(now.QuadPart) / uclock_t(frequency.QuadPart) * 1000;
}