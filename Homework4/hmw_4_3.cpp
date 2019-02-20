//
// hmw_4_3.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <string>
#include <vector>

// generate all subsets of characters of the inputted string and display them (a subset per line)
// Note: a string can contain letters that are repeated, say s = "bob". The algo should treat all letters
// as individual 'place holders' without taking into account its content.
// Thus, the number of subsets of characters for a string containing n characters must be 2^n.

/** declare and implement a helper function for generate_subsets
* string s input string to generate subsets from
* return vector of strings to store generated subsets from string s
*/
std::vector<std::string> _generate_subsets(std::string s)
{
	// handle edge cases
	if (s.empty())
	{
		std::vector<std::string> subset_result;
		subset_result.push_back("");
		return subset_result;
	}

	else
	{
		std::vector<std::string> subset_result = _generate_subsets(s.substr(1));
		char* str_iter = new char[1]; // alloc mem for char ptr to walk along string
		str_iter[0] = s[0];
		int current_results_size = subset_result.size();
		for (int i = 0; i < current_results_size; ++i)
		{
			std::string subset_joined_together = (*str_iter + subset_result[i]); // join subsets together for each subset during the recursive call
			subset_result.push_back(subset_joined_together);
		}

		delete[] str_iter; // dealloc mem for char ptr

		return subset_result;
	}
}

/** generate_subsets function that utilizes the helper function _generate_subsets for recursive call
* string s input string to generate subsets from
* return vector of strings to store generated subsets from string s
*/
std::vector<std::string> generate_subsets(std::string s)
{
	return _generate_subsets(s);
}

/** print elements of the vector of generated subsets strings to gather each subset separated by quotation marks to the console
* const vector of strings in_vec to parse out and print subsets to console
*/
void print_vec(const std::vector<std::string> in_vec)
{
	for (int i = 0; i < in_vec.size(); i++)
	{
		std::cout << "\"" << in_vec[in_vec.size() - i - 1] << "\"" << std::endl;
	}
}

int main()
{
	char user_continue;

	do
	{
		std::string user_input;

		std::cout << "Enter a string: ";
		getline(std::cin, user_input);

		std::vector<std::string> subsets = generate_subsets(user_input);

		int subset_len = subsets.size();

		std::cout << subset_len << " subsets:" << std::endl;
		print_vec(subsets);

		std::cout << "Continue (y/n) ";
		std::cin >> user_continue;
		std::cin.ignore();
		std::cout << std::endl;
	} while (user_continue == 'y' || user_continue == 'Y');
	return 0;
}