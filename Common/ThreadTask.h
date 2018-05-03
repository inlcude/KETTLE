#ifndef __THREAD_TASK_H__
#define __THREAD_TASK_H__

class ITask
{
public:
	virtual void Run(void* param) = 0;
};
#endif
