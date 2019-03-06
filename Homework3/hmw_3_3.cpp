//
// hmw_3_3.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <ios>
#include <vector>

/**
* @param in ifstream of the user's inputted file
* @return bool will return true if the inputted file exists in the directory
*/
bool validateInput(std::ifstream &in)
{
	return in.good();
}

/**
* @param inputted string to reverse
* @return string reversed string from input
*/
std::string reverseText(const std::string &input_str)
{
	std::string rev;
	rev.resize(input_str.size());
	int j = 0;
	for (int i = input_str.length() - 1; i >= 0; i--)
	{
		rev[j] = input_str[i];
		j++;
	}
	return rev;
}

int main()
{
	// Declare variables for main run
	bool input_is_valid = true;
	std::string input_file;

	// Get the name of the file that the user wants to reverse
	std::cout << "Enter the name of the file: ";
	getline(std::cin, input_file);

	std::ifstream inputstream(input_file.c_str());
	std::ofstream outputstream;

	// Check if the user's inputted file exists in the directory
	input_is_valid = validateInput(inputstream);

	if (input_is_valid)
	{
		std::string contents;
		std::vector<std::string> saved_conts;

		// Get and the display the contents of the input file
		std::cout << "Original file " << input_file << " content:" << std::endl;
		while (getline(inputstream, contents))
		{
			saved_conts.push_back(contents);
			std::cout << contents << std::endl;
		}

		// Open and rewrite the file with the reversed string, line by line
		outputstream.open(input_file, std::ofstream::in | std::ofstream::out);
		for (int i = 0; i < saved_conts.size(); i++)
		{
			outputstream << reverseText(saved_conts[i]) << "\n";
		}
		outputstream.close();

		// Displayed the reversed contents of the file
		std::cout << "\nReversed file " << input_file << " content:" << std::endl;
		for (int i = 0; i < saved_conts.size(); i++)
		{
			std::cout << reverseText(saved_conts[i]) << "\n";
		}
	}
	else
	{
		// If user inputted file does not exist
		std::cout << "Error opening file " << input_file << "!" << std::endl;
		return 0;
	}

	return 0;
}