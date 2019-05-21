//
// hmw_6_4.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <vector> 
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>
#include <map>
#include <set>
#include <list>

// Binary Search Tree

using namespace std;

class TreeNode
{
public:
	void insert_node(TreeNode* new_node);
	vector<int> print_nodes() const;
	vector<int> print_nodes_pre() const;
	vector<int> print_nodes_post() const;
	bool find(string value) const;
private:
	string data;
	TreeNode* left;
	TreeNode* right;
	friend class BinarySearchTree;
};

class Action
{
public:
	virtual void act(string str);
	TreeNode* root = NULL;
};

void Action::act(string str)
{
	int len = str.length();
	cout << len;
}

class PrintAction : public Action
{
public:
	vector<int> print();
	vector<int> print_pre();
	vector<int> print_post();
};

vector<int> PrintAction::print()
{
	vector<int> len;
	if (root != NULL)
		root->print_nodes();
		return len;
}

vector<int> PrintAction::print_pre()
{
	vector<int> len;
	if (root != NULL)
		root->print_nodes_pre();
	return len;
}

vector<int> PrintAction::print_post()
{
	vector<int> len;
	if (root != NULL)
		root->print_nodes_post();
	return len;
}

class LengthAction : public Action
{
public:
	int get_length(Action& a) const;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	void insert(string data);
	void erase(string data);
	void inorder(Action &a);
	void preorder(Action &a);
	void postorder(Action &a);
	int count(string data) const;
	vector<int> print();
private:
	TreeNode* root;
};

BinarySearchTree::BinarySearchTree()
{
	root = NULL;
}

void BinarySearchTree::inorder(Action &a)
{
	vector<int> len;
	if (root != NULL)
		len = root->print_nodes();
}

void BinarySearchTree::preorder(Action &a)
{
	vector<int> len;
	if (root != NULL)
		len = root->print_nodes_pre();
}

void BinarySearchTree::postorder(Action &a)
{
	vector<int> len;
	if (root != NULL)
		len = root->print_nodes_post();
}

void BinarySearchTree::insert(string data)
{
	TreeNode* new_node = new TreeNode;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	if (root == NULL) root = new_node;
	else root->insert_node(new_node);
}

void TreeNode::insert_node(TreeNode* new_node)
{

	if (new_node->data < data)
	{
		if (left == NULL) left = new_node;
		else left->insert_node(new_node);
	}
	else if (data < new_node->data)
	{
		if (right == NULL) right = new_node;
		else right->insert_node(new_node);
	}
}

int BinarySearchTree::count(string data) const
{
	if (root == NULL) return 0;
	else if (root->find(data)) return 1;
	else return 0;
}

void BinarySearchTree::erase(string data)
{
	// Find node to be removed and its parent
	TreeNode* to_be_removed = root;
	TreeNode* parent = NULL;
	bool found = false;
	while (!found && to_be_removed != NULL)
	{
		if (to_be_removed->data < data)
		{
			parent
				= to_be_removed;
			to_be_removed = to_be_removed->right;
		}
		else if (data < to_be_removed->data)
		{
			parent = to_be_removed;
			to_be_removed = to_be_removed->left;
		}
		else found = true;
	}

	if (!found) return;

	// to_be_removed contains data (and hence is not NULL)

	// If one of the children is empty, use the other

	if (to_be_removed->left == NULL || to_be_removed->right == NULL)
	{
		TreeNode* new_child;

		if (to_be_removed->left == NULL)
			new_child = to_be_removed->right;
		else
			new_child = to_be_removed->left;

		if (parent == NULL) // Found in root
		{
			delete to_be_removed;
			root = new_child;
		}
		else if (parent->left == to_be_removed)
		{
			delete to_be_removed;
			parent->left = new_child;
		}
		else
		{
			delete to_be_removed;
			parent->right = new_child;
		}
		return;
	}

	// Neither subtree is empty

	// Find smallest element of the right subtree

	TreeNode* smallest_parent = to_be_removed;
	TreeNode* smallest = to_be_removed->right;
	while (smallest->left != NULL)
	{
		smallest_parent = smallest;
		smallest = smallest->left;
	}

	// smallest contains smallest child in right subtree

	// Move contents, unlink child
	to_be_removed->data = smallest->data;
	if (smallest_parent == to_be_removed)
	{
		smallest_parent->right = smallest->right;
		delete smallest;
	}
	else
	{
		smallest_parent->left = smallest->right;
		delete smallest;
	}
}

bool TreeNode::find(string value) const
{
	if (value < data)
	{
		if (left == NULL) return false;
		else return left->find(value);
	}
	else if (data < value)
	{
		if (right == NULL) return false;
		else return right->find(value);
	}
	else { return true; }
}

vector<int> TreeNode::print_nodes() const
{
	if (left != NULL)
		left->print_nodes();
	cout << data << "\n";
	vector<int> len;
	len.push_back(data.length());
	if (right != NULL)
		right->print_nodes();
	
	return len;
}

vector<int> TreeNode::print_nodes_pre() const
{
	cout << data << "\n";
	vector<int> len;
	len.push_back(data.length());
	if (left != NULL)
		left->print_nodes_pre();
	if (right != NULL)
		right->print_nodes_pre();

	return len;
}

vector<int> TreeNode::print_nodes_post() const
{
	if (left != NULL)
		left->print_nodes_post();
	if (right != NULL)
		right->print_nodes_post();
	cout << data << "\n";
	vector<int> len;
	len.push_back(data.length());

	return len;
}

/*
* Reads in numbers from text file into a list.
* @param in ifstream reference from which numbers are coming from
* @param word_list reference of list of numbers
*/
void readIn(std::ifstream &in, BinarySearchTree &names_tree)
{
	std::string line;

	while (getline(in, line))
	{
		std::string cur_word;

		std::stringstream ss(line);

		ss >> cur_word;

		names_tree.insert(cur_word);
	}
}

int main()
{
	// Read In File Contents
	std::string input_file = "data4.txt";
	std::ifstream fstream(input_file.c_str());
	BinarySearchTree names_tree;
	readIn(fstream, names_tree);
	fstream.close();
	vector<int> lens;
	PrintAction pa;

	// Storage Variables
	std::cout << "The sum of all lengths of the strings stored in a tree: " << std::endl;

	cout << "\nPrinting the elements of the tree inorder:" << endl;
	names_tree.inorder(pa);

	cout << "\nPrinting the elements of the tree preorder:" << endl;
	names_tree.preorder(pa);

	cout << "\nPrinting the elements of the tree postorder:" << endl;
	names_tree.postorder(pa);

	cout << endl;
	
	return 0;
}