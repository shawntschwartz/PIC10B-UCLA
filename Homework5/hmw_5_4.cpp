//
// hmw_5_4.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>

/*Tasks
* Implement a function vector<size_t> remove_duplicates(vector<int> &v),
* that removes the duplicates from vector<int> &v and returns the vector<size_t> containing the number of times
* each distinct value appeared in the original v.
* The algorithm should have complexity O(n*log(n)).
* Hint: Sort v using built-in sort function.
* Note: The elements in v may have a different order after removal of duplicates.
*
* Write a program that reads the list of integers from the file data4.txt into a vector.
* Display the numbers on the screen. Then call the function remove_duplicates and display the content of the modified
* vector indicating how many times each number appeared in the original vector.
* The order of the displayed numbers does not matter.
*/

/**
* Use binary search to find position of first occurance of given value in vector v
* @param v input vector of ints to search
* @param value integer value to search for within the vector
* @return int position of occurance
*/
int binary_search_first(std::vector<int> &v, int value)
{
	int min = 0;
	int max = v.size() - 1;
	int guess = (min + max) / 2; // mid

	int m = -1;

	while (min <= max)
	{
		guess = (min + max) / 2; // mid

		if (v[guess] == value)
		{
			m = guess;

			// search points towards the left
			max = guess - 1;
		}

		else if (v[guess] > value)
		{
			max = guess - 1;
		}
		else
		{
			min = guess + 1;
		}
	}

	return m;
}

/**
* Use binary search to find position of last occurance of given value in vector v
* @param v input vector of ints to search
* @param value integer value to search for within the vector
* @return int position of occurance
*/
int binary_search_last(std::vector<int> &v, int value)
{
	int min = 0;
	int max = v.size() - 1;
	int guess = (min + max) / 2; // mid

	int m = -1;

	while (min <= max)
	{
		guess = (min + max) / 2; // mid

		if (v[guess] == value)
		{
			m = guess;

			// search points towards the right
			min = guess + 1;
		}

		else if (v[guess] > value)
		{
			max = guess - 1;
		}
		else
		{
			min = guess + 1;
		}
	}

	return m;
}

/**
* Removes the duplicates from vector<int> &v
* @param v vector of ints to remove duplicates from
* @return vector<size_t> containing the number of times each distinct value appeared in the original v.
*/
std::vector<size_t> remove_duplicates(std::vector<int> &v)
{
	std::vector<size_t> num_duplicate_vals;

	std::vector<size_t> lower_occurances;
	std::vector<size_t> upper_occurances;

	// if vector is not sorted, sort it
	if (std::is_sorted(v.begin(), v.end()) == false)
	{
		std::sort(v.begin(), v.end());
	}

	int lower_bound;
	int upper_bound;

	// check if vector is not empty
	if (!v.empty())
	{
		lower_bound = v.front();
		upper_bound = v.back();
	}
	else
	{
		lower_bound = -1;
		upper_bound = -1;
	}

	// Get first and last occurances of each number in the sorted vector
	for (int i = lower_bound; i <= upper_bound; i++)
	{
		lower_occurances.push_back(binary_search_first(v, i));
		upper_occurances.push_back(binary_search_last(v, i));
	}

	// Calculate the differences between last and first occurance indices to determine quantity of that value
	for (int i = 0; i < lower_occurances.size(); i++)
	{
		size_t cur_num_elems = (upper_occurances[i] - lower_occurances[i] + 1);
		num_duplicate_vals.push_back(cur_num_elems);
	}

	// Remove the duplicates
	std::vector<int> v_tmp;
	for (int i = 0; i < v.size() - 1; i++)
	{
		if (v[i] != v[i + 1])
		{
			v_tmp.push_back(v[i]);
		}
	}

	// Store the last element
	v_tmp.push_back(v[v.size() - 1]);

	// Send v_tmp back to v for passed reference of the vector back into main
	v = v_tmp;

	return num_duplicate_vals;
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

/**
* Prints a vector to the console.
* @param in_vec input vector to print
*/
void printVec(std::vector<int> in_vec)
{
	for (int i = 0; i < in_vec.size(); i++)
	{
		std::cout << in_vec[i] << " ";
	}
}

/**
* Prints duplicate values from size_t vec containing the number of times each distinct value appeared in the original v.
* @param v vector of ints to that duplicates were removed from
* @param duplicates vector of duplicate value occurances per distinct value
*/
void printDuplicates(std::vector<int> &v, std::vector<size_t> duplicates)
{
	for (int i = 0; i < duplicates.size(); i++)
	{
		std::cout << v[i] << " (" << duplicates[i] << " times)" << std::endl;
	}
}

int main()
{
	// Get the ints from the file
	std::string filename = "data4.txt";
	std::ifstream fstream(filename.c_str());
	std::vector<int> read_vec = getFileContents(fstream);
	fstream.close();

	std::cout << "Array:";
	printVec(read_vec);
	std::cout << std::endl;
	std::vector<size_t> duplicates_vec = remove_duplicates(read_vec);
	printDuplicates(read_vec, duplicates_vec);

	return 0;
}