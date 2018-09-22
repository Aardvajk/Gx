#include "GxCore/GxDebug.h"
#include "GxCore/GxWindows.h"

Gx::Debug::~Debug()
{
    OutputDebugString(o.str().c_str());
    OutputDebugString("\n");
}
