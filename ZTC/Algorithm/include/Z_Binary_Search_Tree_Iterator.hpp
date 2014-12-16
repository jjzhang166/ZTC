/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : Z_Tree_Node_Iterator.hpp
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.12.3 21:8:56
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.12.3 21:8:56
*/

#ifndef ZTC__ALGORITHM_INCLUDE__Z_Binary_Search_TREE_ITERATOR_HPP
#define ZTC__ALGORITHM_INCLUDE__Z_Binary_Search_TREE_ITERATOR_HPP

#include "../../include/ZMacroDefine.h"
#include "../../include/ZIterator.hpp"
#include "Z_Tree_Node.hpp"

BEGIN_ZTC_NAMESPACE

struct BinarySearchTreeIterator
{
	typedef bidirectional_iterator_tag iterator_category;

	TreeNodeBase* m_pNode;
	void Increment()
	{
		if(m_pNode->m_pRight != 0)
		{
			m_pNode->m_pRight;
			while(m_pNode->m_pLeft)
				m_pNode = m_pNode->m_pLeft;
		}
		else
		{
			TreeNodeBase* tmpNode = m_pNode->m_pParent;
			while(m_pNode == tmpNode->m_pRight)
			{
				m_pNode = tmpNode;
				tmpNode = m_pNode->m_pParent;
			}
			m_pNode = tmpNode;
		}
	}

	void Decrement()
	{
		if(m_pNode->m_pLeft != 0)
		{
			m_pNode = m_pNode->m_pLeft;
			while(m_pNode->m_pLeft != 0)
			{
				m_pNode = m_pNode->m_pLeft;
			}
		}
		else if(m_pNode->m_pRight != 0)
		{
			m_pNode = m_pNode->m_pRight;
			while(m_pNode->m_pLeft != 0)
			{
				m_pNode = m_pNode->m_pLeft;
			}
		}
		else
		{
			TreeNodeBase* tmpNode = m_pNode->m_pParent;
			if(m_pNode == tmpNode->m_pLeft)
			{
				m_pNode = tmpNode;
			}
			else
			{
				TreeNodeBase* tmpNode = m_pNode->m_pParent;
				while(m_pNode == tmpNode->m_pRight)
				{
					m_pNode = tmpNode;
					tmpNode = tmpNode->m_pParent;
				}
				m_pNode = tmpNode;
			}
		}
	}
};

template <class Value, class Ref, class Ptr>
struct TreeIterator : public BinarySearchTreeIterator
{
	typedef TreeIterator<Value, Value&, Value*> iterator;

	TreeIterator(){}
	
	TreeIterator(TreeNode<Value> *treeNode)
	{
		this->m_pNode = treeNode;
	}
	
	TreeIterator(const iterator& it)
	{
		this->m_pNode = it.m_pNode;
	}

	Ref operator*() const
	{
		return (TreeNode<Value>*)m_pNode->m_value;
	}

	Ptr operator->() const
	{
		return &(operator*());
	}

	//TreeIterator<Value, Ref, Ptr> 
};

END_ZTC_NAMESPACE

#endif //ZTC__ALGORITHM_INCLUDE__Z_Binary_Search_TREE_ITERATOR_HPP