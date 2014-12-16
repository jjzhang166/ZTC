/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZEvent.hpp
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.2.25 22:13:10
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.2.25 22:13:10
*/
#ifndef ZTC_INCLUDE_ZEVENT_HPP
#define ZTC_INCLUDE_ZEVENT_HPP

#include "ZMacroDefine.h"
#include "ZDelegationImp.hpp"

BEGIN_ZTC_NAMESPACE
//--@ 零个参数的事件
template <typename RetType>
class ZEvent0 : private ZDelegationImp0<RetType>
{
public:
	template<typename OBJType>
	bool connect(OBJType *pObj, RetType (OBJType::*pFunc)())
	{
		return ZDelegationImp0<RetType>::pushBack(pObj, pFunc);
	}

	bool connect(RetType (*pFunc)())
	{
		return ZDelegationImp0<RetType>::pushBack(pFunc);
	}

	template<typename OBJType>
	void disconnect(OBJType *pObj, RetType (OBJType::*pFunc)())
	{
		 ZDelegationImp0<RetType>::remove(pObj, pFunc);
	}

	void disconnect(RetType (*pFunc)())
	{
		ZDelegationImp0<RetType>::remove(pFunc);
	}

	void operator() ()
	{
		ZDelegationImp0<RetType>::invoke();
	}

	std::size_t numSlots() const
	{
		return ZDelegationImp0<RetType>::numDelegation();
	}

	bool empty() const
	{
		return ZDelegationImp0<RetType>::empty();
	}
};

//---@ 一个参数的事件
template <typename RetType, typename ParamType1>
class ZEvent1 : private ZDelegationImp1<RetType, ParamType1>
{
public:
	template<typename OBJType>
	bool connect(OBJType *pObj, RetType (OBJType::*pFunc)(ParamType1))
	{
		return ZDelegationImp1<RetType, ParamType1>::pushBack(pObj, pFunc);
	}

	bool connect(RetType (*pFunc)(ParamType1))
	{
		return ZDelegationImp1<RetType, ParamType1>::pushBack(pFunc);
	}

	template<typename OBJType>
	void disconnect(OBJType *pObj, RetType (OBJType::*pFunc)(ParamType1))
	{
		ZDelegationImp1<RetType, ParamType1>::remove(pObj, pFunc);
	}

	void disconnect(RetType (*pFunc)(ParamType1))
	{
		ZDelegationImp1<RetType, ParamType1>::remove(pFunc);
	}

	void disconnectAllSlots()
	{
		ZDelegationImp1<RetType, ParamType1>::removeAll();
	}

	void operator() (ParamType1 param1)
	{
		ZDelegationImp1<RetType, ParamType1>::invoke(param1);
	}

	std::size_t numSlots() const
	{
		return ZDelegationImp1<RetType, ParamType1>::numDelegation();
	}

	bool empty() const
	{
		return ZDelegationImp1<RetType, ParamType1>::empty();
	}
};

//---@ 两个参数的事件
template <typename RetType, typename ParamType1, typename ParamType2>
class ZEvent2 : private ZDelegationImp2<RetType, ParamType1, ParamType2>
{
public:
	template<typename OBJType>
	bool connect(OBJType *pObj, RetType (OBJType::*pFunc)(ParamType1, ParamType2))
	{
		return ZDelegationImp2<RetType, ParamType1, ParamType2>::pushBack(pObj, pFunc);
	}

	bool connect(RetType (*pFunc)(ParamType1, ParamType2))
	{
		return ZDelegationImp2<RetType, ParamType1, ParamType2>::pushBack(pFunc);
	}

	template<typename OBJType>
	void disconnect(OBJType *pObj, RetType (OBJType::*pFunc)(ParamType1, ParamType2))
	{
		ZDelegationImp2<RetType, ParamType1, ParamType2>::remove(pObj, pFunc);
	}

	void disconnect(RetType (*pFunc)(ParamType1, ParamType2))
	{
		ZDelegationImp2<RetType, ParamType1, ParamType2>::remove(pFunc);
	}

