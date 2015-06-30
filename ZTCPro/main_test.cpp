#include <string>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Observe.h"
#include "./include/ZHeaply.h"
#include "./include/ZBiggestPriorityQueue.hpp"
#include "./include/ZMinimumPriorityQueue.hpp"
#include "./include/ZFormatData.h"

using std::wstring;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::string;

typedef unsigned long long U32;

inline unsigned int rank(const unsigned long long& n)
{
	if (n<2) return 0;

	unsigned long long k(1);
	unsigned int i=0;
	for (;i<sizeof(unsigned long long)*8;++i)
	{
		if(n<k) break;
		k <<=1;
	}
	return i-1;
}

inline unsigned int bitsOfNumber(const unsigned long long& n){return rank(n)+1;}

wstring numToWstring( U32 num, bool isTow = false)
{
	wstring unit(L"");
	switch(num % 10)
	{
	case 0:
		{
			unit = L"";			
		}break;
	case 1:
		{
			unit = L"一";
		}break;
	case 2:
		{
			if(!isTow)
				unit = L"两";
			else
				unit = L"二";
		}break;
	case 3:
		{
			unit = L"三";
		}break;
	case 4:
		{
			unit = L"四";
		}break;
	case 5:
		{
			unit = L"五";
		}break;
	case 6:
		{
			unit = L"六";
		}break;
	case 7:
		{
			unit = L"七";
		}break;
	case 8:
		{
			unit = L"八";
		}break;
	case 9:
		{
			unit = L"九";
		}break;
	}
	return unit;
}


wstring numberCovertPromptData( U32 num, bool isTow = false)
{
	wstring reStr;
	//wstring unitStr(L"十百千万零");
	//U32 len = unitStr.length();

	//wstring unitStr[] = {L"十", L"百", L"千", L"万", L"十万", L"百万",L"千万",L"亿", L"零"};
	//U32 len = 9;
	wstring unitStr[] = {L"十", L"百", L"千", L"万", L"亿", L"零"};
	U32 len = 6;

	U32 i = 0;
	wstring strNum;
	U32 tmpNum = num;
	wstring unit;
	wstring preUnit;
	while(tmpNum != 0)
	{
		U32 tmp = tmpNum % 10;
	 	tmpNum = tmpNum / 10;
		if(tmp != 0)
			strNum = numToWstring(tmp, true);
		else
			strNum = L"";
		if(i != 0 && !strNum.empty()) 
		{
			//unit = unitStr[i - 1];
			if(i >= 5 && i < 8)
			{
				unit = unitStr[i%5];
				if(i == 5)
					preUnit = L"";
			}
			else if(i >= 9 )
			{
				unit = unitStr[i%9];
			}
			else if(i == 8)
			{
				unit = unitStr[4];
				preUnit = L"";
			}
			else
				unit = unitStr[i - 1];
		}
		if(i != 0 && strNum.empty() && !reStr.empty() /*&& unit.compare(L"零") != 0*/)
		{
			if(i == 4)
				unit = unitStr[3];
			else if( i == 8)
				unit = unitStr[4];
			else
			{
				preUnit = unit;
				unit = unitStr[len - 1];
			}
		}
		if(preUnit.compare(unit) == 0)
			reStr = strNum + reStr;
		else
			reStr = strNum + unit + reStr;
		++i;
	}

	if(num >= 10 && num < 20)
		reStr = reStr.substr(1);

	return reStr;
}

void numToChinese()
{
	setlocale(LC_ALL,"chs");
	U32 i = 100;
	U32 num[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,55,44,100,101,109,110,111,122,1000,1001
	,1011
	,1101
	,1111
	,10000
	,10001
	,10010
	,10100
	,11000
	,11100
	,11110
	,11111
	,111100
	,111111
	,1111111
	,11111111
	,111111111
	,1111111111
	,11101101010
	};
	U32 n = sizeof(num)/sizeof(U32);
	wstring re;
	for(U32 i = 0; i < n; ++i)
	{
		re = numberCovertPromptData(num[i]);
		//cout<<num[i]<<" : "<<re<<endl;
		wprintf(L"num: %lld , %s\n", num[i], re.c_str());
	}
	cout<<endl;
}

