#pragma once
#include "message.h"
#include "object.h"
#include "message_system.h"

#ifndef NDEBUG
#pragma comment( lib, "mds-debug.lib" )
#else
#pragma comment( lib, "mds-release.lib" )
#endif