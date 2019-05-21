//
// hmw_6_1.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <list>
#include <cassert>

// Class Prototype Definitions
class ListInt;
class Iterator;

class Node
{
public:
	/* 
	* Constructs a node with a given data value.
	* @param s the data to store in this node
	*/
	Node(int s);

	// Destructor
	~Node() {}

private:
	int data;
	Node* previous;
	Node* next;
	friend class ListInt;
	friend class Iterator;
};

class ListInt
{
public:
	/*
	* Constructs an empty list.
	*/
	ListInt();

	// Destructor
	// Deletes Nodes that are dynamically allocated
	~ListInt();

	/*
	* Appends an element to the list.
	* @param data the value to append
	*/
	void push_back(int data);

	/*
	* Inserts an element into the list.
	* @param iter the position before which to insert
	* @param s the value to append
	*/
	void insert(Iterator iter, int s);

	/*
	* Swaps the nodes to which the iterators it1 and it2 point to.
	* @param it1 first iterator to swap with the second.
	* @param it2 second iterator to swap with the first.
	*/
	void swap_nodes(Iterator it1, Iterator it2);
	void swap_nodes_node(Node* start, Node* min, Node* minPrev);

	/*
	* Sorts the elements of the ListInt using selection sort alogrithm
	*/
	void selection_sort();

	/*
	* Removes an element from the list.
	* @param iter the position to remove.
	* @return an iterator pointing to the element after the erased element
	*/
	Iterator erase(Iterator iter);

	/*
	* Gets the beginning position of the list.
	* @return an iterator pointing to the beginning of the list
	*/
	Iterator begin();

	/*
	* Gets the past-the-end position of the list.
	* @return an iterator pointing past the end of the list
	*/
	Iterator end();

	bool empty();

private:
	Node* first;
	Node* last;
	friend class Iterator;
};

class Iterator
{
public:
	/*
	* Constructs an iterator that does not point into any list.
	*/
	Iterator();

	// Copy constructor
	Iterator(const Iterator &pos);

	/*
	* Looks up the value at a position.
	* @return the value of the node to which the iterator points
	*/
	int get() const;

	/*
	* Advances the iterator to the next node.
	*/
	void next();

	/*
	* Moves the iterator to the previous node.
	*/
	void previous();

	/*
	* Compares two iterators.
	* @param b the iterator to compare with this iterator
	* @return true if this iterator and b are equal
	*/
	bool equals(Iterator b) const;

	// Overloaded Operators
	bool operator==(const Iterator &b) const;
	bool operator!=(const Iterator &b) const;
	Iterator operator++(int unused); // postfix
	Iterator& operator++(); // prefix
	Iterator operator--(int unused); // postfix
	Iterator& operator--(); // prefix
	int operator*() const;

private:
	Node* position;
	ListInt* container;
	friend class ListInt;
};

Node::Node(int s)
{
	data = s;
	previous = NULL;
	next = NULL;
}

ListInt::ListInt()
{
	first = NULL;
	last = NULL;
}

ListInt::~ListInt()
{
	if (!empty()) // if the list is nonempty
	{
		Node* node = this->first;

		while (node->next != NULL)
		{
			node = node->next; // jump to the next one
			delete node->previous; // deleting the memory for previous
		}

		if (node->next == NULL) // reaching the last node
		{
			delete node;
		}
	}
}

bool ListInt::empty()
{
	return (last = NULL);
}

void ListInt::push_back(int data)
{
	Node* new_node = new Node(data);
	if (last == NULL) // List is empty
	{
		first = new_node;
		last = new_node;
	}

	else
	{
		new_node->previous = last;
		last->next = new_node;
		last = new_node;
	}
}

void ListInt::insert(Iterator iter, int s)
{
	if (iter.position == NULL)
	{
		push_back(s);
		return;
	}

	Node* after = iter.position;
	Node* before = after->previous;
	Node* new_node = new Node(s);
	new_node->previous = before;
	new_node->next = after;
	after->previous = new_node;
	if (before == NULL) // Insert at beginning
	{
		first = new_node;
	}
	else
	{
		before->next = new_node;
	}
}

