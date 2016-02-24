#pragma once

// ----------------------------------------------------------------------------------
#pragma region __WARNING__, __ERROR__
// stringised version of line number (must be done in two steps)
#define STRINGISE(N) #N
#define EXPAND_THEN_STRINGISE(N) STRINGISE(N)

// MSVC-suitable routines for formatting <#pragma message>
#define __LOC__ __FILE__ "(" EXPAND_THEN_STRINGISE(__LINE__) ")"
#define __OUTPUT_FORMAT__(type) __LOC__ " : " type " : "

// specific message types for <#pragma message>
#define __WARNING__ __OUTPUT_FORMAT__("warning")
#define __ERROR__ __OUTPUT_FORMAT__("error")
#pragma endregion
// ----------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------
#include "ErrorReporter.h"

#pragma region HR_THROW_MSG, HR_THROW
#define HR_THROW_MSG(x, msg) \
do { \
    HRESULT __hresult = (x); \
    if( FAILED(__hresult) ) throw ErrorReporter( __FILE__, __LINE__, __FUNCTION__, #x, __hresult, msg ); \
} while ( false )

#define HR_THROW(x) HR_THROW_MSG(x, nullptr)
#pragma endregion

#pragma region FALSE_THROW_MSG, FALSE_THROW
#define FALSE_THROW_MSG(x, msg) \
do { \
    if( !(x) ) throw ErrorReporter( __FILE__, __LINE__, __FUNCTION__, #x, E_FAIL, msg ); \
} while ( false )

#define FALSE_THROW(x) FALSE_THROW_MSG(x, nullptr)
#pragma endregion

#pragma region NONZERO_THROW_MSG, NONZERO_THROW
#define NONZERO_THROW_MSG(x, msg) \
do { \
    if( x ) throw ErrorReporter( __FILE__, __LINE__, __FUNCTION__, #x, E_FAIL, msg ); \
} while ( false )

#define NONZERO_THROW(x) NONZERO_THROW_MSG(x, nullptr)
#pragma endregion
// ----------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------
#include "CheckMemLeak.h"
#include "uclock.h"
