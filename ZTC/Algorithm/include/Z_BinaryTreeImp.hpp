#ifndef ZTC_ALGORITHM_Z_BINARYTREEIMP_HPP
#define ZTC_ALGORITHM_Z_BINARYTREEIMP_HPP

#include <iostream>
#include <cmath>
#include <vector>

namespace ZTC
{
	template <typename ElemType>
	struct ZBinaryTreeNode
	{
		ElemType data;
		ZBinaryTreeNode<ElemType>* leftTreeNode;
		ZBinaryTreeNode<ElemType>* rightTreeNode;
		unsigned int index;

		ZBinaryTreeNode(): data(ElemType()), leftTreeNode(NULL), rightTreeNode(NULL), index(0xFFFF){}
	};

	template <typename ElemType>
	class BinaryTreeImp
	{
	private:
		enum NodeFlag{
			LeftNode = 0,
			RightNode
		};
		enum NodeNum {
			CapacityNum = 600
		};
	public:

		explicit BinaryTreeImp():m_pBinaryTree(NULL), m_actualNodeNum(0), m_nowMaxIndexNo(0),m_userDefineCapactyNum(0)
		{}

		/*
		 * 第一参数表示头节点，第二个参数表示树节点的总个数
		 **/
		explicit BinaryTreeImp(ElemType nodeData, unsigned int num = 100) : m_pBinaryTree(NULL), m_actualNodeNum(0), m_nowMaxIndexNo(0),m_userDefineCapactyNum(num)
		{
			InitDataMemeber(num);
			CreateBinaryTree(nodeData);
			AssigentIndex();
		}
		BinaryTreeImp(const BinaryTreeImp<ElemType> &other):m_pBinaryTree(NULL), m_actualNodeNum(0), m_userDefineCapactyNum(0)
		{
			ReleaseDataMember();
			m_userDefineCapactyNum = other.m_userDefineCapactyNum;
			InitDataMemeber(m_userDefineCapactyNum);
			PushLeftNode(other.m_pBinaryTree[0]);  //从other的头结点开始添加
			AssigentIndex();
		}
		BinaryTreeImp<ElemType>& operator= (const BinaryTreeImp<ElemType> &other)
		{
			if(this == &other)
				return *this;

			m_actualNodeNum = 0;
			m_userDefineCapactyNum = other.m_userDefineCapactyNum;
			ReleaseDataMember();
			InitDataMemeber(m_userDefineCapactyNum);
			PushLeftNode(other.m_pBinaryTree[0]);  //从other的头结点开始添加
			AssigentIndex();
			return *this;
		}

		~BinaryTreeImp()
		{
			ReleaseDataMember();
		}

		ZBinaryTreeNode<ElemType>*getNode(unsigned long index)
		{
			return &m_pBinaryTree[index];
		}

		/*****
		 * 注意：如果待添加的节点有左子树或右子树则也会被添加进当前树里面
		 **/
		bool PushLeftNode(const ZBinaryTreeNode<ElemType> &treeNode)
		{
			 if(PushNode(treeNode, LeftNode))
			 {
				 ResetIndex();
				 AssigentIndex();
				 return true;
			 }
			 else
				 return false;
		}

