/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZDelegationImp.hpp
* File Identifier :
* Abstract        :	用法和例子参见testDelegation.h 测试用例
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.2.25 22:33:34
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.2.25 22:33:34
*/
#ifndef ZTC_INCLUDE_ZDELEGATIONIMP_HPP
#define ZTC_INCLUDE_ZDELEGATIONIMP_HPP

#include "ZMacroDefine.h"
#include "ZDelegation.hpp"

#include <algorithm>

BEGIN_ZTC_NAMESPACE 
	//-----
//--@ 零个参数的委托
template <typename ReType>
class ZDelegationImp0
{
	typedef typename vector<ZDelegationBase0<ReType> *>::iterator DelegationBaseIter;
	typedef typename vector<ZDelegationBase0<ReType> *>::const_iterator DelegationBaseConstIter;
public:
	~ZDelegationImp0()
	{
		removeAll();
	}

	template <typename ObjType>
	bool pushBack(ObjType* pObj, ReType (ObjType::*pFunc)())
	{
		if(isHas(pObj, pFunc))
			return false;
		ZDelegation0<ObjType, ReType> *one = new ZDelegation0<ObjType, ReType>(pObj, pFunc);
		m_delegation.push_back(one);
		return true;
	}

	bool pushBack(ReType (*pFunc)())
	{
		if(isHas(pFunc))
			return false;
		ZDelegation0<void, ReType> *one = new ZDelegation0<void, ReType>(pFunc);
		m_delegation.push_back(one);
		return true;
	}

	template <typename ObjType>
	bool isHas(ObjType* pObj, ReType (ObjType::*pFunc)())
	{
		if(find(pObj, pFunc) != m_delegation.end())
			return true;
		else
			return false;
	}

	bool isHas(ReType (*pFunc)())
	{
		if(find(pFunc) != m_delegation.end())
			return true;
		else
			return false;
	}

	void invoke()
	{
		for(DelegationBaseIter iter = m_delegation.begin();	iter != m_delegation.end(); ++iter)
			(*iter)->invoke();
	}

	template <typename ObjType>
	void remove(ObjType *pObj, ReType (ObjType::*pFunc)())
	{
		DelegationBaseIter iter = find(pObj, pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			m_delegation.erase(iter);
			//unlock
		}
	}

	void remove(ReType (*pFunc)())
	{
		DelegationBaseIter iter = find(pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			m_delegation.erase(iter);
			//unlock
		}	
	}

	void removeAll()
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			if(*iter != NULL)
			{
				delete *iter;
				*iter = NULL;
			}
		}
		m_delegation.erase(m_delegation.begin(), m_delegation.end());
		//m_delegation.swap(vector<ZDelegationBase0<ReType> *>());
	}

	std::size_t numDelegation() const
	{
		return m_delegation.size();
	}

	bool empty() const
	{
		return m_delegation.empty();
	}

private:
	template <typename ObjType>
	DelegationBaseIter find(ObjType* pObj, ReType (ObjType::*pFunc)())
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation0<ObjType, ReType> * pDelegation = dynamic_cast<ZDelegation0<ObjType, ReType> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pObj, pFunc))
				return iter;
		}
		return m_delegation.end();
	}

	DelegationBaseIter find(ReType (*pFunc)())
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation0<void, ReType> * pDelegation = dynamic_cast<ZDelegation0<void, ReType> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pFunc))
				return iter;
		}		
		return m_delegation.end();
	}


private:
	vector<ZDelegationBase0<ReType> *> m_delegation;
};	

//--@ 一个参数的委托
template <typename ReType, typename ParamType1>
class ZDelegationImp1
{
	typedef typename vector<ZDelegationBase1<ReType, ParamType1> *>::iterator DelegationBaseIter;
	typedef typename vector<ZDelegationBase1<ReType, ParamType1> *>::const_iterator DelegationBaseConstIter;
public:
	~ZDelegationImp1()
	{
		removeAll();
	}

