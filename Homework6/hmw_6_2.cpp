//
// hmw_6_2.cpp
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
class sList;
class Iterator;

class Node
{
public:
	/*
	* Constructs a node with a given data value.
	* @param s the data to store in this node
	*/
	Node(std::string s);

	// Destructor
	~Node() {}

private:
	std::string data;
	Node* next;
	friend class sList;
	friend class Iterator;
};

class sList
{
public:
	/*
	* Constructs an empty list.
	*/
	sList();

	// Destructor
	// Deletes Nodes that are dynamically allocated
	~sList();

	/*
	* Appends an element to the list.
	* @param data the value to append
	*/
	void push_back(std::string data);

	/*
	* Inserts an element into the list.
	* @param iter the position before which to insert
	* @param s the value to append
	*/
	void insert(Iterator iter, std::string s);

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

	Iterator();
	Iterator(const Iterator &pos);
	std::string get() const;
	void next();
	bool equals(Iterator b) const;


	// Overloaded Operators
	bool operator==(const Iterator &b) const;
	bool operator!=(const Iterator &b) const;
	Iterator operator++(int unused); // postfix
	Iterator& operator++(); // prefix
	std::string operator*() const;

private:
	Node* position;
	Node* previous;
	sList* container;
	friend class sList;
};

Node::Node(std::string s)
{
	data = s;
	next = NULL;
}

sList::sList()
{
	first = NULL;
	last = NULL;
}

sList::~sList()
{
	if (!empty()) // if the list is nonempty
	{
		Node* node = this->first;

		while (node->next != NULL)
		{
			node = node->next; // jump to the next one
		}

		if (node->next == NULL) // reaching the last node
		{
			delete node;
		}
	}
}

bool sList::empty()
{
	return (last = NULL);
}

void sList::push_back(std::string data)
{
	Node* new_node = new Node(data);
	if (last == NULL) // List is empty
	{
		first = new_node;
		last = new_node;
	}

	else
	{
		last->next = new_node;
		last = new_node;
	}
}

void sList::insert(Iterator iter, std::string s)
{
	if (iter.position == NULL)
	{
		push_back(s);
		return;
	}

	Node* after = iter.position;
	Node* new_node = new Node(s);
	new_node->next = after;
}

Iterator sList::erase(Iterator iter)
{
	assert(iter.position != NULL);

	Node* remove = iter.position;
	Node* remove_prev = iter.previous;

	// Case for First Element
	if (remove == first)
	{
		first = remove->next;

		if (first == NULL)
		{
			last = NULL;
		}
	}

	// Case for Last Element
	else if (remove == last)
	{
		last = remove_prev;

		if (remove_prev != NULL)
		{
			remove_prev->next = NULL;
		}
		
	}

	// Case for All Other Elements in Between
	else
	{
		remove_prev->next = remove->next;
	}


	Iterator r;
	r.previous = remove_prev;
	r.position = remove->next;
	r.container = this;

	delete remove;

	return r;
}

Iterator sList::begin()
{
	Iterator iter;
	iter.position = first;
	iter.previous = NULL;
	iter.container = this;
	return iter;
}

Iterator sList::end()
{
	Iterator iter;
	iter.position = NULL;
	iter.previous = last;
	iter.container = this;
	return iter;
}

Iterator::Iterator()
{
	previous = NULL;
	position = NULL;
	container = NULL;
}

Iterator::Iterator(const Iterator & pos)
{
	(*this) = pos;
}

std::string Iterator::get() const
{
	assert(position != NULL);
	return position->data;
}

void Iterator::next()
{
	assert(position != NULL);
	previous = position;
	position = position->next;
}

bool Iterator::equals(Iterator b) const
{
	return ( (container==b.container) && (position == b.position) 
		     && (previous == b.previous));
}

bool Iterator::operator==(const Iterator &b) const
{
	return (equals(b));
}

bool Iterator::operator!=(const Iterator &b) const
{
	return (!equals(b));
}

Iterator& Iterator::operator++() // prefix
{
	assert(position != NULL);
	previous = position;
	position = position->next;
	return *this;
}

Iterator Iterator::operator++(int unused) // postfix
{
	assert(position != NULL);

	Iterator clone(*this);

	previous = position;
	position = position->next;

	return clone;
}

std::string Iterator::operator*() const
{
	assert(position != NULL);
	return position->data;
}

/*
* Reads in numbers from text file into a list.
* @param in ifstream reference from which numbers are coming from
* @param word_list reference of list of numbers
*/
void readIn(std::ifstream &in, sList &word_list)
{
	std::string line;

	while (getline(in, line))
	{
		std::string cur_word;

		std::stringstream ss(line);

		ss >> cur_word;

		word_list.push_back(cur_word);
	}
}

/*
* Iterates and prints through list.
* @param word_list list to print.
*/
void printList(sList &word_list)
{

	int counter = 0;
	for (auto x: word_list )
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

/*
* Removes inputted string word from a singly linked list of words.
* @param word input word to remove
* @param word_list singly linked list of words to remove input word from
* @return bool if word was present in list or not
*/
bool removeWordFromList(const std::string word, sList &word_list)
{
	Iterator beginning = word_list.begin();
	Iterator ending = word_list.end();
	Iterator position = beginning;

	bool wordFound = false;

	for (position; position != ending; position++)
	{
		if (*position == word)
		{
			wordFound = true;
			word_list.erase(position);
			break;
		}
	}

	if (!wordFound)
	{
		std::cout << "\nThere is no such element in the list." << std::endl;
	}

	return wordFound;
}

int main()
{
	char cont;

	// Read in Data from Text File
	std::string input_file = "data2.txt";
	std::ifstream fstream(input_file.c_str());
	sList word_list;
	readIn(fstream, word_list);
	fstream.close();

	std::string wordToRemove;

	// Console Outputs
	std::cout << "Iterating through the list in " << input_file << ":" << std::endl;
	std::cout << std::endl;
	printList(word_list);
	std::cout << std::endl;
	std::cout << "Testing Removal." << std::endl;

	do
	{
		bool wordPresent = false;

		std::cout << "\nEnter the element to remove: ";
		getline(std::cin, wordToRemove);

		wordPresent = removeWordFromList(wordToRemove, word_list);

		if (wordPresent)
		{
			std::cout << "\nUpdated list: ";
			printList(word_list);
		}

		std::cout << "\nContinue (y/n)? ";
		std::cin >> cont;
		std::cin.ignore();

	} while (cont == 'y' || cont == 'Y');
	
	return 0;
}