//
// hmw_1_4.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <string>
#include <cstring>

int main()
{
	// declare booleans 
	bool cont = true; // for checking if user wants to continue
	bool isBufferFull = false; // for checking if buffer is full (i.e. > 1000 chars)

	// init empty string to store input via std::cin to getline for buffer
	std::string input_for_buffer;
	char* lines[100]; // init pointer to char for 100 lines of input

	// declare vars to store current and total buffer sizes
	int current_line_size = 0;
	int updated_buffer_size = 0;

	// declare var to store the current line of input
	int current_line = 0;

	// while user continues to enter input and the buffer is not full
	while (cont && !isBufferFull)
	{
		// accept user input via std::cin
		std::cout << "Enter a line: ";
		getline(std::cin, input_for_buffer);

		// get the current line size and update the total buffer size
		current_line_size = (int)strlen(input_for_buffer.c_str());
		updated_buffer_size += current_line_size;

		// if the total buffer size is > 1000 break out of accepting user input to buffer
		if (updated_buffer_size > 1000)
		{
			isBufferFull = true;
			break;
		}

		// dynamically allocate memory for the current line of the line pointer to char of the input buffer length
		lines[current_line] = new char[input_for_buffer.length()];
		strcpy(lines[current_line], input_for_buffer.c_str()); // copy c style string from buffer input to pointer destination of lines[current_line]
		current_line++; // increment current_line by 1 for next line input

		// init empty char for user input to continue entering line
		char decision;
		std::cout << "\nContinue (y/n)? ";
		std::cin >> decision;
		std::cin.ignore();
		if (decision == 'y' || decision == 'Y')
		{
			cont = true;
		}
		else
		{
			cont = false;
		}
		std::cout << std::endl;
	}

	// check if buffer is full and if it is then print it to console
	if (isBufferFull)
	{
		std::cout << "\nBuffer is full! Stop.\n" << std::endl;
	}

	// print to console for reversed lines output
	std::cout << "Lines in reversed order: \n" << std::endl;

	// print the lines in reverse order by starting at the current_line in the list and going backwards to the first indice 
	for (int i = current_line - 1; i >= 0; i--)
	{
		std::cout << lines[i] << std::endl;
		// deallocate dynamically allocated memory for each line of the pointer to char lines
		lines[i] = NULL;
		delete[] lines[i];
	}

	return 0;
}