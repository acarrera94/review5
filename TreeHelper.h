#pragma once
#include <stdlib.h>
#include "BinaryTree.h"

template <typename type>
class TreeHelper
{
public:
	TreeHelper() {}
	~TreeHelper() {}

	void ToVectorInOrder(const BinaryTreeNode<type> *node, std::vector<type> &vector)
	{
		if (node == NULL)
			return;

		if (node->Left != NULL)
			ToVectorInOrder(node->Left, vector);

		vector.push_back(node->Data);

		if (node->Right != NULL)
			ToVectorInOrder(node->Right, vector);
	}

	void ToVectorPreOrder(const BinaryTreeNode<type> *node, std::vector<type> &vector)
	{
		if (node == NULL)
			return;

		vector.push_back(node->Data);

		if (node->Left != NULL)
			ToVectorPreOrder(node->Left, vector);

		if (node->Right != NULL)
			ToVectorPreOrder(node->Right, vector);
	}

	void ToVectorPostOrder(const BinaryTreeNode<type> *node, std::vector<type> &vector)
	{
		if (node == NULL)
			return;

		if (node->Left != NULL)
			ToVectorPostOrder(node->Left, vector);

		if (node->Right != NULL)
			ToVectorPostOrder(node->Right, vector);

		vector.push_back(node->Data);
	}
};

