#ifndef ZTC_TEST_TESTSMARTPTR_H
#define ZTC_TEST_TESTSMARTPTR_H

#include <iostream>
#include "../ZTC/SmartPtr/ZCountingPtr.hpp"

class Base
{
public:
	Base():a(13){}
	int a;
};

class Son:public Base
{
public:
	Son():b(0.123){}
	double b;
};

using namespace std;  
using namespace ZTC;

void TestSmartPtr()
{
	int *pInt = new int(10);
	ZCountingPtr<int> pSmart(pInt);
	{
		ZCountingPtr<int> pSmart2(pSmart);
		cout<<pSmart.GetCounter()<<endl;
		ZCountingPtr<int> pSmart1 = pSmart;
		cout<<pSmart1.GetCounter()<<endl;
	}
	cout<<pSmart.GetCounter()<<endl;

	Son *pSon = new Son();
	{
		/*ZCountingPtr<Base> pBase(pSon);
		cout<<pBase->a<<endl;*/
	}
	cout<<"子类a的值:"<<pSon->a<<endl;

	//int *pInt0 = new int(30);
	////std::shared_ptr<int> pSharedPtr1(pInt0);
	//{
	//	std::shared_ptr<int> pSharedPtr(pInt0);
	//}
	//cout<<*pInt0<<endl;

	//int *pInt0;
	//std::shared_ptr<int> pSharedPtr(pInt0);
}

#endif //ZTC_TEST_TESTSMARTPTR_H