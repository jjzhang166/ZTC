/*
* Copyright (c) 2013 ZZ
* All rights reserved.
* 
* File Name       : ZBinaryTree.hpp
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ
* Completion Date : 2013.11.2 14:11:54
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.11.2 14:11:54
*/

#ifndef ZTC_ALGORITHM_ZBINARYTREE_HPP
#define ZTC_ALGORITHM_ZBINARYTREE_HPP

#include "include/Z_BinaryTreeImp.hpp"

namespace ZTC
{
	template <typename ElemType>
	class ZBinaryTree
	{
	public:

		explicit ZBinaryTree() :m_binaryTree(BinaryTreeImp<ElemType>())
		{
		}

		explicit ZBinaryTree(ElemType nodeData, unsigned int num = 100) :m_binaryTree(BinaryTreeImp<ElemType>(nodeData, num))
		{
		}

		ZBinaryTree(const ZBinaryTree<ElemType> &other): m_binaryTree(other.m_binaryTree)
		{

		}

		ZBinaryTree<ElemType> & operator =(const ZBinaryTree<ElemType> &other)
		{
			if(this == &other)
				return *this;
			m_binaryTree = other.m_binaryTree;
		}

		~ZBinaryTree()
		{

		}

		ZBinaryTreeNode<ElemType>*getNode(unsigned long index)
		{
			return m_binaryTree.getNode(index);
		}

		bool PushLeftNode(const ZBinaryTreeNode<ElemType> &treeNode)
		{
			return m_binaryTree.PushLeftNode(treeNode);
		}
		bool PushLeftNode(const ElemType &treeNodeData)
		{
			return m_binaryTree.PushLeftNode(treeNodeData);
		}
		bool PushLeftNode(unsigned long index, const ElemType &treeNodeData)
		{
			return m_binaryTree.PushLeftNode(index, treeNodeData);
		}
		bool PushRightNode(const ZBinaryTreeNode<ElemType> &treeNode)
		{
			return m_binaryTree.PushRightNode(treeNode);
		}

		bool PushRightNode(const ElemType &treeNodeData)
		{
			return m_binaryTree.PushRightNode(treeNodeData);
		}

		bool PushRightNode(unsigned long index, const ElemType &treeNodeData)
		{
			return m_binaryTree.PushRightNode(index, treeNodeData);
		}

		bool IsEmpty()
		{
			return m_binaryTree.IsEmpty();
		}

		unsigned long Size()
		{
			return m_binaryTree.Size();
		}

		unsigned long GetResidualCapacity()
		{
			return m_binaryTree.GetResidualCapacity();
		}
		unsigned long GetCapacity()
		{
			return m_binaryTree.GetCapacity();
		}

		unsigned long GetParentIndex(unsigned long index)
		{
			return m_binaryTree.GetParentIndex(index);
		}

		unsigned long GetLeftIndex(unsigned long index)
		{
			return m_binaryTree.GetLeftIndex(index);
		}

		unsigned long GetRightIndex(unsigned long index)
		{
			return m_binaryTree.GetRightIndex(index);
		}
		
		/**********
		 ** 判断是否为完全二叉树
		 ****/
		bool IsCompleteTree()
		{
			return m_binaryTree.IsCompleteTree();
		}

		/**********
		 ** 判断是否为满二叉树
		 ****/
		bool IsFullyTree()
		{
			return m_binaryTree.IsFullyTree();
		}

		void PreOrderTraverse(std::vector<ElemType> &elemArray)  //先序遍历
		{
			m_binaryTree.PreOrderTraverse(elemArray);
		}

		void InOrderTraverse(std::vector<ElemType> &elemArray)  //中序遍历
		{
			m_binaryTree.InOrderTraverse(elemArray);
		}

		void PostOrderTraverse(std::vector<ElemType> &elemArray) //后
		{
			m_binaryTree.PostOrderTraverse(elemArray);
		}

	private:
		BinaryTreeImp<ElemType> m_binaryTree;
	};
}

#endif //ZTC_ALGORITHM_ZBINARYTREE_HPP