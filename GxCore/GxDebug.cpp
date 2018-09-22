#include "GxCore/GxDebug.h"

#include <windows.h>

Gx::Debug::~Debug()
{
    OutputDebugString(o.str().c_str());
    OutputDebugString("\n");
}
