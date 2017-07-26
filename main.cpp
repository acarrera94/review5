#include <exception>
#include <string>
#include <sstream>

using namespace std;

#include "TestCase.h"
#include "BinaryTree.h"
#include "TreeHelper.h"

struct CounterClass
{
	static int InstanceCount;

	int Data;

	CounterClass() : Data(0) { InstanceCount++; }
	CounterClass(int data) : Data(data) { InstanceCount++; }
	CounterClass(const CounterClass& other) : Data(other.Data) { InstanceCount++; }

	~CounterClass() { InstanceCount--; }

	bool operator==(const CounterClass& other) const { return Data == other.Data; }
	bool operator!=(const CounterClass& other) const { return Data != other.Data; }
	bool operator<(const CounterClass& other) const { return Data < other.Data; }
	bool operator>(const CounterClass& other) const { return Data > other.Data; }
};

int CounterClass::InstanceCount = 0;




void __ValidateVector(TestCase &tc, int expected[], int len, vector<CounterClass> &v)
{
	tc.AssertEquals(len, v.size(), "Make sure the tree has the expected number of items.");

	int min = len;
	if (min > v.size())
		min = v.size();

	int i;
	for (i = 0; i < min; i++)
	{
		stringstream ss;
		ss << "Check item at index " << i;
		tc.AssertEquals(expected[i], v[i].Data, ss.str().c_str());
	}

	for (; i < len; i++)
	{
		stringstream ss;
		ss << "Missing item " << expected[i] << " at position " << i;
		tc.LogResult(false, ss.str().c_str());
	}

	for (; i < v.size(); i++)
	{
		stringstream ss;
		ss << "Found extra item " << v[i].Data << " at position " << i;
		tc.LogResult(false, ss.str().c_str());
	}
}


//##############################################################################
//###   Basic tests
//##############################################################################