	void operator() (ParamType1 param1, ParamType2 param2)
	{
		ZDelegationImp2<RetType, ParamType1, ParamType2>::invoke(param1, param2);
	}

	std::size_t numSlots() const
	{
		return ZDelegationImp2<RetType, ParamType1, ParamType2>::numDelegation();
	}

	bool empty() const
	{
		return ZDelegationImp2<RetType, ParamType1, ParamType2>::empty();
	}
};

//---@ 三个参数的事件
template <typename RetType, typename ParamType1, typename ParamType2, typename ParamType3>
class ZEvent3 : private ZDelegationImp3<RetType, ParamType1, ParamType2, ParamType3>
{
public:
	template<typename OBJType>
	bool connect(OBJType *pObj, RetType (OBJType::*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		return  ZDelegationImp3<RetType, ParamType1, ParamType2, ParamType3>::pushBack(pObj, pFunc);
	}

	bool connect(RetType (*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		return ZDelegationImp3<RetType, ParamType1, ParamType2, ParamType3>::pushBack(pFunc);
	}

	template<typename OBJType>
	void disconnect(OBJType *pObj, RetType (OBJType::*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		ZDelegationImp3<RetType, ParamType1, ParamType2, ParamType3>::remove(pObj, pFunc);
	}

	void disconnect(RetType (*pFunc)(ParamType1, ParamType2,  ParamType3))
	{
		ZDelegationImp3<RetType, ParamType1, ParamType2,  ParamType3>::remove(pFunc);
	}

	void operator() (ParamType1 param1, ParamType2 param2,  ParamType3 param3)
	{
		ZDelegationImp3<RetType, ParamType1, ParamType2, ParamType3>::invoke(param1, param2, param3);
	}

	std::size_t numSlots() const
	{
		return ZDelegationImp3<RetType, ParamType1, ParamType2, ParamType3>::numDelegation();
	}

	bool empty() const
	{
		return ZDelegationImp3<RetType, ParamType1, ParamType2, ParamType3>::empty();
	}
};

//---@ 四个参数的事件
template <typename RetType, typename ParamType1, typename ParamType2, typename ParamType3, typename ParamType4>
class ZEvent4 : private ZDelegationImp4<RetType, ParamType1, ParamType2, ParamType3, ParamType4>
{
public:
	template<typename OBJType>
	bool connect(OBJType *pObj, RetType (OBJType::*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		return ZDelegationImp4<RetType, ParamType1, ParamType2, ParamType3, ParamType4>::pushBack(pObj, pFunc);
	}

	bool connect(RetType (*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		return ZDelegationImp4<RetType, ParamType1, ParamType2, ParamType3, ParamType4>::pushBack(pFunc);
	}

	template<typename OBJType>
	void disconnect(OBJType *pObj, RetType (OBJType::*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		 ZDelegationImp4<RetType, ParamType1, ParamType2, ParamType3, ParamType4>::remove(pObj, pFunc);
	}

	void disconnect(RetType (*pFunc)(ParamType1, ParamType2,  ParamType3, ParamType4))
	{
		 ZDelegationImp4<RetType, ParamType1, ParamType2,  ParamType3, ParamType4>::remove(pFunc);
	}

	void operator() (ParamType1 param1, ParamType2 param2,  ParamType3 param3, ParamType4 param4)
	{
		ZDelegationImp4<RetType, ParamType1, ParamType2, ParamType3, ParamType4>::invoke(param1, param2, param3, param4);
	}

	std::size_t numSlots() const
	{
		return ZDelegationImp4<RetType, ParamType1, ParamType2, ParamType3, ParamType4>::numDelegation();
	}

	bool empty() const
	{
		return ZDelegationImp4<RetType, ParamType1, ParamType2, ParamType3, ParamType4>::empty();
	}
};

END_ZTC_NAMESPACE

#endif //ZTC_INCLUDE_ZEVENT_HPP
