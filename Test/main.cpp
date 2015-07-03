#include <stdio.h>  
#include "stdlib.h"  
#include "math.h"  
#include <iostream>  
#include <string>
#include <sys/timeb.h>

#include "TestLog.h"

#include "../ZTC/include/ZCommonality.h"
#include "../ZTC/include/ZCommon.hpp"
#include "../ZTC/PictureRead/ZBitmapStruct.h"
#include "../ZTC/PictureRead/ZPictureFunctionPool.h"
#include "../ZTC/PictureRead/ZBitmap.h"
#include "../ZTC/SmartPtr/ZCountingPtr.hpp"
#include "../ZTC/Algorithm/include/Z_BinaryTreeImp.hpp"

#include "Test1.h"
#include "TestContainer.h"
#include "TestSmartPtr.h"
#include "TestAlgorithm.h"
#include "testDelegation.h"

//#include <boost\shared_ptr.hpp>

using namespace std;  
using namespace ZTC;

union obj
{
	/*union*/ obj * free_list_link;
	char client_data[1];
};

enum{_ALIGN = 8};

size_t round_up(size_t bytes)
{
	return (((bytes) + _ALIGN - 1) &(~(_ALIGN - 1)));
}

int maxSum(int *arr, int n, int & start, int & end)    
{  
	int i , temp , dp , max ;  
	dp = max = arr[n-1];  
	start = end = n-1;  
	temp = n-1;  
	for(i = n - 2 ; i >= 0 ; --i)  
	{  
		if(dp > 0)  
			dp += arr[i];  
		else  
		{  
			dp = arr[i];    //抛弃当前子序列  
			temp = i;        //开始新的子序列搜索  
		}  
		if(dp > max)        //更新最大子序列  
		{  
			max = dp;  
			end = temp;  
			start = i;           //最大和增加，此时的i一定是最右端  
		}  
	}  
	return max;  
} 

int maxSubArray(int *pArray, int n)
{
	int sum = 0;
	int maxSum = 0; //最大子序列值
	for(int i = 0; i<n; ++i)
	{
		if(sum >= 0)
		{
			sum += pArray[i];
		}
		else
		{
			sum = pArray[i];
		}
		if(sum > maxSum)
			maxSum = sum;
	}
	return maxSum;
}

struct SubArray
{
	int maxValue;
	int left;
	int right;
	SubArray():maxValue(-32768),left(-32768),right(-32768){}
};

SubArray findMaxCrossingSubArray(int *pArray, int left, int middle, int right)
{
	//--@左边最大子数组
	int leftSum = 0;
	int maxLeftSum = -32768;
	int leftEnd = -32768;
	for(int i = middle; i>= left; --i)
	{
		leftSum += pArray[i - 1];
		if(leftSum > maxLeftSum)
		{
			maxLeftSum = leftSum;
			leftEnd = i;
		}
	}

	//--@右边最大子数组
	int rightSum = 0;
	int maxRightSum = -32768;
	int rightEnd = -32768;
	for(int j = middle + 1; j<=right; ++j)
	{
		rightSum += pArray[j - 1];
		if(rightSum > maxRightSum)
		{
			maxRightSum = rightSum;
			rightEnd = j;
		}
	}

	SubArray retSubArray;
	retSubArray.left = leftEnd;
	retSubArray.right = rightEnd;
	retSubArray.maxValue = maxLeftSum + maxRightSum;
	return retSubArray;
}

SubArray findMaxSubArray(int *pArray, int left, int right)
{
	if(left == right)
	{
		SubArray subArray;
		subArray.left = left;
		subArray.right = right;
		subArray.maxValue = pArray[left - 1];

		return subArray;
	}

	int num = left + right;
	int minddle =  num/2; 
	SubArray leftArray = findMaxSubArray(pArray, left, minddle);
	SubArray rightArray = findMaxSubArray(pArray, minddle + 1, right);
	SubArray middleArray = findMaxCrossingSubArray(pArray, left, minddle, right);

	if(leftArray.maxValue >= rightArray.maxValue 
		&& leftArray.maxValue >= middleArray.maxValue)
		return leftArray;
	else if(rightArray.maxValue >= leftArray.maxValue &&
		rightArray.maxValue >= middleArray.maxValue)
		return rightArray;
	else
		return middleArray;
}

SubArray maxSubA(int *pArray, int n)
{
	return findMaxSubArray(pArray, 1, n);
}

int find(int A[],int start,int end)
{
	if(start==end)
	{
		if(A[start]>0)
			return A[start];
		else return 0;
	}
	int leftsum,rightsum,center;
	center=(start+end)/2;
	leftsum=find(A,start,center);
	rightsum=find(A,center+1,end);
	int leftpartsum=0,leftbiggest=0,rightpartsum=0,rightbiggest=0,i;
	//如果跨过中间
	for(i=center;i>=0;i--)
	{
		leftpartsum=leftpartsum+A[i];
		if(leftbiggest<leftpartsum)
			leftbiggest=leftpartsum;
	}
	for(i=center+1;i<=end;i++)
	{
		rightpartsum=rightpartsum+A[i];
		if(rightbiggest<rightpartsum)
			rightbiggest=rightpartsum;
	}
	return max(max(leftsum,rightsum),leftbiggest+rightbiggest);
}

class Base0
{

};


class Son0:public Base0
{

};



class Empty{typedef int Int;};
class EmptyToo : public Empty{};
//class EmptyThree : public EmptyToo, public Empty{};


void testTime()
{
	struct        timeb        tp;
	struct        tm        * tm;

	ftime ( &tp );
	tm = localtime (  & ( tp.time )  );

	printf ( "%02d:%02d:%02d:%03d\n", ( tm -> tm_hour ) , ( tm -> tm_min  ) ,
		( tm -> tm_sec  ),        ( tp.millitm ) );
}

int main(int argv, char*argc[])
{    
	//Test1();
	////TestSmartPtr();
	////TestContainer();
	//cout<<round_up(2)<<endl;
	//cout<<sizeof(obj)<<endl;

	//TestLog();

	//int start;
	//int end;
	//int tmpArray[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	//cout<<maxSum(tmpArray, 16, start, end)<<endl;
	//cout<<maxSubArray(tmpArray, 16)<<endl;

	//SubArray subArray = maxSubA(tmpArray, 16);

	//cout<<find(tmpArray, 0, 15)<<endl;

	//TestAlogrithm();
	//TestAlogrithm1();

	//cout<<"sizeof(Empty): "<<sizeof(Empty)<<endl;
	//cout<<"sizeof(EmptyToo): "<<sizeof(EmptyToo)<<endl;
	////cout<<"sizeof(EmptyThree): "<<sizeof(EmptyThree)<<endl;

	//engageInLawsuit();
	//engageInLawsuit1();

	//TestAlogrithm2();
	
	TestLog();
	testDoubleLinkList();
	testList();

	//testTime();

	return 0;
}  