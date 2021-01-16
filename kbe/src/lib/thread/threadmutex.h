// Copyright 2008-2018 Yolo Technologies, Inc. All Rights Reserved. https://www.comblockengine.com

/*
	�̻߳����壺
	�÷�:
		ThreadMutex tm;
		tm.lockMutex();
		....��ȫ����
		tm.unlockMutex();
		
		��������ThreadGuard��ʹ��
		��һ�����ж��廥�����Ա
		ThreadMutex tm;
		����Ҫ�����ĵط�:
		void XXCLASS::func(void)
		{
			ThreadGuard tg(this->tm);
			����Ĵ��붼�ǰ�ȫ��
			...
		}
*/
#ifndef __THREADMUTEX_H__
#define __THREADMUTEX_H__
	
#include "common/common.h"


namespace KBEngine{ namespace thread{

class ThreadMutexNull
{
public:
	ThreadMutexNull(void)
	{
	}

	virtual ~ThreadMutexNull(void)
	{
	}

	virtual void lockMutex(void)
	{
	}

	virtual void unlockMutex(void)
	{
	}
};

class ThreadMutex : public ThreadMutexNull
{
public:
	ThreadMutex(void)
	{
		THREAD_MUTEX_INIT(mutex_);
	}

	/*
		notes: https://www.cnblogs.com/qiu00/p/11914595.html
		���ʹ��Ĭ�ϵĿ������캯�������е����г�Ա��������Ӳ������п���һ�ݣ�
		ע�⣺ָ���Ա�����Ŀ���������ָ�������������ָ��ָ��ı���ֵ������֮��
		���һ��ָ���Ա������ͨ����������ģ���ô�ó�Աָ��Ͳ������еĳ�Աָ��
		ָ��ͬһ���ڴ�.
	*/
	ThreadMutex(const ThreadMutex& v)
	{
	   // ���ﲻ����������mutex_��mutex_ = v.mutex_;�������Ƿǳ�Σ�յ�, ����ɶ��THREAD_MUTEX_DELETE
		THREAD_MUTEX_INIT(mutex_);
	}

	ThreadMutex& operator=(const ThreadMutex&) = delete;  //���ø�ֵ����

	virtual ~ThreadMutex(void)
	{ 
		THREAD_MUTEX_DELETE(mutex_);
	}	
	
	virtual void lockMutex(void)
	{
		THREAD_MUTEX_LOCK(mutex_);
	}

	virtual void unlockMutex(void)
	{
		THREAD_MUTEX_UNLOCK(mutex_);
	}

protected:
	THREAD_MUTEX mutex_;
};

}
}
#endif
