#ifndef __THREAD_MUTEX_H__
#define __THREAD_MUTEX_H__
#include "KETTLEPlatform.h"

namespace KETTLE
{
	class ILock
	{
	public:
        virtual ~ILock() {}
		virtual bool Lock() = 0;
		virtual bool UnLock() = 0;
	};

	class ThreadMutex final : public ILock
	{
	public:
		ThreadMutex() {
#if __WINDOWS__
            // ����̬������
			m_HandleMutex = CreateMutex(NULL, false, NULL);
#elif __LINUX__

#endif
		}

		virtual bool Lock() override final
		{
#if __WINDOWS__
			DWORD return_code = WaitForSingleObject(m_HandleMutex, INFINITE);
            // wait handle active, WAIT_OBJECT_0 is success
            if (WAIT_OBJECT_0 != return_code) return false;
#elif __LINUX__
#endif
			return true;
		}

		virtual bool UnLock() override final
		{
#if __WINDOWS__
            ReleaseMutex(m_HandleMutex);
#elif __LINUX__
#endif
			return true;
		}
		~ThreadMutex()
		{
#if __WINDOWS__
			CloseHandle(m_HandleMutex);
#elif __LINUX__
#endif
		}
	private:
#if __WINDOWS__
		HANDLE           m_HandleMutex;
#elif __LINUX__
#endif
	};

	class ProcessMutex final : public ILock
	{
		public:
			ProcessMutex(const char* lock_name);
		public:
			virtual bool Lock() override final;
			virtual bool UnLock() override final;
		private:
			#ifdef __LINUX__
				pthread_mutex_t* mutex; 
			#endif
	};


	class AutoLock
	{
	public:
        AutoLock(ILock* pLock) : m_pLock(pLock) {
			m_pLock->Lock();
		}

		~AutoLock()
		{
			m_pLock->UnLock();
		}
	private:
		ILock*              m_pLock;
		
	};
}

#endif