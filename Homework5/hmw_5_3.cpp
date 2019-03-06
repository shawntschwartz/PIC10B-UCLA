//
// hmw_5_3.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>

/* Tasks
* Implement a function: bool binary_search(vector<int> & v, int value, int & m),
* that uses binary search to find out whether there is an integer value in the vector v of integers.
* If vector<int> & v is not sorted, then the function must return false and set m = -1.
* If v is sorted and a match is found, the function must return true, otherwise false.
* In the above function m is a reference parameter, which must be set to the location of the match if the search was successful.
* if value were not found, set m to the index of the next larger value instead, or to v.size() if value is larger than all the elements of the vector.
*
* Write a program that reads the list of integers from a file data3.txt and displays them on the screen.
* Then the program must sort the numbers using sort function from the C++ library and then display the sorted vector.
*
* Finally, implement a loop in which the user is asked to enter a value, which is then searched in the sorted array using
* the above binary_search function.
* If value is found display "Found. m=" followed by the value of m.
* Otherwise, display "Not found. m=" followed by the value of m.
*/

/**
* Use binary search to find out whether there is an integer value in the vector v of ints
* @param v input vector of ints to search
* @param value integer value to search for within the vector
* @param m integer location of the match
* @return bool true if match is found
*/
bool binary_search(std::vector<int> &v, int value, int &m)
{
	// cover edge cases
	// check if vector is sorted
	// if vector not sorted, return false
	if (std::is_sorted(v.begin(), v.end()) == false)
	{
		m = -1;
		return false;
	}

	int min = 0;
	int max = v.size() - 1;

	int guess = (min + max) / 2; // the position of the middle of the vector

	if (v[guess] == value)
	{
		m = guess;
		return true;
	}

	while (min <= max)
	{
		guess = (min + max) / 2; // the position of the middle of the vector

		if (v[guess] < value)
		{
			min = guess + 1;
		}
		else if (v[guess] > value)
		{
			max = guess - 1;
		}
		else
		{
			m = guess;
			return true;
		}
	}

	m = -1;
	return false;
}

/**
* Reads in ints from external text file and stores in a vector.
* @param in ifstream reference for reading in the text file
* @return vector<int> all integers from the external text file
*/
std::vector<int> getIntsFromFile(std::ifstream &in)
{
	int file_contents;
	std::vector<int> all_lines;

	while (in >> file_contents)
	{
		all_lines.push_back(file_contents);
	}

	return all_lines;
}

/**
* Prints a vector to the console.
* @param in_vec input vector to print
*/
void print(std::vector<int> in_vec)
{
	for (int i = 0; i < in_vec.size(); i++)
	{
		std::cout << in_vec[i] << " ";
	}
}

int main()
{
	// Read in the file to store in the vector
	std::string filename = "data3.txt";
	std::ifstream fstream(filename.c_str());
	std::vector<int> read_vec = getIntsFromFile(fstream);
	fstream.close();

	// Print before sorted vector of ints
	std::cout << "Before sorting:" << std::endl;
	print(read_vec);

	// Print after sorted vector of its
	std::cout << "\nAfter sorting:" << std::endl;
	std::sort(read_vec.begin(), read_vec.end());
	print(read_vec);

	std::cout << std::endl;
	std::cout << std::endl;

	char user_continue;
	do
	{
		int val_to_search;
		int m_loc;
		bool is_search_found = false;

		std::cout << "\nEnter a value: ";
		std::cin >> val_to_search;

		is_search_found = binary_search(read_vec, val_to_search, m_loc);
		if (is_search_found)
		{
			std::cout << "Found. m=" << m_loc << std::endl;
		}
		else
		{
			std::cout << "Not found. m=" << m_loc << std::endl;
		}

		std::cout << "\nContinue (y/n)? ";
		std::cin >> user_continue;
	} while (user_continue == 'y' || user_continue == 'Y');

	std::cout << std::endl;

	return 0;
}