void ListInt::swap_nodes(Iterator it1, Iterator it2)
{
	// Edge Case: Do nothing if it1 and it2 are the same
	if (it1 == it2)
	{
		return;
	}

	Node* pos1 = it1.position;
	Node* pos2 = it2.position;
	Node* tmp_node = NULL;

	tmp_node = pos1;
	pos1 = pos2;
	pos2 = tmp_node;
}

void ListInt::selection_sort()
{
	Node* next = this->first;

	Iterator i = this->begin();
	Iterator j = this->begin()++;

	Iterator min = this->begin();

	for (i; i != this->end(); i++)
	{
		for (j; j != this->end(); j++)
		{
			if (*j < *min)
			{
				min = j;
			}
		}

		if (*min != next->data)
		{
			swap_nodes(i, j);
			first->data = *i;
		}	
	}
}

Iterator ListInt::erase(Iterator iter)
{
	assert(iter.position != NULL);
	Node* remove = iter.position;
	Node* before = remove->previous;
	Node* after = remove->next;
	if (remove == first)
	{
		first = after;
	}
	else
	{
		before->next = after;
		if (remove == last)
		{
			last = before;
		}
		else
		{
			after->previous = before;
		}
	}
	delete remove;
	Iterator r;
	r.position = after;
	r.container = this;
	return r;
}

Iterator ListInt::begin()
{
	Iterator iter;
	iter.position = first;
	iter.container = this;
	return iter;
}

Iterator ListInt::end()
{
	Iterator iter;
	iter.position = NULL;
	iter.container = this;
	return iter;
}

Iterator::Iterator()
{
	position = NULL;
	container = NULL;
}

Iterator::Iterator(const Iterator &pos)
{
	(*this) = pos;
}

int Iterator::get() const
{
	assert(position != NULL);
	return position->data;
}

void Iterator::next()
{
	assert(position != NULL);
	position = position->next;
}

void Iterator::previous()
{
	assert(position != container->first);
	if (position == NULL)
	{
		position = container->last;
	}
	else
	{
		position = position->previous;
	}
}

bool Iterator::equals(Iterator b) const
{
	return position == b.position;
}

bool Iterator::operator==(const Iterator &b) const
{
	return position == b.position;
}

bool Iterator::operator!=(const Iterator &b) const
{
	return position != b.position;
}

Iterator& Iterator::operator++() // prefix
{
	assert(position != NULL);
	position = position->next;
	return *this;
}

Iterator Iterator::operator++(int unused) // postfix
{
	assert(position != NULL);

	Iterator clone(*this);

	position = position->next;

	return clone;
}

Iterator& Iterator::operator--() // prefix
{
	assert(position != container->first);
	if (position == NULL)
	{
		position = container->last;
	}
	else
	{
		position = position->previous;
	}
	return *this;
}

Iterator Iterator::operator--(int unused)
{
	assert(position != container->first);

	Iterator clone(*this);

	if (position == NULL)
	{
		position = container->last;
	}
	else
	{
		position = position->previous;
	}
	return clone;
}

int Iterator::operator*() const
{
	assert(position != NULL);
	return position->data;
}

/*
* Reads in numbers from text file into a list.
* @param in ifstream reference from which numbers are coming from
* @param num_list reference of list of numbers 
*/
void readIn(std::ifstream &in, ListInt &num_list)
{
	std::string line;

	while (getline(in, line))
	{
		int num;

		std::stringstream ss(line);

		ss >> num;

		num_list.push_back(num);
	}
}

/*
* Iterates and prints through list.
* @param num_list list to print.
*/
void printList(ListInt & num_list)
{
	int counter = 0;
	for (auto x : num_list)
	{
		if (counter != 0)
		{
			std::cout << "->";
		}
		counter++;
		std::cout << x;
	}
	std::cout << std::endl;
}

int main()
{

	// Read in Data from Text File
	std::string input_file = "data1.txt";
	std::ifstream fstream(input_file.c_str());
	ListInt number_list;
	readIn(fstream, number_list);
	fstream.close();

	// Console Outputs
	std::cout << "Iterating through the list in " << input_file << ":" << std::endl;
	std::cout << std::endl;
	printList(number_list);
	std::cout << std::endl;
	std::cout << "Sorted List:" << std::endl;
	std::cout << std::endl;
	number_list.selection_sort();
	printList(number_list);
	
	std::cout << std::endl;

	return 0;
}