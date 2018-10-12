#include"stdafx.h"
#include"TemplateFunctions.h"

using namespace KETTLE;

void KETTLE::CommonFunction::FunctionSleep(int milsec)
{
#if __WINDOWS__
    Sleep(milsec);
#elif __LINUX__
    ::nanosleep(milsec * 1000 * 1000);
#endif
}
