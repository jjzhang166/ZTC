#ifndef ZTC_ZList_HPP
#define ZTC_ZList_HPP

#include "../include/ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE

template <typename ObjType>
struct ZTC_CLASS ZNode
{
	ObjType m_value;
	ZNode<ObjType> *m_pNext;
};

template <typename ObjType>
class ZTC_CLASS ZList 
{
public:
	ZList() : m_pList(NULL), m_size(0)
	{

	}

	ZList(const ZList<ObjType> &other): m_pList(NULL), m_size(0)
	{
		clear();
		insert(other);
	}

	ZList<ObjType>& operator= (const ZList<ObjType> &other)
	{
		clear();
		
		ZNode<ObjType> *pTmpNode = other.m_pList;
		insert(other);
	}

	~ZList()
	{
		clear();
	}

	void insert(const ObjType &obj)
	{
		ZNode<ObjType> *pNode = new(std::nothrow) ZNode<ObjType>();
		pNode->m_value = obj;
		pNode->m_pNext = NULL;
		
		if(m_pList == NULL)
			m_pList = pNode;
		else
		{
			ZNode<ObjType> *pTmpNode = m_pList;
			while(pTmpNode->m_pNext != NULL)
			{
				pTmpNode = pTmpNode->m_pNext;
			}
			pTmpNode->m_pNext = pNode;
		}
		++m_size;
	}

	void insert(const ZList<ObjType> &otherList)
	{
		ZNode<ObjType> *pTmpNode = otherList.m_pList;
		while(pTmpNode)
		{
			insert(pTmpNode->m_value);
			pTmpNode = pTmpNode->m_pNext;
		}
	}

	bool search(const ObjType &obj, int &index)
	{
		bool isFind = false;
		ZNode<ObjType> *pTmpNode = m_pList;
		int i = 0;
		while(pTmpNode != NULL)
		{
			if(pTmpNode->m_value == obj)
			{
				isFind = true;
				break;
			}
			pTmpNode = pTmpNode->m_pNext;
			++i;
		}
		if(isFind)
			index = i;
		return isFind;
	}

	void deleteObj(int index, ObjType &obj)
	{
		if(index >= m_size)
			return;
		if(index == 0)
		{
			ZNode<ObjType> *pTmpNode = m_pList;
			obj = m_pList->m_value;
			m_pList = m_pList->m_pNext;
			DELETE_PTR(pTmpNode);
			--m_size;
			return;
		}

		ZNode<ObjType> *pTmpNode = m_pList;
		ZNode<ObjType> *pPreNode = NULL;
		while(index--)
		{
			pPreNode = pTmpNode;
			pTmpNode = pTmpNode->m_pNext;
		}

		pPreNode->m_pNext = pTmpNode->m_pNext;
		obj = pTmpNode->m_value;
		DELETE_PTR(pTmpNode);
		--m_size;
	}

	bool isEmpty()
	{
		return (m_size == 0 ? true : false);
	}

	int size()
	{
		return m_size;
	}
private:
	void clear()
	{
		if(m_pList == NULL)
			return;
		ZNode<ObjType> *pNode = NULL;
		do 
		{
			pNode = m_pList->m_pNext;
			DELETE_PTR(m_pList);
			m_pList = pNode;
			--m_size;
		} while (m_pList->m_pNext != NULL);
	}

	ZNode <ObjType> * m_pList;
	int m_size;
	
};

END_ZTC_NAMESPACE
#endif //ZTC_ZList_HPP