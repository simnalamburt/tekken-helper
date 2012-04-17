#pragma once

#ifdef _DEBUG

#if defined(_INC_CRTDBG) && !defined(_CRTDBG_MAP_ALLOC)
#include "CoreDef.h"
#pragma message ( __WARNING__ \
    "header file <crtdbg.h> was already included without macro _CRTDBG_MAP_ALLOC, " \
    "there will be no location data for memory leak occured by CRT malloc functions")
#else
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

static struct CheckMemLeak
{
    CheckMemLeak()
    {
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
        _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE );
    }
} ___G___CheckMemLeak;

#endif