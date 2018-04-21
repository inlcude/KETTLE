#include"Thread.h"
#include"ThreadTask.h"


bool KETTLE::Thread::CreateThread()
{
#ifdef __WINDOWS__
	m_nThreadHandle = (HANDLE)_beginthreadex(NULL,
		0,
		&(KETTLE::Thread::threadfunc),
		(void*)this,
		0,
		&m_nThreadId);

	m_nThreadState = THREAD_STATE_INITIALIZED;
#else
#endif
	return true;
}
#ifdef __WINDOWS__
unsigned __stdcall KETTLE::Thread::threadfunc(void* arg)
{
	Thread* pThis = static_cast<Thread*>(arg);
	return pThis->ThreadFunc();
}
#else
void* Thread::threadfunc(void* arg)
{
	return NULL;
}
#endif

unsigned KETTLE::Thread::ThreadFunc()
{
	std::cout << "Thread start" << std::endl;
	while (m_nThreadState)
	{
		if (m_nThreadState == THREAD_STATE_RUN)
		{
			m_nThreadState = THREAD_STATE_BUSY;
			//_task->Run(NULL);
		}
		;//;if(_task) _task->
	}

	std::cout << "Thread end" << std::endl;
	return 0;
}

KETTLE::Thread::THREAD_STATE KETTLE::Thread::GetThreadState() const
{
	return m_nThreadState;
}

KETTLE::Thread::THREAD_STATE KETTLE::Thread::GetThreadState()
{
	return m_nThreadState;
}

void KETTLE::Thread::NotifyThreadExit()
{

}

void KETTLE::Thread::NotifyThreadSleep()
{

}

void KETTLE::Thread::SetThreadState(KETTLE::Thread::THREAD_STATE nState)
{
	m_nThreadState = nState;
}

