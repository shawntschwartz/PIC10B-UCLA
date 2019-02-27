//
// hmw_1_3.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <string>

// Declare function prototypes
void reverse(double*, int);
bool user_continue(char);

int main()
{
	// declare boolean var and set to true for checking if user wants to continue entering lists of numbers
	bool userInput = true;

	// do while userInput is true
	do
	{
		// init empty string for user input and store user input to string
		std::string s;
		std::cout << "Enter a list of numbers: ";
		getline(std::cin, s);

		// retrieve size of inputted string elements for new array by 1+separations by spaces to capture last number in list
		int a_size = (int)std::count(s.begin(), s.end(), ' ') + 1;

		// dynamically allocate memory for new array of size a_size
		double* arr = new double[a_size];

		// unsigned int for pointer to object of size_t to start of characters in string index to convert strings to double
		std::size_t offset = 0;
		for (int i = 0; i < a_size; i++)
		{
			// convert strings to doubles and store each converted double to the dynamically allocated array arr
			arr[i] = std::stod(&s[i], &offset);
			s = s.substr(offset);
		}

		// output reversed list to console
		std::cout << "Reversed list: ";
		reverse(arr, a_size); // perform reverse function on the pointer to array arr of size a_size
		for (int i = 0; i < a_size; i++)
		{
			// print all but the last element of the arr with a comma separator 
			if (i != a_size - 1)
			{
				std::cout << arr[i] << ", ";
			}
			// print the last element of the array without a comma separator to console 
			else 
			{
				std::cout << arr[i] << std::endl;
			}
		}

		// deallocate dynamically allocated memory for pointe to arr
		arr = NULL;
		delete[] arr;

		// init empty char to store user input for (y)es continue inputting lists of numbers
		char cont;
		std::cout << "\nContinue (y/n)? ";
		std::cin >> cont;
		std::cin.ignore();
		userInput = user_continue(cont);
	} while (userInput);

	return 0;
}

/**
	@param a: pointer to array
	@param a_size: size of input arr
*/
void reverse(double* a, int a_size)
{
	double* a_start = a; // points to the first element of the input pointer array
	double* a_end = a + (a_size - 1); // points to the last element of the input pointer array
	double temp_rev_storage = 0; // declare temporary storage for dereferenced start and end pointers for reversal of arr elements 

	// reverse the elements until the starting pointer is larger than the ending pointer (i.e., overlapping each other)
	while (a_start < a_end)
	{
		temp_rev_storage = *a_start; // first store dereferenced value of a_start pointer to temporary storage
		*a_start = *a_end; // then set dereferenced starting value to that of the end point
		*a_end = temp_rev_storage; // finally set dereferenced end value to the dereferenced starting value from step 1

		a_start++; // move starting pointer forward (increment)
		a_end--; // move ending pointer backwards (decrement)
	}
}

/**
	@param decision: user char input to compare for continuing to run program
	@return bool: based on user input of (y)es or other
*/
bool user_continue(char decision)
{
	if (decision == 'y' || decision == 'Y')
	{
		return true;
	}
	else
	{
		return false;
	}
}