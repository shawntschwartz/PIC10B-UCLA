//
// hmw_4_2.cpp
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

/** declare helper function for generate_substrings
* string s input string to generate substrings from
* return vector of strings with the generated substrings of input string s
*/
std::vector<std::string> _generate_substrings(std::string s)
{
	std::vector<std::string> substrings_results;

	// handle edge case of empty vector
	if (s.empty())
	{
		substrings_results.push_back("");
		return substrings_results;
	}

	for (int i = 0; i < s.length(); i++)
	{
		std::string substring = s.substr(0, i + 1);
		substrings_results.push_back(substring);
	}

	std::vector<std::string> get_substrings = _generate_substrings(s.substr(1));

	for (int i = 0; i < get_substrings.size(); i++)
	{
		substrings_results.push_back(get_substrings[i]);
	}

	return substrings_results;
}

/** generate substrings function implementing the _generate_substrings function for recursive call
* string s input string to generate substrings from
* return vector of strings with the generated substrings of input string s
*/
std::vector<std::string> generate_substrings(std::string s)
{
	return _generate_substrings(s);
}

/** print the vector of strings separated by quotation marks
* vector of strings in_vec input vector to print to the console
*/
void print_vec(const std::vector<std::string> in_vec)
{
	for (int i = 0; i < in_vec.size(); i++)
	{
		std::cout << "\"" << in_vec[i] << "\"" << std::endl;
	}
}

int main()
{
	char user_continue;
	do {
		std::vector<std::string> generated_substrings;
		std::string user_input;

		std::cout << "Enter a string: ";
		getline(std::cin, user_input);

		generated_substrings = generate_substrings(user_input);
		print_vec(generated_substrings);

		std::cout << "Continue (y/n) ";
		std::cin >> user_continue;
		std::cin.ignore();
		std::cout << std::endl;
	} while (user_continue == 'y' || user_continue == 'Y');

	return 0;
}