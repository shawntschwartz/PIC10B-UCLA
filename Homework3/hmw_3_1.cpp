//
// hmw_3_1.cpp
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
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ios>

/**
* @param input_file name of input file from user to validate if file exists
* @return bool will return true if file exists
*/
bool validateInput(const std::string& input_file)
{
	std::ifstream fstream(input_file.c_str());
	return fstream.good();
}

/**
* @param input_file name of input file from user to validate if file exists
* @return long number of characters in the file
*/
long numberOfChars(const std::string& input_file)
{
	std::ifstream fstream(input_file);
	fstream.seekg(0, fstream.end);
	long char_count = fstream.tellg();
	fstream.close();

	return char_count;
}

/**
* @param input_file name of input file from user to validate if file exists
* @return long number of words in the file
*/
long numberOfWords(const std::string& input_file)
{
	std::ifstream fstream(input_file);
	std::stringstream ss;
	ss << fstream.rdbuf();

	std::string file_conts = ss.str();

	const char* buffer = file_conts.c_str();
	long buffer_len = strlen(buffer);
	fstream.close();

	long word_count = 0;

	for (int i = 0; i < buffer_len; i++)
	{
		if (buffer[i] == ' ' || buffer[i] == '\n')
		{
			word_count++;
		}
	}

	return word_count - 1;
}

/**
* @param input_file name of input file from user to validate if file exists
* @return long number of lines in the file
*/
long numberOfLines(const std::string& input_file)
{
	std::ifstream fstream(input_file);
	std::stringstream ss;
	ss << fstream.rdbuf();

	std::string file_conts = ss.str();

	const char* buffer = file_conts.c_str();
	long buffer_len = strlen(buffer);
	fstream.close();

	long line_count = 1;

	for (int i = 0; i < buffer_len; i++)
	{
		if (buffer[i] == '\n')
		{
			line_count++;
		}
	}

	return line_count;
}

int main()
{
	// Declare variables for main run
	bool input_is_valid = true;
	std::string input_file;

	// Declare variables to hold the returned number of characters, words, and lines in the inputted file from the user
	long numChars = 0;
	long numWords = 0;
	long numLines = 0;

	while (input_is_valid)
	{
		std::cout << "Enter a file name: ";
		getline(std::cin, input_file);

		input_is_valid = validateInput(input_file);

		if (input_is_valid)
		{
			numChars = numberOfChars(input_file);
			numWords = numberOfWords(input_file);
			numLines = numberOfLines(input_file);

			std::cout << "Number of characters" << std::setw(3) << " = " << numChars << std::endl;
			std::cout << "Number of words" << std::setw(8) << " = " << numWords << std::endl;
			std::cout << "Number of lines" << std::setw(8) << " = " << numLines << std::endl;

			std::cout << std::endl;
		}
		else
		{
			std::cout << "File " << input_file << " does not exist! Exit.\n" << std::endl;
			break;
		}
	}

	return 0;
}