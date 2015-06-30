#ifndef ZTC__INCLUDE__ZOBSERVER_HPP
#define ZTC__INCLUDE__ZOBSERVER_HPP

#include <vector>
#include <algorithm>
//#include "ZLocker.hpp"

using std::vector;

namespace ZTC
{
	typedef void (*pObserverCallBackFun)(void *);

	template <typename ParamType>
	class ZObserver
	{
	public:
		virtual ~ZObserver(){}
		virtual void notifedMe(const ParamType *) = 0;
	};

	template <typename ParamType>
	class ZSubject
	{
	public:
		virtual ~ZSubject(){}
		virtual void setNotifedData(const ParamType *) = 0;

		void addSubjectFun(pObserverCallBackFun fun)
		{
			m_toBeNotifedFun.push_back(fun);
		}
		void removeSubjectFun(pObserverCallBackFun fun)
		{
			//lock
			//m_removeLocker.lock();
			typename vector<pObserverCallBackFun>::iterator iter = std::find(m_toBeNotifedFun.begin(), m_toBeNotifedFun.end(), fun);
			if(iter != m_toBeNotifedFun.end())
			{
				m_toBeNotifedFun.erase(iter);
			}
			//m_removeLocker.unlock();
			//unlock
		}

		void addSubjectObj(const ZObserver<ParamType> * obj)
		{
			m_toBeNotifedObj.push_back(const_cast<ZObserver<ParamType> *>(obj));
		}
		void removeSubjectObj(const ZObserver<ParamType> *obj)
		{
			//lock
			//m_removeLocker.lock();
			typename vector<ZObserver<ParamType> *>::iterator iter = std::find(m_toBeNotifedObj.begin(), m_toBeNotifedObj.end(), obj);			
			if(iter != m_toBeNotifedObj.end())
			{
				m_toBeNotifedObj.erase(iter);
			}
			//m_removeLocker.unlock();
			//unlock
		}

		void notifedAllObserver()
		{
			for(typename vector<pObserverCallBackFun>::const_iterator iter = m_toBeNotifedFun.begin();
				iter != m_toBeNotifedFun.end(); ++iter)
			{
				(*iter)((void *)&m_data);
			}

			for(typename vector<ZObserver<ParamType> *>::const_iterator iter = m_toBeNotifedObj.begin();
				iter != m_toBeNotifedObj.end(); ++iter)
			{
				(*iter)->notifedMe(&m_data);
			}
		}
	protected:
		ParamType m_data;
	private:
		vector<pObserverCallBackFun> m_toBeNotifedFun;
		vector<ZObserver<ParamType> *> m_toBeNotifedObj;
		//ZLocker m_removeLocker;
	};
}

#endif //ZTC__INCLUDE__ZOBSERVER_HPP
