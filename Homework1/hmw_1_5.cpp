//
// hmw_1_5.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>

// define type of int for pointer to int for function
typedef int(*intFunPointer)(int);

// declare function prototypes
int get_square(int);
void fill_with_values(int[], int, intFunPointer);
void print_array(int[], int);
bool user_continue(char);

int main()
{
	// declare int for user input
	int n = 0;
	// function pointer to get_square func
	intFunPointer funPtr = get_square; 

	// declare boolean var to continue accepting user input
	bool userInput = true;
	// init empty char for user input to continue accepting
	char cont;

	// do while userInput is true
	do
	{
		std::cout << "Enter the size of the array: ";
		std::cin >> n;

		// define pointer to int and dynamically allocate memory for arr of size input
		int* arr = new int[n];

		fill_with_values(arr, n, funPtr);

		print_array(arr, n);

		// deallocate dynamically allocated memory for pointer to arr
		arr = NULL;
		delete[] arr;

		// ask user if the would like to continue
		std::cout << "\nContinue (y/n)? ";
		std::cin >> cont;
		std::cout << std::endl;
		userInput = user_continue(cont);
	} while (userInput);

	return 0;
}

/**
	@param x: integer for multiplying by itself
	@return int: the square of the inputted number x*x
*/
int get_square(int x)
{
	return (x + 1)*(x + 1); //increment by 1 to compensate for indices of function pointer
}

/**
	@param a[]: input array to fill with values
	@param size: size of input array
	@param f: intFunPointer for getting the square of the indices of the array being filled
*/
void fill_with_values(int a[], int size, intFunPointer f)
{
	for (int i = 0; i <= size; i++)
	{
		a[i] = f(i);
	}
}

/**
	@param a[]: input array to print
	@param size: size of input array
*/
void print_array(int a[], int size)
{
	for (int i = 0; i < size; i++)
	{
		// print all elements of array to console except for last element with a comma separator
		if (i != size - 1)
		{
			std::cout << a[i] << ", ";
		}
		// if the last element of the array then print element to console without a comma separator
		else
		{
			std::cout << a[i] << std::endl;
		}
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