/*
* Copyright (c) 2013 ZZ(Ø¼Quit__¡£)
* All rights reserved.
* 
* File Name       : TreeNode.hpp
* File Identifier :
* Abstract        :
* 
* Current Version : 1.0
* Author          : ZZ(Ø¼Quit__¡£)
* Completion Date : 2013.11.21 22:13:2
*
* Replace Version : 
* Original Author :
* Completion Date : 2013.11.21 22:13:2
*/

#ifndef ZTC_ALGORITHM_INCLUDE_Z_TREENODE_HPP
#define ZTC_ALGORITHM_INCLUDE_Z_TREENODE_HPP

#include "../../include/ZMacroDefine.h"

BEGIN_ZTC_NAMESPACE

struct TreeNodeBase
{
	TreeNodeBase *m_pLeft;
	TreeNodeBase *m_pRight;
	TreeNodeBase *m_pParent;

	static TreeNodeBase* minimum(TreeNodeBase* pNode)
	{
		while(pNode->m_pLeft)
			pNode = pNode->m_pLeft;
		return pNode;
	}

	static TreeNodeBase* maximum(TreeNodeBase* pNode)
	{
		while(pNode->m_pRight)
			pNode = pNode->m_pRight;
		return pNode;
	}
};

template <class ElemType>
struct TreeNode : public TreeNodeBase
{
	ElemType m_value;
};

END_ZTC_NAMESPACE

#endif //ZTC_ALGORITHM_INCLUDE_Z_TREENODE_HPP