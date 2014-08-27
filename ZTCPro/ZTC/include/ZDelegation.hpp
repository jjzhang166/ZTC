#ifndef ZTC__INCLUDE__ZDELEGATION_HPP
#define ZTC__INCLUDE__ZDELEGATION_HPP

#include <stdio.h>
#include <vector>

using std::vector;

namespace ZTC
{
	/*---
	*  零个参数的委托
	*/
	template<typename REType>
	class ZDelegationBase0
	{
	public:
		~ZDelegationBase0(){}
		virtual REType invoke() = 0;
	};

	template <typename OBJType, typename REType = void>
	class ZDelegation0 : public ZDelegationBase0<REType>
	{
	public:
		ZDelegation0(OBJType* pObj, REType (OBJType::*pFunc)()) : m_pObj(pObj), m_pFunc(pFunc)
		{
		}

		virtual REType invoke()
		{
			return (m_pObj->*m_pFunc)();
		}

		bool equal(OBJType* pObj, REType (OBJType::*pFunc)())
		{
			if(pObj == m_pObj && pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		OBJType* m_pObj;
		REType (OBJType::* m_pFunc)();
	};

	template <typename REType>
	class ZDelegation0<void, REType> : public ZDelegationBase0<REType>
	{
	public:
		ZDelegation0( REType (*pFunc)()) : m_pFunc(pFunc)
		{
		}

		virtual REType invoke()
		{
			return (*m_pFunc)();
		}

		bool equal(REType (*pFunc)())
		{
			if(pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		REType (*m_pFunc)();
	};

	

	/*---
	*  1个参数的委托
	*/
	template<typename REType, typename ParamType1>
	class ZDelegationBase1
	{
	public:
		~ZDelegationBase1(){}
		virtual REType invoke(ParamType1) = 0;
	};

	template <typename OBJType, typename REType, typename ParamType1>
	class ZDelegation1: public ZDelegationBase1<REType, ParamType1>
	{
	public:
		ZDelegation1(OBJType* pObj, REType (OBJType::*pFunc)(ParamType1)) : m_pObj(pObj), m_pFunc(pFunc)
		{
		}

		virtual REType invoke(ParamType1 p1)
		{
			return (m_pObj->*m_pFunc)(p1);
		}

		bool equal(OBJType* pObj, REType (OBJType::*pFunc)(ParamType1))
		{
			if(pObj == m_pObj && pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		OBJType* m_pObj;
		REType (OBJType::* m_pFunc)(ParamType1);
	};

	template <typename REType, typename ParamType1>
	class ZDelegation1<void, REType, ParamType1> : public ZDelegationBase1<REType, ParamType1>
	{
	public:
		ZDelegation1( REType (*pFunc)(ParamType1)) : m_pFunc(pFunc)
		{
		}

		virtual REType invoke(ParamType1 p1)
		{
			return (*m_pFunc)(p1);
		}

		bool equal(REType (*pFunc)(ParamType1))
		{
			if(pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		REType (*m_pFunc)(ParamType1);
	};

	

	/*---
	*  2个参数的委托
	*/
	template<typename REType, typename ParamType1, typename ParamType2>
	class ZDelegationBase2
	{
	public:
		~ZDelegationBase2(){}
		virtual REType invoke(ParamType1, ParamType2) = 0;
	};

	template <typename OBJType, typename REType, typename ParamType1, typename ParamType2>
	class ZDelegation2 : public ZDelegationBase2<REType, ParamType1, ParamType2>
	{
	public:
		ZDelegation2(OBJType* pObj, REType (OBJType::*pFunc)(ParamType1, ParamType2)) : m_pObj(pObj), m_pFunc(pFunc)
		{
		}

		virtual REType invoke(ParamType1 p1, ParamType2 p2)
		{
			return (m_pObj->*m_pFunc)(p1, p2);
		}

		bool equal(OBJType* pObj, REType (OBJType::*pFunc)(ParamType1, ParamType2))
		{
			if(pObj == m_pObj && pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		OBJType* m_pObj;
		REType (OBJType::* m_pFunc)(ParamType1, ParamType2);
	};

	template <typename REType, typename ParamType1, typename ParamType2>
	class ZDelegation2<void, REType, ParamType1, ParamType2> : public ZDelegationBase2<REType, ParamType1, ParamType2>
	{
	public:
		ZDelegation2( REType (*pFunc)(ParamType1, ParamType2)) : m_pFunc(pFunc)
		{
		}

		virtual REType invoke(ParamType1 p1, ParamType2 p2)
		{
			return (*m_pFunc)(p1, p2);
		}

		bool equal(REType (*pFunc)(ParamType1, ParamType2))
		{
			if(pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		REType (*m_pFunc)(ParamType1, ParamType2);
	};

	
	/*---
	*  3个参数的委托
	*/
	template<typename REType, typename ParamType1, typename ParamType2, typename ParamType3>
	class ZDelegationBase3
	{
	public:
		~ZDelegationBase3(){}
		virtual REType invoke(ParamType1, ParamType2, ParamType3) = 0;
	};

	template <typename OBJType, typename REType, typename ParamType1, typename ParamType2, typename ParamType3>
	class ZDelegation3 : public ZDelegationBase3<REType, ParamType1, ParamType2, ParamType3>
	{
	public:
		ZDelegation3(OBJType* pObj, REType (OBJType::*pFunc)(ParamType1, ParamType2, ParamType3)) : m_pObj(pObj), m_pFunc(pFunc)
		{
		}

		virtual REType invoke(ParamType1 p1, ParamType2 p2, ParamType3 p3)
		{
			return (m_pObj->*m_pFunc)(p1, p2, p3);
		}

		bool equal(OBJType* pObj, REType (OBJType::*pFunc)(ParamType1, ParamType2, ParamType3))
		{
			if(pObj == m_pObj && pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		OBJType* m_pObj;
		REType (OBJType::* m_pFunc)(ParamType1, ParamType2, ParamType3);
	};

	template <typename REType, typename ParamType1, typename ParamType2, typename ParamType3>
	class ZDelegation3<void, REType, ParamType1, ParamType2, ParamType3> : public ZDelegationBase3<REType, ParamType1, ParamType2, ParamType3>
	{
	public:
		ZDelegation3( REType (*pFunc)(ParamType1, ParamType2, ParamType3)) : m_pFunc(pFunc)
		{
		}

		virtual REType invoke(ParamType1 p1, ParamType2 p2, ParamType3 p3)
		{
			return (*m_pFunc)(p1, p2, p3);
		}

		bool equal(REType (*pFunc)(ParamType1, ParamType2, ParamType3))
		{
			if(pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		REType (*m_pFunc)(ParamType1, ParamType2, ParamType3);
	};

	

	/*---
	*  4个参数的委托
	*/
	template<typename REType, typename ParamType1, typename ParamType2, typename ParamType3, typename ParamType4>
	class ZDelegationBase4
	{
	public:
		~ZDelegationBase4(){}
		virtual REType invoke(ParamType1, ParamType2, ParamType3, ParamType4) = 0;
	};

	template <typename OBJType, typename REType, typename ParamType1, typename ParamType2, typename ParamType3, typename ParamType4>
	class ZDelegation4 : public ZDelegationBase4<REType, ParamType1, ParamType2, ParamType3, ParamType4>
	{
	public:
		ZDelegation4(OBJType* pObj, REType (OBJType::*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4)) : m_pObj(pObj), m_pFunc(pFunc)
		{
		}

		virtual REType invoke(ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4)
		{
			return (m_pObj->*m_pFunc)(p1, p2, p3, p4);
		}

		bool equal(OBJType* pObj, REType (OBJType::*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
		{
			if(pObj == m_pObj && pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		OBJType* m_pObj;
		REType (OBJType::* m_pFunc)(ParamType1, ParamType2, ParamType3, ParamType4);
	};

	template <typename REType, typename ParamType1, typename ParamType2, typename ParamType3, typename ParamType4>
	class ZDelegation4<void, REType, ParamType1, ParamType2, ParamType3, ParamType4> : public ZDelegationBase4<REType, ParamType1, ParamType2, ParamType3, ParamType4>
	{
	public:
		ZDelegation4( REType (*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4)) : m_pFunc(pFunc)
		{
		}

		virtual REType invoke(ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4)
		{
			return (*m_pFunc)(p1, p2, p3, p4);
		}

		bool equal(REType (*pFunc)(ParamType1, ParamType2, ParamType3, ParamType4))
		{
			if(pFunc == m_pFunc)
				return  true;
			else
				return false;
		}

	private:
		REType (*m_pFunc)(ParamType1, ParamType2, ParamType3, ParamType4);
	};


}

#endif //ZTC__INCLUDE__ZDELEGATION_HPP