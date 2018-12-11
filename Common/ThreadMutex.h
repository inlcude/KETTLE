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

/////////////////////////////////////////////////////////////
	class ThreadMutex final : public ILock
	{
		public:
			ThreadMutex();
			~ThreadMutex();
		private:
			pthread_mutex_t mutex;
	};

/////////////////////////////////////////////////////////////////
	class ProcessMutex final : public ILock
	{
		public:
			ProcessMutex(const char* lock_name);
		public:
			virtual bool Lock() override final;
			virtual bool UnLock() override final;
		private:
			pthread_mutex_t* mutex; 
	};

//////////////////////////////////////////////////////////////////
	class AutoLock
	{
	public:
        AutoLock(std::shared_ptr<ILock>);
		~AutoLock();
	private:
		std::shared_ptr<ILock>   m_pLock;
	};
}

#endif