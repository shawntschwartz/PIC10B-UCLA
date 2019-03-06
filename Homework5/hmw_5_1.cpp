//
// hmw_5_1.cpp
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

/* Tasks
* Modify the selection sort alogrithm to sort a vector of integers in descending order.
* Write a program that reads in a list of integers from a file data1.txt into a vector
* and then uses the above algorithm to sort it. Then display the sorted vector.
*/

/**
* Swaps two ints.
* @param x the first integer to swap
* @param y the second integer to swap
*/
void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

/**
* Gets the position of the largest element in a vector range.
* @param a the vector
* @param from the beginning of the range
* @param to the end of the range
* @return int the position of the largest element in the range a[from] ... a[to]
*/
int max_position(std::vector<int> &a, int from, int to)
{
	int max_pos = from;
	int i;

	for (i = from + 1; i <= to; i++)
	{
		if (a[i] > a[max_pos])
		{
			max_pos = i;
		}
	}

	return max_pos;
}

/**
* Sorts a vector using the selection sort alogrithm in descending order.
* @param a the vector to sort
*/
void selection_sort(std::vector<int> &a)
{
	int next; // next position to be set to the min

	for (next = 0; next < a.size() - 1; next++)
	{
		// Find position of min
		int max_pos = max_position(a, next, a.size() - 1);
		if (max_pos != next)
		{
			swap(a[max_pos], a[next]);
		}
	}
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

/**
* Reads in ints from external text file and stores in a vector.
* @param in ifstream reference for reading in the text file
* @return vector<int> all integers from the external text file
*/
std::vector<int> getFileContents(std::ifstream &in)
{
	int file_contents;
	std::vector<int> all_lines;

	while (in >> file_contents)
	{
		all_lines.push_back(file_contents);
	}

	return all_lines;
}

int main()
{
	// Read in the file to store in the vector
	std::string filename = "data1.txt";
	std::ifstream fstream(filename.c_str());
	std::vector<int> read_vec = getFileContents(fstream);
	fstream.close();

	// Print before and after sorted vector
	std::cout << "Before sorting:" << std::endl;
	print(read_vec);
	std::cout << "\nAfter sorting:" << std::endl;
	selection_sort(read_vec);
	print(read_vec);

	std::cout << std::endl;

	return 0;
}