#ifndef ZTC_ZList_HPP
#define ZTC_ZList_HPP

template <typename ObjType>
struct ZNode
{
	ObjType m_value;
	ZNode<ObjType> *m_pNext;
};

template <typename ObjType>
class ZList 
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

	int search(const ObjType &obj)
	{
		ZNode<ObjType> *pTmpNode = m_pList;
		int index = 0;
		while(pTmpNode != NULL)
		{
			if(pTmpNode->m_value == obj)
				break;
			pTmpNode = pTmpNode->m_pNext;
			++index;
		}
		return index;
	}

	void deleteNode(int index, ObjType &obj)
	{
		ZNode<ObjType> *pTmpNode = m_pList;
		ZNode<ObjType> *pPreNode = NULL;
		while(index--)
		{
			pPreNode = pTmpNode;
			pTmpNode = pTmpNode->m_pNext;
		}

		pPreNode->m_pNext = pTmpNode->m_pNext;
		obj = pTmpNode->m_value;
		delete pTmpNode;
		pTmpNode = NULL;
		--m_size;
	}

	bool isEmpty()
	{
		return (m_size == 0 ? true : false);
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
			delete m_pList;
			m_pList = NULL;
			m_pList = pNode;
			--m_size;
		} while (m_pList->m_pNext != NULL);
	}

	ZNode <ObjType> * m_pList;
	int m_size;
	
};


#endif //ZTC_ZList_HPP