/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZSingle.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.7.27 21:20:43
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.7.27 21:20:43
*/
#ifndef ZTC_ZSINGLETON_H
#define ZTC_ZSINGLETON_H

#include "ZUncopy.h"

namespace ZTC
{
	template <typename T>
	class ZSingleton :public ZUncopy
	{
	public:
		static ZSingleton * getInstance()
		{
			static ZSingleton singleton;
			create_object.do_nothing();
			return &singleton;
		}
	private:
		struct ObjectCreate
		{
			ObjectCreate()
			{
				ZSingleton<T>::getInstance();
			}
			inline void do_nothing() const{}
		};
		static ObjectCreate create_object;
	};

	template<typename Type>
	typename ZSingleton<Type>::ObjectCreate  ZSingleton<Type>::create_object;
}
#endif //ZTC_ZSINGLETON_H