#ifndef ZTC_SMARTPTR_ZCOUNTINGPTR_HPP
#define ZTC_SMARTPTR_ZCOUNTINGPTR_HPP

#include "ZCounterPolicy.hpp"
#include "ZObjectPolicy.hpp"

namespace ZTC
{
	template<typename T, 
		typename CounterPolicy = ZSimpleReferenceCount,
		typename ObjectPolicy = ZStandarObjectPolicy >
	class ZCountingPtr : private CounterPolicy, private ObjectPolicy
	{
	public:
		ZCountingPtr(): this->m_pObject(NULL)
		{}

		explicit ZCountingPtr(T * pObject)
		{
			Init(pObject);
		}

		template<class Y>
		explicit ZCountingPtr(Y *_Px):m_pObject(_Px)
		{	
			//Init(_Px);

			if(_Px)
				CounterPolicy::Init(); //重置计数器
		}

		ZCountingPtr(const ZCountingPtr<T, CounterPolicy, ObjectPolicy> &other):
			CounterPolicy((const CounterPolicy&)other),
			ObjectPolicy((const ObjectPolicy&)other)
		{
			m_pObject = other.m_pObject;
			if(m_pObject)
				CounterPolicy::Increment();
		}

		~ZCountingPtr()
		{
			Detach();
		}

		/***
		* 内建指针的赋值运算符
		***/
		ZCountingPtr<T, CounterPolicy, ObjectPolicy>& operator= (T * p)
		{
			assert(p != m_pObject); //计数指针不能指向 *p
			Detach(); //减少计数器值
			m_pObject = p;
			CounterPolicy::Init(); //重置计算器
			return *this;
		}

		ZCountingPtr<T, CounterPolicy, ObjectPolicy>&
			operator= (const ZCountingPtr<T, CounterPolicy, ObjectPolicy>& other)
		{
			if(m_pObject == other.m_pObject)
				return *this;
			Detach(); //减少计数器值
			CounterPolicy::operator=((const CounterPolicy &)other);
			ObjectPolicy::operator=((const ObjectPolicy &)other);
			m_pObject = other.m_object;
			if(m_pObject)
				CounterPolicy::Increment();  //增加计数器值
			return *this;
		}

		T* operator->() const
		{
			return m_pObject;
		}
		T& operator*() const
		{
			return *m_pObject;
		}

		size_t GetCounter()
		{
			return CounterPolicy::GetCounter();
		}
		T* GetPtr() 
		{
			return m_pObject;
		}

		operator bool() const
		{
			return m_pObject != (T*)0;
		}

		friend bool operator== (const ZCountingPtr<T, CounterPolicy, ObjectPolicy> &ptr, const T* p)
		{
			return ptr == p;
		}

		friend bool operator== (const T* p, const ZCountingPtr<T, CounterPolicy, ObjectPolicy> &ptr)
		{
			return p == ptr;
		}

		/*template <typename T1, typename T2, typename CP, typename OP>
		inline bool operator== (const ZCountingPtr<T1, CP, OP> &ptr1, const ZCountingPtr<T2, CP, OP> &ptr2)
		{
			return ptr1.operator->() == ptr2.operator->();
		}
*/
	private:

		void Init(T *pObject)
		{
			if(pObject)
				CounterPolicy::Init(); //重置计数器
			m_pObject = pObject;
		}

		void Detach()
		{
			if(m_pObject)
			{
				CounterPolicy::Decrement(); //计数器减1
				if(CounterPolicy::IsZero()) //判断计数器是否为0，如果为0，释放计数器和对象
				{
					CounterPolicy::Dispose();
					ObjectPolicy::Dispose<T>(m_pObject);
				}
			}
		}

	private:
		T* m_pObject;
	};
};

#endif //ZTC_SMARTPTR_ZCOUNTINGPTR_HPP