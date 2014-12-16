#ifndef ZTC_TEST_TEST1_H
#define ZTC_TEST_TEST1_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "../ZTC/include/ZPoint.h"
#include "../ZTC/include/ZCommonality.h"
#include "../ZTC/include/ZSortTracer.hpp"
#include "../ZTC/include/ZIfThenElse.hpp"
#include "../ZTC/include/ZBaseMemberPair.hpp"

using namespace std;
using namespace ZTC;

template <typename T>
class Creator
{
public:
	friend void feed(Creator<T>*)
	{
		cout<<"feed º¯Êý"<<endl;
	}
};


template <template <typename > class TT>
class X 
{};

template <typename T>
class C
{
public:
	C* a;
//	C<void> c;
	X<::C> d;
	X< ::C> e;

};

template<typename T>
class B 
{
public:
	enum E{e1 = 6, e2 = 28, e3 = 496};
	virtual void zero(E e = e1){};
	virtual void one(E &);
};

//template <typename T>
//class D: public B<T>
//{
//public:
//	typename D<T>::E E1;
//	//this->zero();
//	one(E1);
//};

class TestClass
{
public:
	TestClass() : m(10){}
	int m;
};
void Test2()
{}

int Test1()
{
	char *str = "#C255 244 233 22##H5##a1#";
	cout<<"The string is: "<<str<<endl;

	vector<string> ve;
	//SplitBaseOnGropChar(str, split[1], ve);
	//SplitBaseOnMultiGropChar(str, split, ve);
	SplitBaseOnSingleChar(str, "#0123456789", ve);
	//SplitBaseOnGropChar(str, "asd", ve);
	for(vector<string>::iterator ite = ve.begin(); ite != ve.end(); ++ite)
		cout<<*ite<<endl;
	cout<<CharToHex(str)<<endl;

	//cout<<ItoString(6.1234213123198098789877983, 20)<<endl;
	
	int i = 0;
	const int IntA = 10;
	//const int IntA = 6;
	//int arry[IntA] = {5, 2, 4, 6, 1, 3};
	int arry[IntA] = {0,0,49,49, 25, 52, 64, 98, 1, 3};
	//cout<<"The Orignal Arry is: "<<endl;
	//PutOut(arry, IntA);

	//cout<<"The Sorted Arry is: "<<endl;
	//BubbleSort(arry, IntA, false);
	//InsertionSort(arry, IntA, false);
	//SelectSort(arry, IntA, false);
	//MergeSort(arry, IntA, false);
	//QuickSort(arry, 0, IntA - 1, false);
	
	//PutOut(arry, IntA);

	int a = 0;

	/*ZSortTracer input[] = {7,3,5,6,4,2,0,1,9,8};
	cout<<"The Orignal Arry is: "<<endl;
	for(int i = 0; i<IntA; ++i)
		std::cerr<<input[i].val()<<" ";
	cout<<endl;

	long created_at_start = ZSortTracer::createions();
	long max_live_at_start = ZSortTracer::max_live();
	long assigned_at_start = ZSortTracer::assignments();
	long compared_at_start = ZSortTracer::comparisons();

	std::sort<>(&input[0], &input[0] + 9);

	cout<<"The Sorted Arry is: "<<endl;
	for(int i = 0; i<IntA; ++i)
		std::cerr<<input[i].val()<<" ";
	cout<<endl;

	std::cerr<<"std::sort() of 10 ZSortTracer's"
		<<" was performed by:\n"
		<<ZSortTracer::createions() - created_at_start
		<<" temporary tracers\n"
		<<"up to "
		<<ZSortTracer::max_live()
		<<" tracers at the same time ("
		<<max_live_at_start<<" before)\n"
		<<ZSortTracer::assignments() - assigned_at_start
		<<" assignments\n"
		<<ZSortTracer::comparisons() - compared_at_start
		<<" coparisons\n\n";
	*/

	Creator<int> one;
	Creator<int> two;

	Creator<int> *p = new Creator<int>;
	feed(p);

	C<int> cC;

	//Opt<TestClass> m;
	//m.getFirst();

	return 0;
}



#endif //ZTC_TEST_TEST1_H