#ifndef ZTC_CONTAINER_ZCONTAINERFUNCTIONPOOL_HPP
#define ZTC_CONTAINER_ZCONTAINERFUNCTIONPOOL_HPP

#include "ZDuo.hpp"
#include "../include/ZTypeOp.hpp"

namespace ZTC
{
	//template <typename T1, typename T>
	//	inline ZDuo<T1, T2> MakeDuo(const T1& value1, const T2& value2)
	//	{
	//		return ZDuo<T1, T2>(value1, value2);
	//	}
	/*******************ZDuoT域类型函数***Begin*****************/
	template<int N, typename T>
	class ZDuoT
	{
	public:
		typedef void ResultT;
	};

	template<typename A, typename B>
	class ZDuoT <1, ZDuoT<A, B> >
	{
	public:
		typedef A ResultT;
	};

	template<typename A, typename B>
	class ZDuoT <2, ZDuoT<A, B> >
	{
	public:
		typedef B ResultT;
	};

	template <int N, typename A, typename B, typename C>
	class ZDuoT<N, ZDuo<A, ZDuo<B,C> > >
	{
	public:
		typedef typename ZDuoT<N - 1, ZDuo<B,C> >::ResultT ResultT;
	};

	template <typename A, typename B, typename C>
	class ZDuoT<1, ZDuo<A, ZDuo<B,C> > >
	{
	public:
		typedef A ResultT;
	};

	template <typename A, typename B, typename C>
	class ZDuoT<2, ZDuoT<A, ZDuoT<B,C> > >
	{
	public:
		typedef B ResultT;
	};
	/*******************ZDuoT域 类型函数***End*****************/

	/*******************ZDuoT域 值函数***End*****************/

	/*******************ZDuoT域 值函数***End*****************/
}
#endif // ZTC_CONTAINER_ZCONTAINERFUNCTIONPOOL_HPP