#ifndef __THREAD_TASK_H__
#define __THREAD_TASK_H__

namespace KETTLE
{
    enum TASKSTATUES
    {
        TASKSTATUES_DEFAULT   = 0,          // 缺省状态
        TASKSTATUES_SUBMIT    = 1,          // 已经提交等待处理
        TASKSTATUES_FINISHED  = 2,          // 处理完成
    };
    class ITask
    {
    public:
        ITask() : _STATUES(TASKSTATUES_DEFAULT){}
        virtual ~ITask(){}
	    virtual void Run(void* param) = 0;

        virtual void SetStatues(TASKSTATUES statues) final
        {
            _STATUES = statues;
        }

        virtual TASKSTATUES GetStatues() const final
        {
            return _STATUES;
        }
    private:
        TASKSTATUES    _STATUES;
    };
}

#endif
