/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : Z_Binary_Search_Tree.hpp
* File Identifier :
* Abstract        :	¶þ²æËÑË÷Ê÷
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.11.21 22:2:55
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.11.21 22:2:55
*/

#ifndef ZTC_ALGORITHM_INCLUDE_Z_BINARY_SEARCH_TREE_HPP
#define ZTC_ALGORITHM_INCLUDE_Z_BINARY_SEARCH_TREE_HPP

#include "Z_Tree_Node.hpp"
#include "Z_Allocate.hpp"

BEGIN_ZTC_NAMESPACE

template <typename ElemType, class Alloc = ZAllocate>
class BinarySearchTree
{
public:
	typedef size_t size_type;
	typedef ElemType* iterator;


public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<ElemType>& other);
	BinarySearchTree<ElemType> & operator=(const BinarySearchTree<ElemType>& other);
	~BinarySearchTree();

	bool IsEmpty();
	bool GetTreeSize();

	

private:
	TreeNodeBase *m_pBinarySearhTreeHeader;
	size_type m_nodeCount;
};

template<typename ElemType>
BinarySearchTree::BinarySearchTree():m_pBinarySearchTree(NULL)
{

}

template<typename ElemType>
BinarySearchTree::BinarySearchTree(const BinarySearchTree<ElemType>& other) : m_pBinarySearchTree(NULL)
{

}

template<typename ElemType>
BinarySearchTree<ElemType>& BinarySearchTree::operator= (const BinarySearchTree<ElemType>& other)
{

}

template<typename ElemType>
BinarySearchTree::~BinarySearchTree()
{
	if(m_pBinarySeachTree)
	{
		m_pBinarySeachTree = NULL;
	}
}

//template<typename ElemType>

END_ZTC_NAMESPACE
#endif //ZTC_ALGORITHM_INCLUDE_Z_BINARY_SEARCH_TREE_HPP