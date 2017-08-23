#ifndef __THREAD_H
#define __THREAD_H

#include<vector>
#include<string>
#include<pthread.h>

using namespace std;

/*
*执行任务的类，设置任务数据并执行
*/
class CTask{
protected:
    string m_strTaskName; //
    void* m_ptrData; //
public:
    CTask(){}
    CTask(string taskName){
        m_strTaskName = taskName;
        m_ptrData = NULL;
    }
    virtual int Run() = 0;
    void SetData(void* data);

    virtual ~CTask(){}
};

/*
*线程池管理类的实现
*/
class CThreadPool{
private:
    static vector<CTask*> m_vecTaskList; //task list
    static bool shutdown;                //thread stop flag
    int    m_iThreadNum;                //numbers of thread in threadpool
    pthread_t *pthread_id;

    static pthread_mutex_t m_pthreadMutex;  //线程同步锁
    static pthread_cond_t m_pthreadCond;    //线程同步的条件变量

protected:
    static void* ThreadFunc(void* threadData);
    static int MoveToIdle(pthread_t tid);
    static int MoveToBusy(pthread_t tid);

    int Create();

public:
    CThreadPool(int threadNum = 10);
    int AddTask(CTask *task);
    int StopAll();
    int getTaskSize();
};

#endif // __THREAD_H
