#ifndef __THREAD_H__
#define __THREAD_H__
class Thread
{
public:
	Thread();
	virtual ~Thread();
#ifdef __WINDOWS__
	static unsigned __stdcall threadfunc(void* arg);
#else
	static void* threadfunc(void* arg);
#endif
};

#endif