//
// hmw_1_2.cpp
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
double* maximum(double*, int);
bool user_continue(char);

int main()
{
	// declare boolean var for continuing to run program until user enters (n)o
	bool userInput = true;

	// do while userInput is true
	do
	{
		// init empty string for storing user inputted list of numbers
		std::string s;
		std::cout << "Enter a list of numbers: ";
		getline(std::cin, s);

		// retrieve size of inputted string array through 1+separations by spaces for last number with no space after it
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

		// declare pointer to double of the max value of the inputted pointer to array 
		double* maxptr = maximum(arr, a_size);
		int idx_maxval = 0; // declare int var to eventually store the index of the maximum val in arr

		// output the value of the max element to the console
		std::cout << "maximal element: " << *maxptr << std::endl;

		// retrieve the index of the maxval by checking arr against the pointer to the maxval (maxptr)
		for (int i = 0; i < a_size; i++)
		{
			if (arr[i] == *maxptr) {
				idx_maxval = i;
				break; // break out of conditional if the maxval index is found and stored
			}
		}

		// deallocate memory for the pointer to the maximum value
		maxptr = NULL;
		delete maxptr;

		// output the index of the max element to the console
		std::cout << "index of the maximal element: " << idx_maxval << std::endl;

		// check if the user wants to do another list of numbers
		char cont; // init empty char to store user input of (y/n)

		std::cout << "\nContinue (y/n)? ";
		std::cin >> cont;
		std::cin.ignore();
		std::cout << std::endl;
		userInput = user_continue(cont);

		// deallocate memory for the pointer to the array of converted string-to-doubles 
		arr = NULL;
		delete[] arr;

	} while (userInput);

	return 0;
}

/**
	@param a: pointer to array
	@param a_size: size of array
	@return double*: pointer to maximum value of inputted pointer to array
*/
double* maximum(double* a, int a_size)
{
	double* maxval = a;
	for (int i = 0; i < a_size; i++)
	{
		if (a[i] > *maxval) 
		{
			maxval = &a[i];
		}
	}
	return maxval;
	maxval = NULL;
	delete maxval;
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