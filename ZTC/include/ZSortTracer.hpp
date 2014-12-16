/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZSortTracer.h
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.8.13 21:28:19
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.8.13 21:28:19
*/

#ifndef ZTC_ZSORTTRACER_H
#define ZTC_ZSORTTRACER_H

#include <iostream>

namespace ZTC
{
	class ZSortTracer
	{
	private:
		int value; //被排序的整数值
		int generation; //产生拷贝的份数
		static long n_created; //调用构造函数的次数
		static long n_destroyed; //调用析构函数的次数
		static long n_assigned; //赋值的次数
		static long n_compared; //比较的次数
		static long n_max_live; //现存对象的最大个数
	
		//重新计算现存对象的最大个数
		static void update_max_live()
		{
			if(n_created - n_destroyed > n_max_live)
			{
				n_max_live = n_created - n_destroyed;
			}
		}

	public:
		static long createions()
		{
			return n_created;
		}

		static long destructions()
		{
			return n_destroyed;
		}

		static long assignments()
		{
			return n_assigned;
		}

		static long comparisons()
		{
			return n_compared;
		}

		static long max_live()
		{
			return n_max_live;
		}

	public:
		ZSortTracer(int v = 0):value(v), generation(1)
		{
			++n_created;
			update_max_live();
			std::cerr<<"ZSortTracer # "<< n_created
				<<", created generation "<< generation
				<<" (total: "<<n_created - n_destroyed
				<<")\n";
		}

		ZSortTracer(ZSortTracer const & other):value(other.value), generation(other.generation + 1)
		{
			++n_created;
			update_max_live();
			std::cerr<<"ZSortTracer # "<< n_created
				<<", copied as generation "<< generation
				<<" (total: "<<n_created - n_destroyed
				<<")\n";
		}

		~ZSortTracer()
		{
			++n_destroyed;
			update_max_live();
			std::cerr<<"ZSortTracer generation  "<< generation
				<<", destroy (total:  "<<n_created - n_destroyed
				<<")\n";
		}

		ZSortTracer & operator=(ZSortTracer const &other)
		{
			++n_assigned;
			update_max_live();
			std::cerr<<"ZSortTracer  assignment # "<< n_assigned
				<<", (generation  "<< generation
				<<" = "<<other.value
				<<")\n";
			value = other.value;
			return *this;
		}

		friend bool operator<(ZSortTracer const& one, ZSortTracer const& two)
		{
			++n_compared;
			std::cerr<<"ZSortTracer  comparison # "<< n_compared
				<<", (generation "<< one.generation
				<<" < "<<two.generation
				<<")\n";
			return one.value < two.value;
		}

		int val() const
		{
			return value;
		}
	};

	long ZSortTracer::n_created = 0;
	long ZSortTracer::n_destroyed = 0;
	long ZSortTracer::n_max_live = 0;
	long ZSortTracer::n_assigned = 0;
	long ZSortTracer::n_compared = 0;
}


#endif //ZTC_ZSORTTRACER_H