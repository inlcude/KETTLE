#ifndef __THREAD_MUTEX_H__
#define __THREAD_MUTEX_H__
#include "Platform.h"

namespace KETTLE
{
	class ThreadMutex
	{
	public:
		ThreadMutex() {
#ifdef __WINDOWS__
			m_Handle = CreateMutex(NULL, false, NULL);
#elif 

#endif
		}

		bool Wait()
		{
			WaitForSingleObject(m_Handle, INFINITE);
			return true;
		}
		~ThreadMutex()
		{
			CloseHandle(m_Handle);
		}
	private:
		HANDLE           m_Handle;
	};
}

#endif