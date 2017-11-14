#include"stdafx.h"
#include "Thread.h"



Thread::Thread()
{
}


Thread::~Thread()
{
}
#ifdef __WINDOWS__
unsigned __stdcall Thread::threadfunc(void* arg)
{
	return 0;
}
#else
void* Thread::threadfunc(void* arg)
{
}
#endif

