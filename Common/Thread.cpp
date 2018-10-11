#include"Thread.h"
#include"ThreadTask.h"
#include"TemplateFunctions.h"


bool KETTLE::Thread::CreateThread()
{
#ifdef __WINDOWS__
    // 创建但是不运行,先挂起
	m_nThreadHandle = (HANDLE)_beginthreadex(NULL,
		0,
		&(KETTLE::Thread::threadfunc),
		(void*)this,
		CREATE_SUSPENDED,
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
            AutoLock lock(&m_TaskListMutex);
            if (m_TaskList.empty())
            {
                CommonFunction::FunctionSleep(10);
                continue;
            }

			m_nThreadState = THREAD_STATE_BUSY;
            for (auto& iter : m_TaskList)
            {
                iter->Run(NULL);
                iter->SetStatues(TASKSTATUES_FINISHED);
            }

            m_TaskList.clear();
            m_nThreadState = THREAD_STATE_RUN;
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
#if __WINDOWS__
    if(SuspendThread(m_nThreadHandle)) m_nThreadState = THREAD_STATE_SLEEP;
#elif __LINUX__
#endif
}

void KETTLE::Thread::NotifyThreadRun()
{
#if __WINDOWS__
    if (ResumeThread(m_nThreadHandle)) m_nThreadState = THREAD_STATE_RUN;
#elif __LINUX__
#endif
}

void KETTLE::Thread::SetThreadState(KETTLE::Thread::THREAD_STATE nState)
{
	m_nThreadState = nState;
}

bool KETTLE::Thread::AddTask(ITask* task)
{
    if (!task) return false;
    AutoLock autolock(&m_TaskListMutex);

    m_TaskList.push_back(task);
    return true;
}