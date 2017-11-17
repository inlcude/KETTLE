#ifndef __THREAD_H__
#define __THREAD_H__
#include"Platform.h"
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
			THREAD_STATE_UNINITIALIZED = 0,
			THREAD_STATE_INITIALIZED,
			THREAD_STATE_RUN,
			THREAD_STATE_SLEEP,
			THREAD_STATE_BUSY,
			THREAD_STATE_STOP,
		};
	public:
		Thread():m_nThreadState(THREAD_STATE_UNINITIALIZED),THREAD_ID(0),m_bExitThread(false),_task(NULL)
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
		THREAD_STATE GetThreadState();
		
		void NotifyThreadExit();
		bool IsExit();
		
		void NotifyThreadSleep();
		bool IsSleep();
	protected:
		bool IsThreadExit()
		{
			return m_bExitThread;
		}
		
		void SetThreadState(THREAD_STATE nState);
	private
		THREAD_ID             m_nThreadID;
		THREAD_STATE          m_nThreadState;
		bool                  m_bExitThread;
		ITask*                _task;
	};
	
	class ThreadPool
	{
	}
}
#endif