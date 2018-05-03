#ifndef __THREAD_MUTEX_H__
#define __THREAD_MUTEX_H__
#include "KETTLEPlatform.h"

namespace KETTLE
{
	class ILock
	{
	public:
		virtual bool Lock() = 0;
		virtual bool Unlock() = 0;
	};
	class ThreadMutex : public ILock
	{
	public:
		ThreadMutex() {
#if __WINDOWS__
			m_Handle = CreateMutex(NULL, false, NULL);
#elif __LINUX__

#endif
		}

		virtual bool Lock()
		{
#if __WINDOWS__
			WaitForSingleObject(m_Handle, INFINITE);
#elif __LINUX__
#endif
			return true;
		}

		virtual bool UnLock()
		{
			return true;
		}
		~ThreadMutex()
		{
#if __WINDOWS__
			CloseHandle(m_Handle);
#elif __LINUX__
#endif
		}
	private:
		HANDLE           m_Handle;
	};

	class AutoLock
	{
	public:
		AutoLock(ILock* pLock) : m_pLock(pLock) {
			m_pLock->Lock();
		}

		~AutoLock()
		{
			m_pLock->Unlock();
		}
		//virtual bool Lock()
		//{
		//	return m_pLock->Lock();
		//}
		//virtual bool Unlock()
		//{
		//	return m_pLock->Unlock();
		//}
	private:
		ILock*              m_pLock;
		
	};
}

#endif