		bool PushLeftNode(const ElemType &treeNodeData)
		{
			if(PushNode(m_actualNodeNum - 1, treeNodeData, LeftNode))
			{
				ResetIndex();
				AssigentIndex();
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool PushLeftNode(unsigned long index, const ElemType &treeNodeData)
		{
			if(PushNode(index, treeNodeData, LeftNode))
			{
				ResetIndex();
				AssigentIndex();
				return true;
			}
			else
			{
				return false;
			}
		}

		bool PushRightNode(const ZBinaryTreeNode<ElemType> &treeNode)
		{
			if(PushNode(treeNode, RightNode))
			{
				ResetIndex();
				AssigentIndex();
				return true;
			}
			else
			{
				return false;
			}
		}

		bool PushRightNode(const ElemType &treeNodeData)
		{
			 if(PushNode(m_actualNodeNum - 1, treeNodeData, RightNode))
			 {
				 ResetIndex();
				 AssigentIndex();
				 return true;
			 }
			 else
			 {
				 return false;
			 }
		}

		bool PushRightNode(unsigned long index, const ElemType &treeNodeData)
		{
			if(PushNode(index, treeNodeData, RightNode))
			{
				ResetIndex();
				AssigentIndex();
				return true;
			}
			else
			{
				return false;
			}
		}

		bool IsEmpty()
		{
			return (m_actualNodeNum == 0);
		}

		unsigned long Size()
		{
			return m_actualNodeNum;
		}

		unsigned long GetResidualCapacity()
		{
			return m_userDefineCapactyNum - m_actualNodeNum;
		}
		unsigned long GetCapacity()
		{
			return m_userDefineCapactyNum;
		}

		/*--@
		* 调用此函数时请保证树是一颗完全二叉树
		*/
		unsigned long GetParentIndex(unsigned long index)
		{
			if(0 == index)
				return 0;
			return (index + 1)/2 - 1;
		}

		/*--@
		* 调用此函数时请保证树是一颗完全二叉树
		*/
		unsigned long GetLeftIndex(unsigned long index)
		{
			return 2*index + 1;
		}

		/*--@
		* 调用此函数时请保证树是一颗完全二叉树
		*/
		unsigned long GetRightIndex(unsigned long index)
		{
			return 2 * index + 2;
		}
		
		/**********
		 ** 判断是否为完全二叉树
		 ****/
		bool IsCompleteTree()
		{
			for(unsigned int i = 0; i<m_actualNodeNum; ++i)
			{
				if((m_pBinaryTree[i].leftTreeNode && !m_pBinaryTree[i].rightTreeNode)
					||(!m_pBinaryTree[i].leftTreeNode && m_pBinaryTree[i].rightTreeNode))
					return false;
			}
			return true;
		}

		/**********
		 ** 判断是否为满二叉树
		 ****/
		bool IsFullyTree()
		{
			if(!IsCompleteTree())
				return false;

			int leep = 0;
			Leep(m_pBinaryTree[0], leep);//从头节点开始遍历，获得层数
			int h = (int)(log10((double)m_actualNodeNum + 1) / log10((double)2)); //如果是满二叉树，层数为 log10(m_actualNodeNum + 1) / log10(2)
			if(leep != h - 1)
				return false;

			return true;
		}

		void PreOrderTraverse(std::vector<ElemType> &elemArray)  //先序遍历
		{
			PreOrderTraverse(m_pBinaryTree[0], elemArray);
		}

		void InOrderTraverse(std::vector<ElemType> &elemArray)  //中序遍历
		{
			InOrderTraverse(m_pBinaryTree[0], elemArray);
		}

		void PostOrderTraverse(std::vector<ElemType> &elemArray) //后
		{
			PostOrderTraverse(m_pBinaryTree[0], elemArray);
		}

		/******
		 * 将索引号为index的节点的元素置换为elem
		 **/
		void Assigment(unsigned int index, const ElemType &elem)
		{

		}

	private:
		typedef unsigned long ulong;
		typedef unsigned int uint32;
	private:

		void InitDataMemeber(unsigned int num)
		{
			if(num > 0)
			{
				m_pBinaryTree = new ZBinaryTreeNode<ElemType>[num];
			}
			else
			{
				m_pBinaryTree = NULL;
			}
		}
		void ReleaseDataMember()
		{
			//先释放额外分配的资源
			if(m_userDefineCapactyNum > 0)
			{
				if(m_pBinaryTree[m_userDefineCapactyNum - 1].leftTreeNode)
				{
					ReleaseBinaryTree(m_pBinaryTree[m_userDefineCapactyNum - 1].leftTreeNode);
				}
			}
			if(m_pBinaryTree)
			{
				delete [] m_pBinaryTree;
				m_pBinaryTree = NULL;
			}
		}

		void ReleaseBinaryTree(ZBinaryTreeNode<ElemType> *&pBinaryTreeNode)
		{
			if(pBinaryTreeNode && pBinaryTreeNode->leftTreeNode)
			{
				ReleaseBinaryTree(pBinaryTreeNode->leftTreeNode);
			}
			if(pBinaryTreeNode && pBinaryTreeNode->rightTreeNode)
			{
				ReleaseBinaryTree(pBinaryTreeNode->rightTreeNode);
			}

			if(pBinaryTreeNode)
			{
				delete pBinaryTreeNode;
				pBinaryTreeNode = NULL;
			}
		}

		/*
		 *返回没有增加之前的数目
		 **/
		ulong IncreaseAcualNodeNum()
		{
			++m_actualNodeNum;
			return m_actualNodeNum - 1;
		}

		bool PushNode(unsigned long index, const ElemType &treeNodeData, NodeFlag nodeFlag = LeftNode)
		{
			if(m_actualNodeNum - 1 < index)
				return false;

			if(nodeFlag == LeftNode && m_pBinaryTree[index].leftTreeNode)
				return false;

			if(nodeFlag == RightNode && m_pBinaryTree[index].rightTreeNode)
				return false;

			if(m_actualNodeNum < CapacityNum - 1)
			{
				m_pBinaryTree[m_actualNodeNum].data = treeNodeData;
				m_pBinaryTree[m_actualNodeNum].leftTreeNode = NULL;
				m_pBinaryTree[m_actualNodeNum].rightTreeNode = NULL;
				m_pBinaryTree[m_actualNodeNum].index = m_actualNodeNum;

				if(nodeFlag == LeftNode)
					m_pBinaryTree[index].leftTreeNode = &m_pBinaryTree[m_actualNodeNum];
				if(nodeFlag == RightNode)
					m_pBinaryTree[index].rightTreeNode = &m_pBinaryTree[m_actualNodeNum];
			}
			/*else
			{
				ZBinaryTreeNode<ElemType>* pAddTreeNode = new ZBinaryTreeNode<ElemType>();
				pAddTreeNode->data = treeNodeData;
				pAddTreeNode->leftTreeNode = NULL;
				pAddTreeNode->rightTreeNode = NULL;

				if(nodeFlag == LeftNode)
					m_pBinaryTree[index].leftTreeNode = pAddTreeNode;
				if(nodeFlag == RightNode)
					m_pBinaryTree[index].rightTreeNode = pAddTreeNode;
 			}*/
			
			IncreaseAcualNodeNum();
			return true;
		}

		bool PushNode(const ZBinaryTreeNode<ElemType> &treeNode, NodeFlag nodeFlag = LeftNode)
		{
			if(m_actualNodeNum < CapacityNum - 1 && m_actualNodeNum > 0)
			{
				if(nodeFlag == LeftNode)
					m_pBinaryTree[m_actualNodeNum - 1].leftTreeNode = &m_pBinaryTree[m_actualNodeNum];
				if(nodeFlag == RightNode)
					m_pBinaryTree[m_actualNodeNum - 1].rightTreeNode = &m_pBinaryTree[m_actualNodeNum];

				m_pBinaryTree[m_actualNodeNum].data = treeNode.data;
				m_pBinaryTree[m_actualNodeNum].index = m_actualNodeNum;
			}
			if(m_actualNodeNum == 0)
			{
				m_pBinaryTree[m_actualNodeNum].data = treeNode.data;
				m_pBinaryTree[m_actualNodeNum].index = m_actualNodeNum;
			}
			/*else
			{
				ZBinaryTreeNode<ElemType>* pAddTreeNode = new ZBinaryTreeNode<ElemType>();
				if(nodeFlag == LeftNode)
				m_pBinaryTree[m_actualNodeNum - 1].leftTreeNode = pAddTreeNode;
				if(nodeFlag == RightNode)
				m_pBinaryTree[m_actualNodeNum - 1].rightTreeNode = pAddTreeNode;

				pAddTreeNode->data = treeNode.data;
			}*/
			
			IncreaseAcualNodeNum();
			ulong leep = m_actualNodeNum;
			
			if(treeNode.leftTreeNode)
			{
				PushNode(*treeNode.leftTreeNode, LeftNode);
			}
			if(treeNode.rightTreeNode)
			{
				if(treeNode.leftTreeNode)
					PushNode(leep - 1, *treeNode.rightTreeNode, RightNode);
				else
					PushNode(*treeNode.rightTreeNode, RightNode);
			}
			return true;
		}

		bool PushNode(int index, const ZBinaryTreeNode<ElemType> &treeNode, NodeFlag nodeFlag = LeftNode)
		{
			if(m_actualNodeNum < CapacityNum - 1)
			{
				if(nodeFlag == LeftNode)
					m_pBinaryTree[index].leftTreeNode = &m_pBinaryTree[m_actualNodeNum];
				if(nodeFlag == RightNode)
					m_pBinaryTree[index].rightTreeNode = &m_pBinaryTree[m_actualNodeNum];

				m_pBinaryTree[m_actualNodeNum].data = treeNode.data;
				m_pBinaryTree[m_actualNodeNum].index = m_actualNodeNum;
			}
			/*else
			{
				ZBinaryTreeNode<ElemType>* pAddTreeNode = new ZBinaryTreeNode<ElemType>();
				if(nodeFlag == LeftNode)
					m_pBinaryTree[m_actualNodeNum - 1].leftTreeNode = pAddTreeNode;
				if(nodeFlag == RightNode)
					m_pBinaryTree[m_actualNodeNum - 1].rightTreeNode = pAddTreeNode;

				pAddTreeNode->data = treeNode.data;
			}*/

			IncreaseAcualNodeNum();
			ulong leep = m_actualNodeNum;

			if(treeNode.leftTreeNode)
			{
				PushNode(*treeNode.leftTreeNode, LeftNode);
			}
			if(treeNode.rightTreeNode)
			{
				if(treeNode.leftTreeNode)
					PushNode(leep - 1, *treeNode.rightTreeNode, RightNode);
				else
					PushNode(*treeNode.rightTreeNode, RightNode);
			}
			return true;
		}

		void CreateBinaryTree(const ElemType &nodeData)
		{
			m_pBinaryTree[m_actualNodeNum].data = nodeData;
			m_pBinaryTree[m_actualNodeNum].leftTreeNode = NULL;
			m_pBinaryTree[m_actualNodeNum].rightTreeNode = NULL;
			m_pBinaryTree[m_actualNodeNum].index = m_actualNodeNum;
			IncreaseAcualNodeNum();
		}

		void CreateBinaryTree(const ZBinaryTreeNode<ElemType> &treeNode)
		{
			m_pBinaryTree[m_actualNodeNum].data = treeNode.data;
			m_pBinaryTree[m_actualNodeNum].leftTreeNode = NULL;
			m_pBinaryTree[m_actualNodeNum].rightTreeNode = NULL;
			m_pBinaryTree[m_actualNodeNum].index = m_actualNodeNum;
			IncreaseAcualNodeNum();
		}

		void Leep(const ZBinaryTreeNode<ElemType> &treeNode, int &leep)
		{
			if(treeNode.leftTreeNode)
			{
				++leep;
				Leep(*treeNode.leftTreeNode, leep);
			}
		}

		void PreOrderTraverse(const ZBinaryTreeNode<ElemType> &treeNode, std::vector<ElemType> &elemArray)
		{
			elemArray.push_back(treeNode.data);
			if(treeNode.leftTreeNode)
				PreOrderTraverse(*treeNode.leftTreeNode, elemArray);
			if(treeNode.rightTreeNode)
				PreOrderTraverse(*treeNode.rightTreeNode, elemArray);
		}

		void InOrderTraverse(const ZBinaryTreeNode<ElemType> &treeNode, std::vector<ElemType> &elemArray)
		{
			if(treeNode.leftTreeNode)
				InOrderTraverse(*treeNode.leftTreeNode, elemArray);
			elemArray.push_back(treeNode.data);
			if(treeNode.rightTreeNode)
				InOrderTraverse(*treeNode.rightTreeNode, elemArray);
		}

		void PostOrderTraverse(const ZBinaryTreeNode<ElemType> &treeNode, std::vector<ElemType> &elemArray)
		{
			if(treeNode.leftTreeNode)
				PostOrderTraverse(*treeNode.leftTreeNode, elemArray);
			if(treeNode.rightTreeNode)
				PostOrderTraverse(*treeNode.rightTreeNode, elemArray);
			elemArray.push_back(treeNode.data);
		}

		void ResetIndex()
		{
			m_nowMaxIndexNo = 0;
		}

		void AssigentIndex()
		{
			m_nowMaxIndexNo = 0;
			m_pBinaryTree[0].index = m_nowMaxIndexNo;
			for(uint32 i = 0; i<m_actualNodeNum; ++i)
			{
				IndexSortSubNode(m_pBinaryTree[i]);
			}
		}

		void IndexSortSubNode(ZBinaryTreeNode<ElemType>& binaryTreeNode)
		{
			if(binaryTreeNode.leftTreeNode)
			{
				++m_nowMaxIndexNo;
				binaryTreeNode.leftTreeNode->index = m_nowMaxIndexNo;
			}
			if(binaryTreeNode.rightTreeNode)
			{
				++m_nowMaxIndexNo;
				binaryTreeNode.rightTreeNode->index = m_nowMaxIndexNo;
			}
		}

		ZBinaryTreeNode<ElemType>* m_pBinaryTree;
		uint32 m_actualNodeNum;
		unsigned int m_userDefineCapactyNum;
		unsigned int m_nowMaxIndexNo;
	};
}

#endif //ZTC_ALGORITHM_Z_BINARYTREEIMP_HPP