void cacheBlockIDTest()
{
	vector<U32> ve;
	const U32 num = 16;
	U32 numS[num] = {0};
	U32 unit =  bitsOfNumber(num);
	U32 unit1 = sizeof(U32) * 8 - unit;
	for(U32 j = 0; j < num; ++j)
	{
		cout<<((1 << unit) | j )<<endl;
		numS[j] = ((1 << unit) | j );
		ve.push_back(numS[j]);
	}

	
	/*cout<<"--------------------------------------"<<endl;
	for(U32 i = 0; i < num; ++i)
	{
		U32 tmp = (numS[i]);
		cout<<(tmp >> unit) << " : " << ((numS[i] << unit1) >> unit1)<<endl;
	}*/

	ofstream of("data.txt");
	int count = 0;
	int count1 = 0;
	cout<<"--------------------------------------"<<endl;
	for(U32 j = 1; j < 10000; ++j)
	{
		cout<<"**********************"<<endl;
		of<<"------------------------begin***********"<<endl;
		for(U32 i = 0; i < num; ++i)
		{
			U32 pre = numS[i];
			U32 tmp = ((numS[i] >> unit) + 1) << unit;
			numS[i] = tmp | i;
			cout<<pre<<": "<<tmp<<" : "<<numS[i]<<endl;
			//cout<<(tmp >> unit) << " : " << ((num[i] << unit) >> unit)<<endl;
			
			of<<"***********begin***********"<<endl;
			of<<"pre: "<<pre<<" now: "<<numS[i]<<" count: "<<j<<endl;
			of<<"now: "<<numS[i]<<" count: "<<(numS[i]>>unit)<<" index: "<<((numS[i] << unit1) >> unit1)<<endl;
			of<<"***********end***********"<<endl;

			if(std::find(ve.begin(), ve.end(), numS[i]) != ve.end())
				++count1;
			
			ve.push_back(numS[i]);
		}
		of<<"------------------------end***********"<<endl;
		if(numS[0] >= 4000000000/* 4294967296*/ )
		{
			++count;
		}
	}

	cout<<"--------------------------------------"<<endl;
	for(U32 i = 0; i < ve.size(); ++i)
	{
		U32 tmp = ve[i];
		cout<<ve[i]<<" : 更改次数： "<<(tmp >> unit)<<" : 索引： "<<((ve[i] << unit1) >> unit1) <<endl;
	}
	cout<<"count: "<<count<<"	count1: "<<count1<<endl;
}


class A
{
public:
	char *m_p1;
protected:
	char *m_p2;
private:
	char *m_p3;
};

class B : public A
{

};

/*-----  ------*/
void fun(int m)
{
	cout<<"fun: "<<m<<endl;
}

void testObserve()
{
	ObservableObj observe;

	Observe1 ob1;
	observe.addObserve(&ob1);
	observe.addFun(fun);
	observe.notifice(5);

}


bool toFile(const char* pSourceFile, const char* pDesFile)
{
	if(pSourceFile == NULL || pDesFile == NULL)
		return false;

	ifstream inFile(pSourceFile);
	ofstream outFile(pDesFile);
	
	const int MAX_SIZE = 256;
	char text[MAX_SIZE] = {};
	while(inFile.getline(text, MAX_SIZE))
	{
		char tmp[MAX_SIZE] = {};
		inFile.getline(tmp, MAX_SIZE);
		if(strcmp(text, tmp) == 0)
			continue;
		outFile<< text<<endl;
		//strcpy(text, tmp);
	}
	outFile<< text<<endl;
}

void test1()
{
	string str1("E:\\Deve\\Test\\Test2\\802372_2015-3-23.txt");
	string str2("E:\\Deve\\Test\\Test2\\3_23.txt");
	/*cout<<"源文件：";
	cin>>str1;
	cout<<endl;
	cout<<"目标文件名：";
	cin>>str2;*/
	cout<<endl;
	toFile(str1.c_str(), str2.c_str());
}

