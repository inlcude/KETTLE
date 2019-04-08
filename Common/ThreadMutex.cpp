#include"stdafx.h"
#include"ThreadMutex.h"
#include"Log.h"

////////////////////////////////////////////////////////////////
KETTLE::ThreadMutex::ThreadMutex():mutex(PTHREAD_MUTEX_INITIALIZER){
}

KETTLE::ThreadMutex::~ThreadMutex(){
    pthread_mutex_destroy(&mutex);
}

bool KETTLE::ThreadMutex::Lock(){
	int pthread_err = 0;
	if((pthread_err = pthread_mutex_lock(&mutex)) != 0){
		err_exit(pthread_err,"pthread mutex lock failed");
	}
}

bool KETTLE::ThreadMutex::UnLock(){
	int pthread_err = 0;
	if((pthread_err = pthread_mutex_unlock(&mutex)) != 0)
		err_exit(pthread_err,"mutex unlock failed");
    return true;
}
/////////////////////////////////////////////////////////////////
KETTLE::ProcessMutex::ProcessMutex(const char* lock_name) : mutex(nullptr)
{
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

        pthread_mutex_t* mutex = (pthread_mutex_t*)address;
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
}

bool KETTLE::ProcessMutex::Lock(){
    int pthread_err = 0;
	if((pthread_err = pthread_mutex_lock(mutex)) != 0){
		if(pthread_err != EOWNERDEAD)
			err_exit(pthread_err,"pthread mutex lock failed");
		if((pthread_err = pthread_mutex_consistent(mutex)) != 0)
		    err_exit(pthread_err,"mutex consisten error");
        return false;
	}

    return true;
}

bool KETTLE::ProcessMutex::UnLock() {
	int pthread_err = 0;
	if((pthread_err = pthread_mutex_unlock(mutex)) != 0)
		err_exit(pthread_err,"mutex unlock failed");
    return true;
}
////////////////////////////////////////////////////////////////////
KETTLE::ProcessSem::ProcessSem(const char* sem_name) : _sem_name(sem_name),_sem(nullptr){
    _sem = sem_open(sem_name,O_CREAT|O_EXCL,S_IRUSR|S_IWUSR|S_IROTH,1);
    if(_sem == SEM_FAILED){
        _sem = sem_open("shared_sem",O_CREAT,S_IRUSR|S_IWUSR|S_IROTH);
        if(_sem == SEM_FAILED)
            err_exit(errno,"create sem failed");
    }
}

KETTLE::ProcessSem::~ProcessSem(){
    sem_close(_sem);
    sem_unlink(_sem_name.c_str());
}

bool KETTLE::ProcessSem::Lock(){
    sem_wait(_sem);
    return true;
}

bool KETTLE::ProcessSem::UnLock(){
    sem_post(_sem);
    return true;
}
////////////////////////////////////////////////////////////////////
KETTLE::AutoLock::AutoLock(std::shared_ptr<ILock> pLock) : m_pLock(pLock){
    m_pLock->Lock();
}

KETTLE::AutoLock::~AutoLock(){
    m_pLock->UnLock();
}   