/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZClientTimer.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.10.26 19:39:18
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.10.26 19:39:18
*/
#ifndef ZTC_CLIENTNET_ZCLIENTTIMER_H
#define ZTC_CLIENTNET_ZCLIENTTIMER_H

#include "../include/ZMacroDefine.h"
#include "ZConfig.h"

BEGIN_ZTC_NAMESPACE

//获取ms时间
ZTC_API uint32_t get_time_ms();
ZTC_API void sleep_ms(int ms);

class ZTimeAxis;
class ZTimer;

// 定时器函数对象
class ZITimerFunctor
{
public:
	virtual void operator()(void* user_data) = 0;
};

template<typename T>
class Timer_functor:public ZITimerFunctor
{
public:
	typedef void (T::*Timer_fun)(void*);
	Timer_functor(T* pObj, Timer_fun pFun):m_obj(pObj), m_fun(pFun)
	{
	}

	void operator()(void* user_data)
	{
		(m_obj->*m_fun)(user_data);
	}

private:
	T* m_obj;
	Timer_fun m_fun;
};

// 定时器
class ZTC_CLASS ZTimer
{
public:
	friend class ZTimeAxis;
	enum State
	{
		WAIT_SET,
		NORMAL,
		WAIT_KILL,
	};
	template<typename T>
	ZTimer(T* pObj, void (T::*pFun)(void*), uint32_t interval, uint32_t times = -1, void* user_data = NULL)
		:m_state(WAIT_SET), m_timer_id(INVALID_VALUE), m_interval(interval), m_times(times), m_user_data(user_data)
	{
		m_functor = new Timer_functor<T>(pObj, pFun);
	}
	void operator()()
	{
		(m_functor->operator())(m_user_data);
	}
	~ZTimer()
	{
		delete m_functor;
	}
private:
	State m_state;
	uint32_t m_timer_id;
	uint32_t m_interval;
	uint32_t m_times;
	void* m_user_data;
	ZITimerFunctor* m_functor;
	uint32_t m_last_update;
};

//时间轴接口
class ZITimeAxis
{
public:
	virtual ~ZITimeAxis(){}
	virtual uint32_t set_timer(ZTimer* pTimer) = 0;
	virtual int kill_timer(uint32_t timer_id) = 0;
	virtual int update() = 0;
};

ZTC_API ZITimeAxis* create_ZTimeAxis(uint32_t update_frequency);
ZTC_API void release_ZTimeAxis(ZITimeAxis* pTimeAxis);
	
END_ZTC_NAMESPACE

#endif //ZTC_CLIENTNET_ZCLIENTTIMER_H