/******************************************************************
@源程序名称: Lock.h
@软件著作权: 恒生电子股份有限公司 版权所有
@系统名称: 
@模块名称: 
@功能说明: 进程锁
@相关文档: 
@作者:     
@审核: (可选的)

@修改记录
@修改日期: 2013-02-26
@修改人员: 唐模超
@修改说明: 创建
@版本：   1.0

*******************************************************************/

#ifndef _H_LOCK_H_
#define _H_LOCK_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#endif

class Lock
{
public:
	Lock()
	{
#ifdef _WIN32
		InitializeCriticalSection(&m_lock);
#else
		pthread_mutex_init(&m_lock,NULL);
#endif
	}

	~Lock()
	{
#ifdef _WIN32
		DeleteCriticalSection(&m_lock);
#else
		pthread_mutex_destroy(&m_lock);
#endif
	}

	void Acquire()
	{
#ifdef _WIN32
		EnterCriticalSection(&m_lock);
#else
		pthread_mutex_lock(&m_lock);
#endif

	}
	void Release()
	{
#ifdef _WIN32
		LeaveCriticalSection(&m_lock);
#else
		pthread_mutex_unlock(&m_lock);
#endif
	}
private:
#ifdef _WIN32
	CRITICAL_SECTION m_lock;
#else
	pthread_mutex_t m_lock;
#endif
};


class AutoLock
{
public:
	AutoLock(Lock * pMutex)
	{
		m_pMutex=pMutex;
		pMutex->Acquire();
	};
	~AutoLock()
	{
		m_pMutex->Release();
	};
private:
	Lock * m_pMutex;
};

#endif