void test2()
{
	//用一个FOR 循环排除数组里面的奇数
	int arry[] = {0, 1, 2, 3, 4, 5, 8, 10};
	int size = sizeof(arry)/sizeof(arry[0]);
	int n = size;
	for(int i = 0; i < size; ++i)
	{
		if(arry[i] % 2 != 0)
		{
			memcpy(arry + i, arry + i + 1, (size - i) * sizeof(int));
			n -= 1;
		}
	}

	for(int i = 0; i <n; ++i)
		cout<<arry[i]<<endl;
}

//template <typename ObjTpye>
//void maxHeaply(ObjTpye *array, int num, int index)
//{
//	int left = 2 * index;
//	int right = 2 * index + 1;
//	int maxIndex = index;
//	if(left <= num -1 && array[left] > array[index])
//	{
//		maxIndex = left;
//	}
//
//	if(right <= num - 1 && array[right] > array[maxIndex])
//	{
//		maxIndex = right;
//	}
//
//	if(maxIndex != index)
//	{
//		int temp = array[index];
//		array[index] = array[maxIndex];
//		array[maxIndex] = temp;
//		maxHeaply(array, num, maxIndex);
//	}
//}
//
//template <typename ObjTpye>
//void keepHeaply(ObjTpye *array, int num, int index, bool isMaxHeap = true)
//{
//	int left = 2 * index;
//	int right = 2 * index + 1;
//	int maxOrminIndex = index;
//	if(left <= num -1 && ((array[left] > array[index] && isMaxHeap)||(array[left] < array[index] && !isMaxHeap)))
//	{
//		maxOrminIndex = left;
//	}
//
//	if(right <= num - 1 && ((array[right] > array[maxOrminIndex] && isMaxHeap) || (array[right] < array[maxOrminIndex] && !isMaxHeap)))
//	{
//		maxOrminIndex = right;
//	}
//
//	if(maxOrminIndex != index)
//	{
//		int temp = array[index];
//		array[index] = array[maxOrminIndex];
//		array[maxOrminIndex] = temp;
//		keepHeaply(array, num, maxOrminIndex, isMaxHeap);
//	}
//}
//
//template <typename ObjType>
//void heapSort(ObjType * array, int size, bool isMaxHeap = true)
//{
//	//构建堆
//	for(int i = size/2; i >= 0; i--) //节点
//	{
//		if(isMaxHeap)
//			keepHeaply(array, size, i, true);//maxHeaply(array, size, i);//保持最大堆
//		else
//			keepHeaply(array, size, i, false); //保持最小堆
//	}
//
//	int num = size - 1;
//	for(int i = size - 1; i >= 1; i --)
//	{
//		int tmp = array[0];
//		array[0] = array[i];
//		array[i] = tmp;
//		if(isMaxHeap)
//			keepHeaply(array, num, 0, true);//maxHeaply(array, num, 0);
//		else
//			keepHeaply(array, num, 0, false);
//		num -= 1;
//	}
//}

