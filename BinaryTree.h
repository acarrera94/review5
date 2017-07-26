#pragma once

#include <vector>




template <typename type>
class BinaryTree
{
private:
    struct BinaryTreeNode
    {
    public:
        type Data;
        BinaryTreeNode *Left;
        BinaryTreeNode *Right;
        
        BinaryTreeNode(const type& data) :
        Data(data),
        Left(NULL),
        Right(NULL)
        {}
        
        type& GetData()
        {
            return Data;
        }
        
    };
    
    BinaryTreeNode *_root;
	int _count;

public:
	BinaryTree() :
		_root(NULL),
		_count(0)
	{}


	// Make sure you clean up everything in the destructor.  THe easiest way to
	// do this is to call the Clear() method.
	~BinaryTree()
	{
	}


	// This method returns a pointer to the root tree-node.
	BinaryTreeNode *GetRoot()
	{
		return _root;
	}


	// This method will add a new item to the tree.  You need to check for 
	// duplicates.  If you find a duplicate, you should throw an exception.
	void Add(const type& newItem)
	{
	}


	// This method should remove an item from the tree.  You'll need to traverse
	// the tree until you find the item, then remove the item.  If the item is
	// not in the tree, then throw an exception.
	void Remove(const type &value)
	{
	}


	// This method should return a count of how many items are in your tree.
	int Count()
	{
        return 0;
	}


	// This method will return a true if the item is a member of the tree, and 
	// false if the item is not in the tree.
	bool Contains(const type &value)
    {return true;
	}


	// THis method will delete all the nodes in the tree and reset the count to
	// zero.
	void Clear()
	{
	}
};
