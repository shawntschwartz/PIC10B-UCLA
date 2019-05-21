//
// hmw_6_3.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <string>
#include <stack>

/*
* Return 1 if properly nested, otherwise return 0.
* @param S string to check if paren, brace, and bracket chars are properly nested
* @return int representing if string is properly nested.
*/
int is_nested(std::string S)
{
	std::stack<char> to_check;
	char traverse;

	// Assumptions
	char open_paren = '(';
	char open_brace = '{';
	char open_bracket = '[';
	char close_paren = ')';
	char close_brace = '}';
	char close_bracket = ']';

	for (int i = 0; i < S.length(); i++)
	{
		if (S[i] == open_paren || S[i] == open_brace || S[i] == open_bracket)
		{
			to_check.push(S[i]);
			continue;
		}

		// Return 0 if stack is empty implying that there are no opening chars
		if (to_check.empty())
		{
			return 0;
		}

		// Check closing chars
		if (S[i] == close_paren)
		{
			traverse = to_check.top();
			to_check.pop();

			if (traverse == open_brace || traverse == open_bracket)
			{
				return 0;
			}

			break;
		}
		else if (S[i] == close_brace)
		{
			traverse = to_check.top();
			to_check.pop();

			if (traverse == open_bracket || traverse == open_paren)
			{
				return 0;
			}

			break;
		}
		else if (S[i] == close_bracket)
		{
			traverse = to_check.top();
			to_check.pop();

			if (traverse == open_brace || traverse == open_paren)
			{
				return 0;
			}

			break;
		}
	}

	if (to_check.empty())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main()
{
	char cont;

	do
	{
		std::string input_str;
		std::cout << "Enter a string: ";
		getline(std::cin, input_str);
		int nestedVal = is_nested(input_str);

		if (nestedVal == 1)
		{
			std::cout << "String " << input_str << " is properly nested." << std::endl;
		} 
		else if (nestedVal == 0)
		{
			std::cout << "String " << input_str << " is NOT properly nested." << std::endl;
		}

		std::cout << "\nContinue y/n? ";
		std::cin >> cont;
		std::cin.ignore();
		std::cout << std::endl;

	} while (cont == 'y' || cont == 'Y');
	
	return 0;
}