void testHeapSort()
{
	int array[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int size = sizeof(array)/sizeof(int);

	heapSort(array, size);

	for(int j = 0; j < sizeof(array)/sizeof(int); j++)
	{
		cout<<array[j]<<",";
	}
	cout <<endl;
}

void testMulitHeapSort()
{
	int array[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int size = sizeof(array)/sizeof(int);

	multiHeapSort(array, size, 4);

	for(int j = 0; j < sizeof(array)/sizeof(int); j++)
	{
		cout<<array[j]<<",";
	}
	cout <<endl;
}

//最大优先级队列
class BiggestPriorityQueue
{
public:
	BiggestPriorityQueue(): m_pArrayS(NULL), m_size(0),m_actualSize(0)
	{
		int defaultNum = 10;
		m_pArrayS = new (std::nothrow) int[defaultNum];
		m_size = defaultNum ;
		memset(m_pArrayS, 0, m_size);
	}
	~BiggestPriorityQueue()
	{
		delete [] m_pArrayS;
		m_pArrayS = NULL;
	}

	void insert(int x)
	{
		m_pArrayS[m_actualSize] = x;
		m_actualSize++;
		//maxHeaply(m_pArrayS, m_actualSize, (m_actualSize - 1)/2);
		increaseKey(m_actualSize - 1, x);
	}
	int maximum()
	{
		if(m_pArrayS == NULL)
			return 0;
		return m_pArrayS[0];
	}
	int extractMax()
	{
		int maxValue = m_pArrayS[0];
		m_pArrayS[0] = m_pArrayS[m_actualSize - 1];
		int num = m_actualSize - 1;
		//maxHeaply(m_pArrayS, num, 0);
		keepHeaply(m_pArrayS, num, 0, true);
		return maxValue;
	}

	void increaseKey(int index, int value)
	{
		int i = index;
		m_pArrayS[i] = value;
		while(m_pArrayS[i] > m_pArrayS[i / 2])
		{
			int temp = m_pArrayS[i/2];
			m_pArrayS[i/2] = m_pArrayS[i];
			m_pArrayS[i] = temp;

			i = i / 2;
		}
	}

	void putOut()
	{
		for(int j = 0; j < m_actualSize; j++)
		{
			cout<<m_pArrayS[j]<<",";
		}
		cout <<endl;
	}

private:
	int *m_pArrayS;
	int m_size;
	int m_actualSize;
};

void testBiggestPriorityQueue()
{
	cout<<"---------------------testBiggestPriorityQueue---------------------Begin"<<endl;
	ZBiggestPriorityQueue<int> priorityColumn;
	int array[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int size = sizeof(array)/sizeof(int);

	for(int j = 0; j < sizeof(array)/sizeof(int); j++)
	{
		priorityColumn.insert(array[j]);
	}
	priorityColumn.putOut();
	priorityColumn.increaseKey(8, 15);
	priorityColumn.putOut();
	priorityColumn.deleteElement(8);
	priorityColumn.putOut();
	cout<<"---------------------testBiggestPriorityQueue---------------------End"<<endl;
}

//最小优先级队列
class MinimumPriorityQueue
{
public:
	MinimumPriorityQueue(): m_pArrayS(NULL), m_size(0),m_actualSize(0)
	{
		int defaultNum = 10;
		m_pArrayS = new (std::nothrow) int[defaultNum];
		m_size = defaultNum ;
		memset(m_pArrayS, 0, m_size);
	}
	~MinimumPriorityQueue()
	{
		delete [] m_pArrayS;
		m_pArrayS = NULL;
	}
	
	int minimum()
	{
		if(m_pArrayS == NULL)
			return 0;
		return m_pArrayS[0];
	}
	int extractMin()
	{
		int min = m_pArrayS[0];
		m_actualSize--;
		m_pArrayS[0] = m_pArrayS[m_actualSize - 1];
		keepHeaply(m_pArrayS, m_size, 0, false);
		return min;
	}

	void decreaseKey(int index, int value)
	{
		int i = index;
		m_pArrayS[i] = value;
		while(m_pArrayS[i] < m_pArrayS[i/2])
		{
			int temp = m_pArrayS[i/2];
			m_pArrayS[i/2] = m_pArrayS[i];
			m_pArrayS[i] = temp;

			i = i / 2;
		}
	}

	void insert(int x)
	{
		m_pArrayS[m_actualSize] = x;
		m_actualSize++;
		decreaseKey(m_actualSize - 1, x);
	}

	void putOut()
	{
		for(int j = 0; j < m_actualSize; j++)
		{
			cout<<m_pArrayS[j]<<",";
		}
		cout <<endl;
	}

private:
	int *m_pArrayS;
	int m_size;
	int m_actualSize;
};

void testMinimumPriorityQueue()
{
	cout<<"----------------------- testMinimumPriorityQueue -----------------------Begin"<<endl;
	ZMinimumPriorityQueue<int> priorityColumn;
	int array[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int size = sizeof(array)/sizeof(int);

	for(int j = 0; j < sizeof(array)/sizeof(int); j++)
	{
		priorityColumn.insert(array[j]);
	}
	priorityColumn.putOut();
	priorityColumn.decreaseKey(8, 15);
	priorityColumn.putOut();
	cout<<"----------------------- testMinimumPriorityQueue -----------------------End"<<endl;
}


void testQuickSort()
{
	int array[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	quickSort(array, 0, sizeof(array)/sizeof(array[0]) - 1, false);
	for(int j = 0; j < sizeof(array)/sizeof(array[0]); j++)
	{
		cout<<array[j]<<",";
	}
	cout <<endl;
}


//用一个数组来实现两个栈
class TestStack
{
public:
	TestStack(int num): m_pArray(NULL),m_num(num),m_stack1Pos(-1),m_stack2Pos(num)
	{
		m_pArray = new int[num];
		memset(m_pArray, 0, num);
	}
	~TestStack()
	{
		delete [] m_pArray;
		m_pArray = NULL;
	}

	void push(int stackID, int value)
	{
		if(m_stack1Pos == m_stack2Pos)//栈满了
			return;

		if(stackID == 1)
		{
			++m_stack1Pos;
			m_pArray[m_stack1Pos] = value;
		}
		else
		{
			--m_stack2Pos;
			m_pArray[m_stack2Pos] = value;
		}
	}

	bool empty(int &stackID)
	{
		if(m_stack1Pos == -1)
		{
			stackID = 1;
			return true;
		}

		if(m_stack2Pos == m_num)
		{
			stackID = 2;
			return true;
		}
			
		return false;
	}

	bool isFull()
	{
		if(m_stack1Pos == m_stack2Pos)
			return true;
		return false;
	}

	int pop(int stackID)
	{
		if(stackID == 1)
		{
			if(m_stack1Pos == -1)
				return 0xffff;
			int tmp = m_pArray[m_stack1Pos];
			--m_stack1Pos;
			return tmp;
		}
		else
		{
			if(m_stack2Pos == m_num)
				return 0xffff;
			int tmp = m_pArray[m_stack2Pos];
			++m_stack2Pos;
			return tmp;
		}
	}

private:
	int* m_pArray;
	int m_num;
	int m_stack1Pos;
	int m_stack2Pos;
};

void testStack()
{
	TestStack testStack(10);
	testStack.push(1, 0);
	testStack.push(1, 2);
	testStack.push(1, 4);
	
	testStack.push(2, 1);
	testStack.push(2, 3);
	testStack.push(2, 5);

	cout<<testStack.pop(1)<<" , ";
	cout<<testStack.pop(1)<<" , ";
	cout<<testStack.pop(1)<<endl;
	cout<<testStack.pop(2)<<" , ";
	cout<<testStack.pop(2)<<" , ";
	cout<<testStack.pop(2)<<endl;
	cout<<testStack.pop(1)<<endl;
	cout<<testStack.pop(1)<<endl;
	cout<<testStack.pop(2)<<endl;
}

//两个栈来实现一个队列
class TestQue
{
public:
	TestQue(): m_stack(10), m_stackId(1), m_deleteId(2)
	{

	}

	bool push(int value)
	{
		if(m_stack.isFull())
			return false;
		m_stack.push(1, value);
		return true;
	}

	int deleteQue()
	{
		return 0;
	}

private:
	TestStack m_stack;
	int m_stackId;
	int m_deleteId;
};


void testQue()
{
	TestQue que;
	que.push(0);
	que.push(2);
	que.push(4);
	que.push(1);
	que.push(3);
	que.push(5);

	cout<<que.deleteQue()<<" , ";
	cout<<que.deleteQue()<<" , ";
	cout<<que.deleteQue()<<" , ";
	cout<<que.deleteQue()<<" , ";
	cout<<que.deleteQue()<<" , ";
	cout<<que.deleteQue()<<" , ";
	cout<<que.deleteQue()<<" , ";
}

void main()
{
	numToChinese();
	//cacheBlockIDTest();
	//cout <<sizeof(A)<<endl;
	//testObserve();
	//cout<<(true?1:'1')<<endl;
	
	//testHeapSort();
	//testMulitHeapSort();
	//testBiggestPriorityQueue();
	//testMinimumPriorityQueue();
	//testQuickSort();

	//testStack();
	//testQue();

	//ZFormatData fileFormat("text.txt", "formatData.txt");
	//fileFormat.formatData();
}