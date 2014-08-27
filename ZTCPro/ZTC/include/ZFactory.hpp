#ifndef ZTC_INCLUDE_ZFACTORY_HPP
#define ZTC_INCLUDE_ZFACTORY_HPP

#include "ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE

class ZProduct
{
public:
	virtual ~ZProduct() = 0;
};

ZProduct::~ZProduct()
{}

class ZCreator
{
public:
	virtual ~ZCreator(){}
	
	virtual ZProduct* createProduct() = 0;
};

END_ZTC_NAMESPACE

#endif