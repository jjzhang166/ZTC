/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZIfThenElse.hpp
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.2.17 22:54:26
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.2.17 22:54:26
*/

#ifndef ZTC__INCLUDE__ZIFTHENELSE_HPP
#define ZTC__INCLUDE__ZIFTHENELSE_HPP

#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE

template <bool bo, typename T1, typename T2>
class IfThenElse;

template <typename T1, typename T2>
class IfThenElse<true, T1, T2>
{
public:
	typedef T1 Result;
};

template <typename T1, typename T2>
class IfThenElse<false, T1, T2>
{
public:
	typedef T2 Result;
};



template <typename T>
class IsClassT
{
private:
	typedef char One;
	typedef struct { char a[2]; } Two;
	
	template <typename C>
	static One test(int C::*);
	
	template <typename C>
	static Two test(...);

public:
	enum {Yes = sizeof(IsClassT<T>::test<T>(0)) == 1};
	enum {No = !Yes};
};



template <typename T>
class RParam
{
public:
	typedef typename IfThenElse<IsClassT<T>::No, T, T const&>::Result Type;
};

END_ZTC_NAMESPACE
#endif //ZTC__INCLUDE__ZIFTHENELSE_HPP