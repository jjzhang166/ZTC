#ifndef ZTC_TEST_TESTALORITHM_H
#define ZTC_TEST_TESTALORITHM_H

#include <iostream>
#include "../ZTC/include/ZStdf.h"
#include "../ZTC/include/ZCommonality.h"
#include "../ZTC/include/ZCommon.hpp"
#include "../ZTC/Algorithm/include/Z_BinaryTreeImp.hpp"
#include "../ZTC/Algorithm/ZBinaryTree.hpp"

using namespace std;
using namespace ZTC;

void TestAlogrithm()
{
	BinaryTreeImp<int> binaryTree(10);
	binaryTree.PushLeftNode(0, 5);
	binaryTree.PushRightNode(0, 8);
	cout<<binaryTree.IsCompleteTree()<<" : "<<binaryTree.IsFullyTree()<<endl;

	ZBinaryTreeNode<int> node1;
	ZBinaryTreeNode<int> node2;
	ZBinaryTreeNode<int> node3;
	ZBinaryTreeNode<int> node4;

	node1.data = 1;
	node2.data = 2;
	node3.data = 3;
	node4.data = 4;
	node1.leftTreeNode = &node2;
	node1.rightTreeNode = &node3;
	//node2.rightTreeNode = &node3;
	//node2.leftTreeNode = &node4;

	binaryTree.PushLeftNode(node1);
	binaryTree.PushRightNode(1, 20);
	cout<<binaryTree.IsEmpty()<<endl;
	cout<<binaryTree.IsCompleteTree()<<" : "<<binaryTree.IsFullyTree()<<endl;
	{
		BinaryTreeImp<int> binaryTree2(binaryTree);
		//BinaryTreeImp<int> binaryTree3 = binaryTree2;
	}

#ifdef ZTC_TERMINAL_PUT_OUT

	std::vector<int> preElemArray;
	binaryTree.PreOrderTraverse(preElemArray);
	PutOut(preElemArray);

	std::vector<int> inElemArray;
	binaryTree.InOrderTraverse(inElemArray);
	PutOut(inElemArray);

	std::vector<int> endElemArray;
	binaryTree.PostOrderTraverse(endElemArray);
	PutOut(endElemArray);

#endif //ZTC_TERMINAL_PUT_OUT
}

void TestAlogrithm1()
{
	ZTC::ZBinaryTree<int> binaryTree12;
	cout<<"空的："<<binaryTree12.IsEmpty()<<endl;
	ZTC::ZBinaryTree<int> binaryTree(10);
	binaryTree.PushLeftNode(0, 5);
	binaryTree.PushRightNode(0, 8);
	cout<<binaryTree.IsCompleteTree()<<" : "<<binaryTree.IsFullyTree()<<endl;

	ZBinaryTreeNode<int> node1;
	ZBinaryTreeNode<int> node2;
	ZBinaryTreeNode<int> node3;
	ZBinaryTreeNode<int> node4;

	node1.data = 1;
	node2.data = 2;
	node3.data = 3;
	node4.data = 4;
	node1.leftTreeNode = &node2;
	//node1.rightTreeNode = &node3;
	//node2.rightTreeNode = &node3;
	//node2.leftTreeNode = &node4;

	binaryTree.PushLeftNode(node1);
	binaryTree.PushRightNode(2, 20);
	binaryTree.PushLeftNode(4, 50);
	cout<<binaryTree.IsEmpty()<<endl;
	cout<<binaryTree.IsCompleteTree()<<" : "<<binaryTree.IsFullyTree()<<endl;

#ifdef ZTC_TERMINAL_PUT_OUT

	std::vector<int> preElemArray;
	binaryTree.PreOrderTraverse(preElemArray);
	PutOut(preElemArray);

	std::vector<int> inElemArray;
	binaryTree.InOrderTraverse(inElemArray);
	PutOut(inElemArray);

	std::vector<int> endElemArray;
	binaryTree.PostOrderTraverse(endElemArray);
	PutOut(endElemArray);

	{
		ZBinaryTree<int> binaryTree2(binaryTree);
		ZBinaryTree<int> binaryTree3 = binaryTree2;

		std::vector<int> preElemArray2;
		binaryTree.PreOrderTraverse(preElemArray2);
		PutOut(preElemArray2);
	}
#endif //ZTC_TERMINAL_PUT_OUT
}


#define MAX_BONUS 2600
#define MIDDLE_BONUS 650
#define MIN_BONUS 130

struct Bonus
{
	int m_bonusValues;
	int m_number;
	char m_identifier[20];
};

void updateTreeNodeValue(ZBinaryTreeNode<Bonus>* &pRootNode)
{
	if(pRootNode->leftTreeNode != NULL)
	{
		while(pRootNode->leftTreeNode->leftTreeNode)
		{
			updateTreeNodeValue(pRootNode->leftTreeNode);
			break;
		}
	}

	if(pRootNode->rightTreeNode != NULL)
	{
		while(pRootNode->rightTreeNode->rightTreeNode)
		{
			updateTreeNodeValue(pRootNode->rightTreeNode);
			break;
		}
	}

	if(pRootNode->leftTreeNode == NULL || pRootNode->rightTreeNode == NULL)
		return;

	pRootNode->data.m_number = (std::min)(pRootNode->leftTreeNode->data.m_number, pRootNode->rightTreeNode->data.m_number);
	pRootNode->data.m_bonusValues = pRootNode->data.m_number;
}

void updateTreeValue(ZTC::ZBinaryTree<Bonus> &tree)
{
	ZBinaryTreeNode<Bonus>* pRootNode = tree.getNode(0);

	updateTreeNodeValue(pRootNode);
}

void TestAlogrithm2()
{
	Bonus root;
	strcpy(root.m_identifier, "%");
	ZTC::ZBinaryTree<Bonus> bonusTree(root, 200);

	while(true)
	{
		//格式： nodeIndex,LeftOrRightChild:value
		//	nodeIndex从0（表示根节点）开始
		//  leftChild：-1表示
		//  rightChild: 1表示
		cout <<"请输入要添加的绩效(格式：2:1:2600)： "<<endl;
		std::string str;
		cin >> str;
		std::vector<string> veStr;
		ZTC::SplitBaseOnSingleChar(str, ":", veStr);

		if(veStr.size() > 3)
		{
			cout<<"格式不正确！请重新输入！"<<endl;
			return;
		}

		int index = atoi(veStr[0].c_str());
		int child = atoi(veStr[1].c_str());
		int value = atoi(veStr[2].c_str());

		Bonus childNode;
		childNode.m_number = value;
		switch(value)
		{
		case 2600:
			strcpy(childNode.m_identifier, "$");break;
		case 650:
			strcpy(childNode.m_identifier, "&");break;
		case 130:
			strcpy(childNode.m_identifier, "*");break;
		default:
			strcpy(childNode.m_identifier, "");
		}

		switch(child)
		{
		case -1:
			bonusTree.PushLeftNode(index, childNode);
			break;
		case 1:
			bonusTree.PushRightNode(index, childNode);
			break;
		}

		updateTreeValue(bonusTree);
	}
}

#endif // ZTC_TEST_TESTALORITHM_H