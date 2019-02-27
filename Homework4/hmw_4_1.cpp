//
// hmw_4_1.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <string>

/** implement helper function for index_of function
* string s input full string to search
* string t input substring to search string s for
* int str_index current index searching along the string for recursive call
* return int index of the substring t starting location within full string s
*/
int _index_of(std::string s, std::string t, int str_index)
{
	// handle edge cases --> to stop recursion if the index is out of the string's bounds
	if (s.size() < (t.size() + str_index))
	{
		return -1;
	}

	// obtain substring of user search to check against whole string input
	std::string search_sub = s.substr(str_index, t.size());

	// check if the searched substring at the current search position is equivalent to the full string
	if (search_sub.compare(t) == 0)
	{
		return str_index;
	}

	return _index_of(s, t, str_index + 1);
}

/** main recursive function impelmenting the helper function _index_of
* string s input full string to search
* string t input substring to search string s for
* return int index of the substring t starting location within full string s
*/
int index_of(std::string s, std::string t)
{
	return _index_of(s, t, 0);
}

/** validate input of substring to search for
* string s input full string being searched
* string t input substring to search string s for
* return true if substring t is not contained within the full string s
*/
bool validate_input(std::string s, std::string t)
{
	if (index_of(s, t) == -1)
	{
		std::cout << "Not found!" << std::endl;
		return false;
	}

	return true;
}

int main()
{
	char user_continue;

	do
	{
		std::string user_in;
		std::string user_search;

		std::cout << "Enter a string: ";
		getline(std::cin, user_in);
		std::cout << "Enter a string to search for: ";
		getline(std::cin, user_search);

		bool is_substr_valid = validate_input(user_in, user_search);

		if (is_substr_valid)
		{
			int starting_index = index_of(user_in, user_search);
			std::cout << "The position = " << starting_index << std::endl;
		}

		std::cout << "Continue (y/n) ";
		std::cin >> user_continue;
		std::cout << std::endl;
		std::cin.ignore();
	} while (user_continue == 'y' || user_continue == 'Y');


	return 0;
}