	template <typename ObjType>
	bool pushBack(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1))
	{
		if(isHas(pObj, pFunc))
			return false;
		ZDelegation1<ObjType, ReType, ParamType1> *one = new ZDelegation1<ObjType, ReType, ParamType1>(pObj, pFunc);
		m_delegation.push_back(one);
		return true;
	}

	bool pushBack(ReType (*pFunc)(ParamType1))
	{
		if(isHas(pFunc))
			return false;
		ZDelegation1<void, ReType, ParamType1> *one = new ZDelegation1<void, ReType, ParamType1>(pFunc);
		m_delegation.push_back(one);
		return true;
	}

	template <typename ObjType>
	bool isHas(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1))
	{
		if(find(pObj, pFunc) != m_delegation.end())
			return true;
		else
			return false;
	}

	bool isHas(ReType (*pFunc)(ParamType1))
	{
		if(find(pFunc) != m_delegation.end())
			return true;
		else
			return false;
	}

	void invoke(ParamType1 param1)
	{
		for(DelegationBaseIter iter = m_delegation.begin(); iter != m_delegation.end(); ++iter)
			(*iter)->invoke(param1);
	}

	template <typename ObjType>
	void remove(ObjType *pObj, ReType (ObjType::*pFunc)(ParamType1))
	{
		DelegationBaseIter iter = find(pObj, pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			*iter = NULL;
			m_delegation.erase(iter);
			//unlock
		}
	}

	void remove(ReType (*pFunc)(ParamType1))
	{
		DelegationBaseIter iter = find(pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			*iter = NULL;
			m_delegation.erase(iter);
			//unlock
		}
	}

	void removeAll()
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			if(*iter != NULL)
			{
				delete *iter;
				*iter = NULL;
			}
		}
		m_delegation.erase(m_delegation.begin(), m_delegation.end());
		//m_delegation.swap(vector<ZDelegationBase1<ReType, ParamType1> *>());
	}

	std::size_t numDelegation() const
	{
		return m_delegation.size();
	}

	bool empty() const
	{
		return m_delegation.empty();
	}
private:
	template <typename ObjType>
	DelegationBaseIter find(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1))
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation1<ObjType, ReType, ParamType1> * pDelegation = dynamic_cast<ZDelegation1<ObjType, ReType, ParamType1> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pObj, pFunc))
				return iter;
		}
		return m_delegation.end();
	}

	DelegationBaseIter find(ReType (*pFunc)(ParamType1))
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation1<void, ReType, ParamType1> * pDelegation = dynamic_cast<ZDelegation1<void, ReType, ParamType1> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pFunc))
				return iter;
		}		
		return m_delegation.end();
	}
private:
	vector<ZDelegationBase1<ReType, ParamType1> *> m_delegation;
};

//--@ 两个参数的委托
template <typename ReType, typename ParamType1, typename ParamType2>
class ZDelegationImp2
{
	typedef typename vector<ZDelegationBase2<ReType, ParamType1, ParamType2> *>::iterator DelegationBaseIter;
	typedef typename vector<ZDelegationBase2<ReType, ParamType1, ParamType2> *>::const_iterator DelegationBaseConstIter;
public:
	~ZDelegationImp2()
	{
		removeAll();
	}

	template <typename ObjType>
	bool pushBack(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2))
	{
		if(find(pObj, pFunc) != m_delegation.end())
			return false;
		ZDelegation2<ObjType, ReType, ParamType1, ParamType2> *one = new ZDelegation2<ObjType, ReType, ParamType1, ParamType2>(pObj, pFunc);
		m_delegation.push_back(one);
		return true;
	}

	bool pushBack(ReType (*pFunc)(ParamType1, ParamType2))
	{
		if(find(pFunc) != m_delegation.end())
			return false;
		ZDelegation2<void, ReType, ParamType1, ParamType2> *one = new ZDelegation2<void, ReType, ParamType1, ParamType2>(pFunc);
		m_delegation.push_back(one);
		return true;
	}

	void invoke(ParamType1 param1, ParamType2 param2)
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
			(*iter)->invoke(param1, param2);
	}

	template <typename ObjType>
	void remove(ObjType *pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2))
	{
		DelegationBaseIter iter = find(pObj, pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			m_delegation.erase(iter);
			//unlock
		}
	}

	void remove(ReType (*pFunc)(ParamType1, ParamType2))
	{
		DelegationBaseIter iter = find(pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			m_delegation.erase(iter);
			//unlock
		}	
	}

	void removeAll()
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			if(*iter != NULL)
			{
				delete *iter;
				*iter = NULL;
			}
		}
		m_delegation.erase(m_delegation.begin(), m_delegation.end());
		//m_delegation.swap(vector<ZDelegationBase2<ReType, ParamType1, ParamType2> *>());
	}

	std::size_t numDelegation() const
	{
		return m_delegation.size();
	}

	bool empty() const
	{
		return m_delegation.empty();
	}
