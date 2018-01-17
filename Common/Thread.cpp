#include"stdafx.h"
#include "Thread.h"



namespace KETTLE
{
#ifdef __WINDOWS__

	unsigned __stdcall Thread::threadfunc(void* arg)
	{
		Thread* pTd = static_cast<Thread*>(arg);
		pTd->SetThreadState(THREAD_STATE_INITIALIZED);
		THREAD_STATE _ts;
		while (1)
		{
			//if (pTd->IsExit()) break;
			//if (pTd->)
			//{
			//}
			//if (ts != THREAD_STATE_RUN) continue;

			//{
			//	pTd->SetThreadState(THREAD_STATE_BUSY);
			//}
			//pTd->SetThreadState(THREAD_STATE_RUN);
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
		//m_nThreadID = __beginthreadex(NULL, 0, &(Thread::threadfunc), this, 0, NULL);
			return true;
#else
#endif
		return false;
	}

	void Thread::SetThreadState(THREAD_STATE nState)
	{

	}
}
