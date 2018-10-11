#ifndef __THREAD_H__
#define __THREAD_H__

#include<list>

#include"KETTLEPlatform.h"
#include"ThreadMutex.h"

namespace KETTLE
{
	class ITask;
	class ThreadPool;
	class Thread
	{
		friend class ThreadPool;
	public:
		enum THREAD_STATE
		{
			THREAD_STATE_UNINITIALIZED = 0,            // 线程未初始化
			THREAD_STATE_INITIALIZED,                  // 线程初始化，但未运行
			THREAD_STATE_RUN,                          // 线程正在运行
			THREAD_STATE_SLEEP,                        // 线程正在挂起
			THREAD_STATE_BUSY,                         // 线程正在忙碌
			THREAD_STATE_STOP,                         // 线程停止工作
		};
	public:
		Thread():m_nThreadState(THREAD_STATE_UNINITIALIZED),m_bExitThread(false), m_nThreadHandle(0), m_nThreadId(0)
		{
		}
		virtual ~Thread()
		{
		}
	#ifdef __WINDOWS__
		static unsigned __stdcall threadfunc(void* arg);
	#else
		static void* threadfunc(void* arg);
	#endif
		bool CreateThread();
		THREAD_STATE GetThreadState() const;
		THREAD_STATE GetThreadState();

        bool AddTask(ITask* task);
	protected:
		bool IsThreadExit()
		{
			return m_bExitThread;
		}
		
		void SetThreadState(THREAD_STATE nState);
		unsigned ThreadFunc();

        void NotifyThreadExit();
        void NotifyThreadSleep();
        void NotifyThreadRun();

	private:
		KETTLE::THREAD_HANDLE     m_nThreadHandle;
		THREAD_ID                 m_nThreadId;
		THREAD_STATE              m_nThreadState;
		bool                      m_bExitThread;
		std::list<ITask*>         m_TaskList;
        ThreadMutex               m_TaskListMutex;

        typedef::std::list<const ITask*>::const_iterator TASK_CONST_ITR;
	};
	
}
#endif