/**************************************/
void TestCreateEmptyTree()
{
	TestCase tc("Test creating an empty tree.");

	try
	{
		BinaryTree<CounterClass> tree;

		tc.AssertEquals(0, tree.Count(), "Make sure count is 0 on empty tree.");
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure there are no orphaned instances of CounterClass.");
}



/**************************************/
void TestCallClearOnAnEmptyTree()
{
	TestCase tc("Test calling the Clear method on an empty tree.");

	try
	{
		BinaryTree<CounterClass> tree;
		tree.Clear();

		tc.AssertEquals(0, tree.Count(), "Make sure count is 0 on empty tree.");
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure there are no orphaned instances of CounterClass.");
}


/**************************************/
void TestToVectorPreOrderEmpty()
{
	TestCase tc("Test dumping an empty tree to a vector.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;

		tc.AssertEquals(0, tree.Count(), "Make sure node count is 0.");

		int *expected = NULL;
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 0, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}




//##############################################################################
//###   Add
//##############################################################################

/**************************************/
void TestAddOneNode()
{
	TestCase tc("Test adding one node.");

	try
	{
		BinaryTree<CounterClass> tree;
		tree.Add(10);

		tc.AssertEquals(1, tree.Count(), "Make sure count is 1.");
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestAddOneDumpToVector()
{
	TestCase tc("Test adding one node and dumping to a vector.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);

		tc.AssertEquals(1, tree.Count(), "Make sure count is 1 after adding a node.");

		int expected[] = { 10 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 1, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestAddThreeItemsLeftHeavy()
{
	TestCase tc("Test adding three items in reverse order.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);
		tree.Add(8);
		tree.Add(6);

		tc.AssertEquals(3, tree.Count(), "Make sure count is 3 after adding test nodes.");

		int expected[] = { 6, 8, 10 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 3, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestAddThreeItemsRightHeavy()
{
	TestCase tc("Test adding three items in order.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(6);
		tree.Add(8);
		tree.Add(10);

		tc.AssertEquals(3, tree.Count(), "Make sure count is 3 after adding test nodes.");

		int expected[] = { 6, 8, 10 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 3, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestAddThreeItemsBalanced()
{
	TestCase tc("Test adding three items in balanced order.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(8);
		tree.Add(6);
		tree.Add(10);

		tc.AssertEquals(3, tree.Count(), "Make sure count is 3 after adding test nodes.");

		int expected[] = { 6, 8, 10 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 3, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestAddSevenItemsBalanced()
{
	TestCase tc("Test adding three items in balanced order.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(5);
		tree.Add(3);
		tree.Add(7);
		tree.Add(2);
		tree.Add(4);
		tree.Add(6);
		tree.Add(8);

		tc.AssertEquals(7, tree.Count(), "Make sure count is 7 after adding test nodes.");

		int expected[] = { 2, 3, 4, 5, 6, 7, 8 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 7, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestAddDuplicateRoot()
{
	TestCase tc("Test adding a duplicate node at the root.");

	try
	{
		BinaryTree<CounterClass> tree;
		tree.Add(10);

		try
		{
			tree.Add(10);
			tc.LogResult(false, "Adding a duplicate item did not throw an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(true, "Adding a duplicate item threw an exception.");
		}

		tc.AssertEquals(1, tree.Count(), "Make sure count is 1.");
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestAddDuplicateDeep()
{
	TestCase tc("Test adding a duplicate node deep in the tree.");

	try
	{
		BinaryTree<CounterClass> tree;
		tree.Add(5);
		tree.Add(3);
		tree.Add(7);
		tree.Add(2);
		tree.Add(4);
		tree.Add(6);
		tree.Add(8);

		try
		{
			tree.Add(6);
			tc.LogResult(false, "Adding a duplicate item did not throw an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(true, "Adding a duplicate item threw an exception.");
		}

		tc.AssertEquals(7, tree.Count(), "Make sure count is 7.");
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


//##############################################################################
//###   Delete
//##############################################################################

/**************************************/
void TestDeleteFromEmptyTree()
{
	TestCase tc("Test remove from an empty tree.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;

		tc.AssertEquals(0, tree.Count(), "Make sure node count is 0.");

		try
		{
			tree.Remove(234);
			tc.LogResult(false, "Trying to remove a node should have thrown an exception.");
		}
		catch (exception ex)
		{
			tc.LogResult(true, "Trying to remove a node threw an exception.");
		}
		tc.AssertEquals(0, tree.Count(), "Make sure node count is still 0.");

		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, NULL, 0, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestDeleteRootNode()
{
	TestCase tc("Test delete last item in the tree (root item, no children).");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);

		tc.AssertEquals(1, tree.Count(), "Make sure count is 1 after adding a node.");

		int expected[] = { 10 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 1, v);

		tree.Remove(10);
		tc.LogResult(true, "Deleting the node did not throw an exception.");
		tc.AssertEquals(0, tree.Count(), "Make sure node count is 0.");

		v.clear();
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, NULL, 0, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestDeleteLeftChildLeaf()
{
	TestCase tc("Test delete the left child, which is a leaf node.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);
		tree.Add(5);

		tc.AssertEquals(2, tree.Count(), "Make sure count is 2 after adding test nodes.");

		int expectedBefore[] = { 5, 10 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedBefore, 2, v);

		tree.Remove(5);
		tc.LogResult(true, "One item deleted.");
		tc.AssertEquals(1, tree.Count(), "Make sure node count is 1.");

		int expectedAfter[] = { 10 };
		v.clear();
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedAfter, 1, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestDeleteRightChildLeaf()
{
	TestCase tc("Test delete the right child, which is a leaf node.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);
		tree.Add(15);

		tc.AssertEquals(2, tree.Count(), "Make sure count is 2 after adding test nodes.");

		int expectedBefore[] = { 10, 15 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedBefore, 2, v);

		tree.Remove(15);
		tc.LogResult(true, "One item deleted.");
		tc.AssertEquals(1, tree.Count(), "Make sure node count is 1.");

		int expectedAfter[] = { 10 };
		v.clear();
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedAfter, 1, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestDeleteRootWithOneLeftChild()
{
	TestCase tc("Test delete the root node, with one left child leaf.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);
		tree.Add(5);

		tc.AssertEquals(2, tree.Count(), "Make sure count is 2 after adding test nodes.");

		int expectedBefore[] = { 5, 10 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedBefore, 2, v);

		tree.Remove(10);
		tc.LogResult(true, "Root node deleted.");
		tc.AssertEquals(1, tree.Count(), "Make sure node count is 1.");

		int expectedAfter[] = { 5 };
		v.clear();
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedAfter, 1, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestDeleteRootWithOneRightChild()
{
	TestCase tc("Test delete the root node, with one right child leaf.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);
		tree.Add(15);

		tc.AssertEquals(2, tree.Count(), "Make sure count is 2 after adding test nodes.");

		int expectedBefore[] = { 10, 15 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedBefore, 2, v);

		tree.Remove(10);
		tc.LogResult(true, "Root node deleted.");
		tc.AssertEquals(1, tree.Count(), "Make sure node count is 1.");

		int expectedAfter[] = { 15 };
		v.clear();
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedAfter, 1, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestDeleteRootWithLeftAndRightChild()
{
	TestCase tc("Test delete the root node, with a right and left child.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);
		tree.Add(5);
		tree.Add(15);

		tc.AssertEquals(3, tree.Count(), "Make sure count is 3 after adding test nodes.");

		int expectedBefore[] = { 5, 10, 15 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedBefore, 3, v);

		tree.Remove(10);
		tc.LogResult(true, "Root node deleted.");
		tc.AssertEquals(2, tree.Count(), "Make sure node count is 2.");

		int expectedAfter[] = { 5, 15 };
		v.clear();
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedAfter, 2, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestDeleteMiddleWithRightRighttChild()
{
	TestCase tc("Test delete the middle node in a right-right tree.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(10);
		tree.Add(15);
		tree.Add(20);

		tc.AssertEquals(3, tree.Count(), "Make sure count is 3 after adding test nodes.");

		int expectedBefore[] = { 10, 15, 20 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedBefore, 3, v);

		tree.Remove(15);
		tc.LogResult(true, "Root node deleted.");
		tc.AssertEquals(2, tree.Count(), "Make sure node count is 2.");

		int expectedAfter[] = { 10, 20 };
		v.clear();
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedAfter, 2, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestDeleteMiddleWithRightLeftChild()
{
	TestCase tc("Test delete the middle node in a right-left tree.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(5);
		tree.Add(10);
		tree.Add(15);
		tree.Add(12);
		tree.Add(13);

		tc.AssertEquals(5, tree.Count(), "Make sure count is 5 after adding test nodes.");

		int expectedBefore[] = { 5, 10, 12, 13, 15 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedBefore, 5, v);

		tree.Remove(10);
		tc.LogResult(true, "Root node deleted.");
		tc.AssertEquals(4, tree.Count(), "Make sure node count is 4.");

		int expectedAfter[] = { 5, 12, 13, 15 };
		v.clear();
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expectedAfter, 4, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


//##############################################################################
//###   Search
//##############################################################################

/**************************************/
void TestSearch()
{
	TestCase tc("Test searching the tree.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(50);
		tree.Add(30);
		tree.Add(70);
		tree.Add(20);
		tree.Add(40);
		tree.Add(60);
		tree.Add(80);

		tc.AssertEquals(7, tree.Count(), "Make sure count is 7 after adding test nodes.");

		int expected[] = { 20, 30, 40, 50, 60, 70, 80 };
		vector<CounterClass> v;
		treeHelper.ToVectorInOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 7, v);

		tc.Assert(tree.Contains(50), "Make sure the root value 50 is present.");
		tc.Assert(tree.Contains(30), "Make sure 30 is present.");
		tc.Assert(tree.Contains(70), "Make sure 70 is present.");
		tc.Assert(tree.Contains(20), "Make sure 20 is present.");
		tc.Assert(tree.Contains(40), "Make sure 40 is present.");
		tc.Assert(tree.Contains(60), "Make sure 60 is present.");
		tc.Assert(tree.Contains(80), "Make sure 80 is present.");
		tc.Assert(!tree.Contains(10), "Make sure 10 is not present.");
		tc.Assert(!tree.Contains(25), "Make sure 25 is not present.");
		tc.Assert(!tree.Contains(35), "Make sure 35 is not present.");
		tc.Assert(!tree.Contains(65), "Make sure 65 is not present.");
		tc.Assert(!tree.Contains(75), "Make sure 75 is not present.");
		tc.Assert(!tree.Contains(90), "Make sure 90 is not present.");
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


//##############################################################################
//###   Delete
//##############################################################################

/**************************************/
void TestPreOrder()
{
	TestCase tc("Test pre-order traversal.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(5);
		tree.Add(3);
		tree.Add(7);
		tree.Add(2);
		tree.Add(4);
		tree.Add(6);
		tree.Add(8);

		tc.AssertEquals(7, tree.Count(), "Make sure count is 7 after adding test nodes.");

		int expected[] = { 5, 3, 2, 4, 7, 6, 8 };
		vector<CounterClass> v;
		treeHelper.ToVectorPreOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 7, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}


/**************************************/
void TestPostOrder()
{
	TestCase tc("Test post-order traversal.");

	try
	{
		BinaryTree<CounterClass> tree;
		TreeHelper<CounterClass> treeHelper;
		tree.Add(5);
		tree.Add(3);
		tree.Add(7);
		tree.Add(2);
		tree.Add(4);
		tree.Add(6);
		tree.Add(8);

		tc.AssertEquals(7, tree.Count(), "Make sure count is 7 after adding test nodes.");

		int expected[] = { 2, 4, 3, 6, 8, 7, 5 };
		vector<CounterClass> v;
		treeHelper.ToVectorPostOrder(tree.GetRoot(), v);
		__ValidateVector(tc, expected, 7, v);
	}
	catch (exception &ex)
	{
		tc.LogException(ex);
	}

	tc.AssertEquals(0, CounterClass::InstanceCount, "Make sure destructor cleans up all nodes in the tree.");
}



//##############################################################################
//###   main
//##############################################################################

/**************************************/
void main()
{
	// Basic tests
	TestCreateEmptyTree();
	TestCallClearOnAnEmptyTree();
	TestToVectorPreOrderEmpty();

	// Add
	TestAddOneNode();
	TestAddOneDumpToVector();
	TestAddThreeItemsLeftHeavy();
	TestAddThreeItemsRightHeavy();
	TestAddThreeItemsBalanced();
	TestAddSevenItemsBalanced();
	TestAddDuplicateRoot();
	TestAddDuplicateDeep();

	// Delete nodes 
	TestDeleteFromEmptyTree();
	TestDeleteRootNode();
	TestDeleteLeftChildLeaf();
	TestDeleteRightChildLeaf();
	TestDeleteRootWithOneLeftChild();
	TestDeleteRootWithOneRightChild();
	TestDeleteRootWithLeftAndRightChild();
	TestDeleteMiddleWithRightRighttChild();
	TestDeleteMiddleWithRightLeftChild();

	// Search
	TestSearch();

	// Pre/post order
	TestPreOrder();
	TestPostOrder();

	TestCase::PrintSummary();
}


