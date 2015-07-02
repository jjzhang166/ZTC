#ifndef ZTC_ZDoubleLinkList_HPP
#define ZTC_ZDoubleLinkList_HPP

#include "../include/ZMacroDefine.h"
#include "../include/ZBase.h"

BEGIN_ZTC_NAMESPACE

template <typename ObjType>
struct ZTC_CLASS ZDoubleLinkNode
{
	ObjType m_value;
	ZDoubleLinkNode<ObjType> *m_pNext;
	ZDoubleLinkNode<ObjType> *m_pPre;

	ZDoubleLinkNode(): m_pNext(NULL),m_pPre(NULL){}
};

template<typename ObjType>
class ZTC_CLASS ZDoubleLinkList
{
public:
	ZDoubleLinkList(): m_pDoubleLinkList(NULL), m_size(0)
	{

	}

	~ZDoubleLinkList(){}
	void insert(const ObjType &obj)
	{
		ZDoubleLinkNode<ObjType> *pNode = new(std::nothrow)ZDoubleLinkNode<ObjType>();
		pNode->m_value = obj;

		if(m_pDoubleLinkList == NULL)
		{
			m_pDoubleLinkList = pNode;
		}
		else
		{
			pNode->m_pNext = m_pDoubleLinkList;
			m_pDoubleLinkList->m_pPre = pNode;
			m_pDoubleLinkList = pNode;
		}
		++m_size;
	}

	void insert(const ObjType &obj, int index)
	{
		if(index >= m_size)
			return;
		
		if(index == 0)
		{
			insert(obj);
			return;
		}

		ZDoubleLinkNode<ObjType> *pNode = new(std::nothrow)ZDoubleLinkNode<ObjType>();
		pNode->m_value = obj;

		ZDoubleLinkNode<ObjType> *pTmp = m_pDoubleLinkList;
		while(--index)
		{
			pTmp = pTmp->m_pNext;
		}

		pTmp->m_pPre->m_pNext = pNode;
		pNode->m_pPre = pTmp->m_pPre;
		pNode->m_pNext = pTmp;
		pTmp->m_pPre = pNode;

		++m_size;
	}

	bool search(const ObjType &obj, int &index)
	{
		bool isFind = false;
		int i = 0;
		ZDoubleLinkNode<ObjType> *pTmp = m_pDoubleLinkList;
		while(pTmp->m_pNext)
		{
			if(pTmp->m_value == obj)
			{
				isFind = true;			
				break;
			}
			pTmp = pTmp->m_pNext;
			++i;
		}
		if(isFind)
			index = i;
		return isFind;
	}
	
	bool deleteObj(int index, ObjType &obj)
	{
		if(index >= m_size)
			return false;
		if(index == 0)
		{
			ZDoubleLinkNode<ObjType> *pTmpNode = m_pDoubleLinkList;
			obj = m_pDoubleLinkList->m_value;
			m_pDoubleLinkList = m_pDoubleLinkList->m_pNext;
			DELETE_PTR(pTmpNode);
			--m_size;
			return true;
		}

		ZDoubleLinkNode<ObjType> *pTmpNode = m_pDoubleLinkList;
		ZDoubleLinkNode<ObjType> *pPreNode = NULL;
		while(index--)
		{
			pPreNode = pTmpNode;
			pTmpNode = pTmpNode->m_pNext;
		}

		pPreNode->m_pNext = pTmpNode->m_pNext;
		obj = pTmpNode->m_value;
		DELETE_PTR(pTmpNode);
		--m_size;
		return true;
	}

private:
	ZDoubleLinkNode<ObjType> *m_pDoubleLinkList;
	int m_size;
};


END_ZTC_NAMESPACE

#endif //ZTC_ZDoubleLinkList_HPP