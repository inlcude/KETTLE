#include"stdafx.h"
#include"ThreadMutex.h"

ProcessMutex::ProcessMutex(const char* lock_name)
#ifdef __LINUX__
:mutex(nullptr)
#endif
{
#ifdef __LINUX__
	int fd = open(lock_name,O_RDWR | O_CREAT | O_EXCL,S_IRUSR|S_IWUSR|S_IROTH);
	if(fd < 0){
		fd = open(lock_name,O_RDWR);
		if(fd < 0)
		    err_exit(errno,"open mutex failed");
		void* address = mmap(nullptr,sizeof(pthread_mutex_t),PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
		if(MAP_FAILED == address)
			err_exit(errno,"mmap failed");
		close(fd);

		pthread_mutex_t* mutex = (pthread_mutex_t*)address;
	}
	else{
		if(ftruncate(fd,sizeof(pthread_mutex_t)) < 0)
			err_exit(errno,"ftruncate failed");
		void* address = mmap(nullptr,sizeof(pthread_mutex_t),PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
		if(MAP_FAILED == address)
			err_exit(errno,"mmap failed");
		close(fd);

		int pthread_err = 0;
		pthread_mutexattr_t attr;  
		if((pthread_err = pthread_mutexattr_init(&attr)) != 0)
			err_exit(pthread_err,"pthread attr init error"); 
		if((pthread_err = pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED)) != 0)
			err_exit(pthread_err,"pthread set shared failed");
		if((pthread_err = pthread_mutex_init(mutex,&attr)) != 0)
			err_exit(pthread_err,"pthread_mutex init failed");
		if((pthread_err = pthread_mutexattr_destroy(&attr)) != 0)
			err_exit(pthread_err,"pthread mutex destroy failed");
	}
#endif
}

bool ProcessMutex::Lock(){
#ifdef __LINUX__
    int pthread_err = 0;
	if((pthread_err = pthread_mutex_lock(mutex)) != 0)
	{
		if(pthread_err != EOWNERDEAD)
			err_exit(pthread_err,"pthread mutex lock failed");
		if((pthread_err = pthread_mutex_consistent(mutex)) != 0)
		    err_exit(pthread_err,"mutex consisten error");
        return false;
	}
#endif
    return true;
}

bool ProcessMutex::UnLock() {
#ifdef __LINUX__
	int pthread_err = 0;
	if((pthread_err = pthread_mutex_unlock(pthread_err)) != 0)
		err_exit(pthread_err,"mutex unlock failed");
#endif
    return true;
}