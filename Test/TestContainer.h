#ifndef ZTC_TEST_TESTCONTAINER_H
#define ZTC_TEST_TESTCONTAINER_H

#include <iostream>
#include "../ZTC/include/ZStdf.h"
#include "../ZTC/include/ZCommonality.h"
//#include "../ZTC/Container/ZDuo.hpp"
#include "../ZTC/include/ZList.hpp"
#include "../ZTC/Container/ZDoubleLinkList.hpp"

using namespace std;
using namespace ZTC;

int TestContainer()
{
//	ZDuo<int, double> tmpDuo1;// = MakeDuo(4, 5.98);
//	//ZDuo<int, bool> tmpDuo2 = MakeDuo(4, true);
//	//ZDuo<int, ZDuo<double, double> >tmpDuo3;
//	//if(tmpDuo1 == tmpDuo2)
//		//cout<<"³É¹¦"<<endl;
//
	return 0;
}

void testList()
{
	ZList<int> tmpList;
	tmpList.insert(2);
	tmpList.insert(4);
	tmpList.insert(5);
	int index;
	bool bo = tmpList.search(4, index);
	bo = tmpList.search(2, index);
	int node;
	tmpList.deleteObj(index, node);

	ZList<int> tmp0(tmpList);
	ZList<int> tmp1 = tmp0;
}

void testDoubleLinkList()
{
	ZDoubleLinkList<int> tmpList;
	tmpList.insert(4);
	tmpList.insert(5);
}

#endif //ZTC_TEST_TESTCONTAINER_H