#include"stdafx.h"
#include"TemplateFunctions.h"

using namespace KETTLE;

void KETTLE::CommonFunction::FunctionSleep(int milsec)
{
#if __WINDOWS__
    Sleep(milsec);
#elif __LINUX__
#endif
}