private:
	template <typename ObjType>
	DelegationBaseIter find(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2))
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation2<ObjType, ReType, ParamType1, ParamType2> * pDelegation = dynamic_cast<ZDelegation2<ObjType, ReType, ParamType1, ParamType2> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pObj, pFunc))
				return iter;
		}
		return m_delegation.end();
	}

	DelegationBaseIter find(ReType (*pFunc)(ParamType1, ParamType2))
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation2<void, ReType, ParamType1, ParamType2> * pDelegation = dynamic_cast<ZDelegation2<void, ReType, ParamType1, ParamType2> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pFunc))
				return iter;
		}		
		return m_delegation.end();
	}

private:
	vector<ZDelegationBase2<ReType, ParamType1, ParamType2> *> m_delegation;
};

//--@ 三个参数的委托
template <typename ReType, typename ParamType1, typename ParamType2, typename ParamType3>
class ZDelegationImp3
{
	typedef typename vector<ZDelegationBase3<ReType, ParamType1, ParamType2, ParamType3> *>::iterator DelegationBaseIter;
	typedef typename vector<ZDelegationBase3<ReType, ParamType1, ParamType2, ParamType3> *>::const_iterator DelegationBaseConstIter;
public:
	~ZDelegationImp3()
	{
		removeAll();
	}

	template <typename ObjType>
	bool pushBack(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		if(find(pObj, pFunc) != m_delegation.end())
			return false;
		ZDelegation3<ObjType, ReType, ParamType1, ParamType2, ParamType3> *one = new ZDelegation3<ObjType, ReType, ParamType1, ParamType2, ParamType3>(pObj, pFunc);
		m_delegation.push_back(one);
		return true;
	}

	bool pushBack(ReType (*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		if(find(pFunc) != m_delegation.end())
			return false;
		ZDelegation3<void, ReType, ParamType1, ParamType2, ParamType3> *one = new ZDelegation3<void, ReType, ParamType1, ParamType2, ParamType3>(pFunc);
		m_delegation.push_back(one);
		return true;
	}

	void invoke(ParamType1 param1, ParamType2 param2, ParamType3 param3)
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
			(*iter)->invoke(param1, param2, param3);
	}

	template <typename ObjType>
	void remove(ObjType *pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		DelegationBaseIter iter = find(pObj, pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			m_delegation.erase(iter);
			//unlock
		}
	}

	void remove(ReType (*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		DelegationBaseIter iter = find(pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			m_delegation.erase(iter);
			//unlock
		}
	}

	void removeAll()
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			if(*iter != NULL)
			{
				delete *iter;
				*iter = NULL;
			}
		}
		m_delegation.erase(m_delegation.begin(), m_delegation.end());
		//m_delegation.swap(vector<ZDelegationBase3<ReType, ParamType1, ParamType2, ParamType3> *>());
	}

	std::size_t numDelegation() const
	{
		return m_delegation.size();
	}

	bool empty() const
	{
		return m_delegation.empty();
	}
private:
	template <typename ObjType>
	DelegationBaseIter find(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation3<ObjType, ReType, ParamType1, ParamType2, ParamType3> * pDelegation = dynamic_cast<ZDelegation3<ObjType, ReType, ParamType1, ParamType2, ParamType3> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pObj, pFunc))
				return iter;
		}
		return m_delegation.end();
	}

	DelegationBaseIter find(ReType (*pFunc)(ParamType1, ParamType2, ParamType3))
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation3<void, ReType, ParamType1, ParamType2, ParamType3> * pDelegation = dynamic_cast<ZDelegation3<void, ReType, ParamType1, ParamType2, ParamType3> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pFunc))
				return iter;
		}		
		return m_delegation.end();
	}

