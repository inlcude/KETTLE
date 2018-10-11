#ifndef __THREAD_TASK_H__
#define __THREAD_TASK_H__

namespace KETTLE
{
    enum TASKSTATUES
    {
        TASKSTATUES_DEFAULT   = 0,          // ȱʡ״̬
        TASKSTATUES_SUBMIT    = 1,          // �Ѿ��ύ�ȴ�����
        TASKSTATUES_FINISHED  = 2,          // �������
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
