#pragma once

#if !defined NDEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#pragma warning( disable : 4985 )
#include <crtdbg.h>
#pragma warning( default : 4985 )
#endif