private:
	vector<ZDelegationBase3<ReType, ParamType1, ParamType2, ParamType3> *> m_delegation;
};

//--@ 四个参数的委托
template <typename ReType, typename ParamType1, typename ParamType2, typename ParamType3, typename ParamType4>
class ZDelegationImp4
{
	typedef typename vector<ZDelegationBase4<ReType, ParamType1, ParamType2, ParamType3, ParamType4> *>::iterator DelegationBaseIter;
	typedef typename vector<ZDelegationBase4<ReType, ParamType1, ParamType2, ParamType3, ParamType4> *>::const_iterator DelegationBaseConstIter;
public:
	~ZDelegationImp4()
	{
		removeAll();
	}

	template <typename ObjType>
	bool pushBack(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		if(find(pObj, pFunc) != m_delegation.end())
			return false;
		ZDelegation4<ObjType, ReType, ParamType1, ParamType2, ParamType3, ParamType4> *one = new ZDelegation4<ObjType, ReType, ParamType1, ParamType2, ParamType3, ParamType4>(pObj, pFunc);
		m_delegation.push_back(one);
		return true;
	}

	bool pushBack(ReType (*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		if(find(pFunc) != m_delegation.end())
			return false;
		ZDelegation4<void, ReType, ParamType1, ParamType2, ParamType3, ParamType4> *one = new ZDelegation4<void, ReType, ParamType1, ParamType2, ParamType3, ParamType4>(pFunc);
		m_delegation.push_back(one);
		return true;
	}

	void invoke(ParamType1 param1, ParamType2 param2, ParamType3 param3, ParamType4 param4)
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
			(*iter)->invoke(param1, param2, param3, param4);
	}

	template <typename ObjType>
	void remove(ObjType *pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		DelegationBaseIter iter = find(pObj, pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			m_delegation.erase(iter);
			//unlock
		}
	}

	void remove(ReType (*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		DelegationBaseIter iter = find(pFunc);
		if(iter != m_delegation.end())
		{
			//lock
			delete *iter;
			m_delegation.erase(iter);
			//unlock
		}
	}

	void removeAll()
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			if(*iter != NULL)
			{
				delete *iter;
				*iter = NULL;
			}
		}
		m_delegation.erase(m_delegation.begin(), m_delegation.end());
		//m_delegation.swap(vector<ZDelegationBase4<ReType, ParamType1, ParamType2, ParamType3, ParamType4> *>());
	}

	std::size_t numDelegation() const
	{
		return m_delegation.size();
	}

	bool empty() const
	{
		return m_delegation.empty();
	}
private:
	template <typename ObjType>
	DelegationBaseIter find(ObjType* pObj, ReType (ObjType::*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation4<ObjType, ReType, ParamType1, ParamType2, ParamType3, ParamType4> * pDelegation = dynamic_cast<ZDelegation4<ObjType, ReType, ParamType1, ParamType2, ParamType3, ParamType4> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pObj, pFunc))
				return iter;
		}
		return m_delegation.end();
	}

	DelegationBaseIter find(ReType (*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
	{
		for(DelegationBaseIter iter = m_delegation.begin();
			iter != m_delegation.end(); ++iter)
		{
			ZDelegation4<void, ReType, ParamType1, ParamType2, ParamType3, ParamType4> * pDelegation = dynamic_cast<ZDelegation4<void, ReType, ParamType1, ParamType2, ParamType3, ParamType4> *>(*iter);
			if(pDelegation != NULL && pDelegation->equal(pFunc))
				return iter;
		}		
		return m_delegation.end();
	}
private:
	vector<ZDelegationBase4<ReType, ParamType1, ParamType2, ParamType3, ParamType4> *> m_delegation;
};

END_ZTC_NAMESPACE
#endif //ZTC_INCLUDE_ZDELEGATIONIMP_HPP
