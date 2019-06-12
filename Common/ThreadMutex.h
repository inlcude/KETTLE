#ifndef __THREAD_MUTEX_H__
#define __THREAD_MUTEX_H__
#include "KETTLEPlatform.h"

namespace KETTLE
{
	class ILock{
		friend class AutoLock;
	public:
        virtual ~ILock() {}
	protected:
		virtual bool Lock() = 0;
		virtual bool UnLock() = 0;
	};

/////////////////////////////////////////////////////////////
	class ThreadMutex final : public ILock{
		friend class ThreadCondition;
		public:
			ThreadMutex();
			~ThreadMutex();
		protected:
			virtual bool Lock() override final;
			virtual bool UnLock() override final;
		private:
			pthread_mutex_t mutex;
	};

/////////////////////////////////////////////////////////////////

// not safe for 2 process 
// process A open mutex
//						process B open mutex
//						process B lock mutex
// process A init mutex
// process A lock mutex
// 
// result : two process both lock mutex; should use posix sem instead this ProcessMutex
	class ProcessMutex final : public ILock{
		public:
			ProcessMutex(const char* lock_name);
		protected:
			virtual bool Lock() override final;
			virtual bool UnLock() override final;
		private:
			pthread_mutex_t* mutex; 
	};
//////////////////////////////////////////////////////////////////
	class ProcessSem final : public ILock
	{
		public:
			ProcessSem(const char* sem_name);
			~ProcessSem();
		public:
			virtual bool Lock() override final;
			virtual bool UnLock() override final;
		private:
			sem_t* _sem;
			std::string _sem_name;
	};

//////////////////////////////////////////////////////////////////
	class AutoLock final{
	public:
        AutoLock(std::shared_ptr<ILock>);
		~AutoLock();
	private:
		std::shared_ptr<ILock>   m_pLock;
	};
}

#endif