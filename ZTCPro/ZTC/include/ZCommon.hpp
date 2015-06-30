#ifndef ZTC_ZCOMMON_HPP
#define ZTC_ZCOMMON_HPP

#ifdef ZTC_TERMINAL_PUT_OUT

#include <iostream>

using std::cout;
using std::endl;

#endif //ZTC_TERMINAL_PUT_OUT

namespace ZTC
{
#ifdef ZTC_TERMINAL_PUT_OUT
	template <typename T>
	void PutOut(T *arry, int number)
	{
		for(int i = 0; i<number; ++i)
			cout<<arry[i]<<" ";
		cout<<endl;
	}

	template <typename T>
	void PutOut(const T &coll)
	{
		typename T::const_iterator pos;
		typename T::const_iterator end(coll.end());
		for(pos = coll.begin(); pos!= end; ++pos)
			cout<<*pos<<" ";
		cout<<endl;
	}
#endif //ZTC_TERMINAL_PUT_OUT

	/*************
	* ≤Â»Î≈≈–Ú
	*/
	template <typename T>
	void InsertionSort(T *arry, int n, bool ascend = true)
	{
		for(int i = 1; i<n; ++i)
		{
			int key = arry[i];
			for(int j = i - 1; j>=0; --j)
			{
				if((ascend && arry[j] > key) 
					|| (!ascend && arry[j] < key))
				{
					arry[j + 1] = arry[j];
					arry[j] = key;
				}
			}
		}
	}

	/*************
	*  —°‘Ò≈≈–Ú
	*/
	template <typename T>
	void SelectSort(T *arry, int n, bool ascend = true)
	{
		for(int i = 0; i<n; ++i)
		{
			int minIndex = i;
			for(int j = i + 1; j<n; ++j)
			{
				if((ascend && arry[j] < arry[minIndex])
					|| (!ascend && arry[j] > arry[minIndex]))
					minIndex = j;
			}
			if(minIndex != i)
			{
				T temNum = arry[i];
				arry[i] = arry[minIndex];
				arry[minIndex] = temNum;
			}
		}
	}

	/*************
	*  √∞≈›≈≈–Ú
	*/
	template <typename T>
	void BubbleSort(T *arry, int n, bool ascend = true)
	{
		for(int i = 0; i<n; ++i)
		{
			for(int j = 0; j<n - 1; ++j)
			{
				if((ascend && arry[j] > arry[j + 1])
					|| (!ascend && arry[j] < arry[j + 1] ))
				{
					int tem = arry[j + 1];
					arry[j + 1] = arry[j];
					arry[j] = tem;
				}
			}
		}
	}

	/*************
	* πÈ≤¢≈≈–Ú
	*/
	template<typename T>
	void Merge(T *arry, int firstOne, int firstEnd, int secondOne, int secondEnd, T *pArry, bool ascend = true)
	{
		int firstIndex = firstOne;
		int secondIndex = secondOne;

		int k = 0;
		while(firstIndex <= firstEnd && secondIndex <= secondEnd )
		{
			if((ascend && arry[firstIndex] <= arry[secondIndex])
				||(!ascend && arry[firstIndex] >= arry[secondIndex]))
				pArry[k++] = arry[firstIndex++];
			else
				pArry[k++] = arry[secondIndex++];
		}

		while(firstIndex <= firstEnd)
			pArry[k++] = arry[firstIndex++];

		while(secondIndex <= secondEnd)
			pArry[k++] = arry[secondIndex++];

		for (int i = 0; i < k; i++) 
		{
			arry[firstOne + i] = pArry[i];  
		}
		//PutOut(pArry, k);
	}

	template<typename T>
	void Dichotomia(T *arry, int first, int end, T *pArry, bool ascend = true)
	{
		if(first >= end)
			return;

		int num = first + end;
		int minddle =  num/2; 
		Dichotomia(arry, first, minddle, pArry, ascend); //◊Û±ﬂ”––Ú
		Dichotomia(arry, minddle + 1, end, pArry, ascend); //”“±ﬂ”––Ú
		Merge(arry, first, minddle, minddle + 1, end, pArry, ascend); //∫œ≤¢”––ÚºØ
	}

	template <typename T>
	void MergeSort(T *arry, int n, bool ascend = true)
	{
		if(n == 1)
			return;
		T *pArry = new T[n];
		Dichotomia(arry, 0, n - 1, pArry, ascend);
		delete [] pArry;
	}

	/*************
	* øÏÀŸ≈≈–Ú
	*/
	template<typename T>
int partation(T *pArray, int left, int right, bool ascend = true)
{
	int refValue = pArray[right];
	int i = left - 1;
	for(int j = left; j < right; ++j)
	{
		if((pArray[j] <= refValue && ascend) || (pArray[j] >= refValue && !ascend))
		{
			i = i + 1;

			int tmp = pArray[j];
			pArray[j] = pArray[i];
			pArray[i] = tmp;
		}
	}

	int tmp = pArray[i + 1];
	pArray[i + 1] = pArray[right];
	pArray[right] = tmp;
	return i + 1;
}

template<typename T>
void quickSort(T *arry, int leftIndex, int rightIndex, bool ascend = true)
{
	if(leftIndex >= rightIndex)
		return;

	int index = partation(arry, leftIndex, rightIndex, ascend);
	quickSort(arry, 0, index - 1, ascend);
	quickSort(arry, index + 1, rightIndex, ascend);
}
}
#endif //ZTC_COMMON_HPP