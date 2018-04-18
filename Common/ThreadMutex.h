#ifndef __THREAD_MUTEX_H__
#define __THREAD_MUTEX_H__
#include "KETTLEPlatform.h"

namespace KETTLE
{
	class ThreadMutex
	{
	public:
		ThreadMutex() {
#if __WINDOWS__
			m_Handle = CreateMutex(NULL, false, NULL);
#elif __LINUX__

#endif
		}

		bool Wait()
		{
#if __WINDOWS__
			WaitForSingleObject(m_Handle, INFINITE);
#elif __LINUX__
#endif
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
}

#endif