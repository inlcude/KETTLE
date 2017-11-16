#include"stdafx.h"
#include "Thread.h"




#ifdef __WINDOWS__
unsigned __stdcall Thread::threadfunc(void* arg)
{
	Thread* pTd = static_cast<Thread*>(arg);
	pTd->SetThreadState(THREAD_STATE_INITIALIZED);
	THREAD_STATE _ts; 
	while(_ts = pTd->GetThreadState())
	{
		if(ts == THREAD_STATE_STOP) break;
		if(ts == THREAD_STATE_SLEEP) continue;
		if(ts != THREAD_STATE_RUN) continue;
		
		{
			pTd->SetThreadState(THREAD_STATE_BUSY);
		}
		pTd->SetThreadState(THREAD_STATE_RUN);
	}
	return 0;
}
#else
void* Thread::threadfunc(void* arg)
{
}
#endif

bool Thread::CreateThread()
{
#ifdef __WINDOWS__
	m_nThreadID = __beginthreadex(NULL,0,&(Thread::threadfunc),this,0,NULL)
	return true;
#else
#endif
}

