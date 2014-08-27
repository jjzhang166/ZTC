/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZBaseMemberPair.hpp
* File Identifier :
* Abstract        :	便于空基类优化
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2014.2.20 20:13:17
*
* Replace Version : 
* Original Author :
* Completion Date : 2014.2.20 20:13:17
*/

#ifndef ZTC__INCLUDE__ZBASEMEMBERPAIR_HPP
#define ZTC__INCLUDE__ZBASEMEMBERPAIR_HPP

#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE

template <typename Base, typename Member>
class ZBaseMemberPair : private Base
{
private:
	Member m_member;

public:
	ZBaseMemberPair(Base const &b, Member const &m): Base(b), m_member(m)
	{}

	Base const& first() const 
	{
		return (Base const&) *this;
	}

	Base& first()
	{
		return (Base&) *this;
	}

	Member const& second() const
	{
		return this->member;
	}

	Member& second()
	{
		return this->member;
	}
};


template <typename Cust>
class Opt
{
private:
	ZBaseMemberPair<Cust, void *> info;
public:
	void getFirst()
	{
		cout<<info.first().m<<endl;
	}
};

END_ZTC_NAMESPACE

#endif //ZTC__INCLUDE__BASEMEMBERPAIR_HPP