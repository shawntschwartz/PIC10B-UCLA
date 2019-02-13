//
// hmw_3_2.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

/**
* @param in input file stream for reading in file
* @return vector of strings separating the file line by line without the end-of-line character
*/
std::vector<std::string> getFileLinesNoEOLChar(std::ifstream &in)
{
	std::string file_contents;
	std::vector<std::string> file_lines_contents;

	while (getline(in, file_contents))
	{
		file_lines_contents.push_back(file_contents);
	}

	return file_lines_contents;
}

/**
* @param in input file stream for reading in file
* @return vector of strings separating the file line by line with the end-of-line character
*/
std::vector<std::string> getFileLinesWithEOLChar(std::ifstream &in)
{
	std::string file_contents;
	std::vector<std::string> file_lines_contents;

	while (getline(in, file_contents))
	{
		file_lines_contents.push_back(file_contents + '\n');
	}

	return file_lines_contents;
}

/**
* @param input_vec vector of strings of lines of text
* @param delim char representing delimiter to separate words by from the input lines
* @return vector of strings separating the input lines into separate words by a delimiter
*/
std::vector<std::string> getLineWords(std::vector<std::string> input_vec, char delim)
{
	std::vector<std::string> words;

	for (int i = 0; i < input_vec.size(); i++)
	{
		std::stringstream ss(input_vec[i]);
		std::string field_val = "";

		while (getline(ss, field_val, delim))
		{
			words.push_back(field_val);
		}
	}

	return words;
}

/**
* @param input_vec vector of strings of lines of text to make into one string
* @return string combined input vector elements into one string
*/
std::string makeOneString(std::vector<std::string> input_vec)
{
	std::string output_string;

	for (auto const &i : input_vec)
	{
		output_string += i;
	}

	return output_string;
}

/**
* @param input_vec vector of strings of lines of text to split into separate words
* @param delim delimiter char value to separate the lines of text from the input_vec
* @return two-dimensional vector of strings with split lines into words by delimiter per each database entry (dimension)
*/
std::vector< std::vector<std::string> > splitLinesIntoWords(const std::vector<std::string> input_vec, char delim)
{
	std::vector< std::vector<std::string> > splitLines;

	for (int i = 0; i < input_vec.size(); i++)
	{
		std::vector<std::string> temp_line;
		temp_line.push_back(input_vec[i]);
		splitLines.push_back(getLineWords(temp_line, delim));
	}

	return splitLines;
}

/**
* @param input_vec any vector of strings to print to the console with an end of line character
*/
void printVec(const std::vector<std::string> input_vec)
{
	for (int i = 0; i < input_vec.size(); i++)
	{
		std::cout << input_vec[i] << std::endl;
	}
}

/**
* @param input_vec any vector of strings to print to the console without an end of line character
*/
void printVecNoEndL(const std::vector<std::string> input_vec)
{
	for (int i = 0; i < input_vec.size(); i++)
	{
		std::cout << input_vec[i];
	}
}

/**
* @param separated_db_words two-dimensional vector of strings with split lines into words by delimiter per each database entry (dimension)
* @param template_to_mod combined template elements into one string for modification and replacement with the database elements
* @param iterator integer counter for looping through number of lines from the original database element for generating the junk letter record (i.e., number of entries)
*/
void replaceTemplatePlaceholders(std::vector< std::vector<std::string> > separated_db_words, std::string template_to_mod, int iterator)
{
	for (int j = 0; j < separated_db_words[iterator].size(); j++)
	{
		std::string strSearch = "|" + std::to_string(j + 1) + "|";
		int pipe_occurance = template_to_mod.find(strSearch);
		while (pipe_occurance != std::string::npos)
		{
			template_to_mod.replace(pipe_occurance, strSearch.size(), separated_db_words[iterator][j]);
			pipe_occurance = template_to_mod.find(strSearch, pipe_occurance + strSearch.size());
		}
	}
	std::cout << template_to_mod << std::endl;
}

/**
* @param num_lines number of lines in the database file (for looping through database records)
* @param template_str combined string from vector of strings from the template file
* @param two-dimensional vector of strings with split lines into words by delimiter per each database entry (dimension)
*/
void generateJunkLetterRecord(int num_lines, std::string template_str, std::vector< std::vector<std::string> > separated_db_words)
{
	for (int i = 0; i < num_lines; i++)
	{
		std::cout << "\nJunk letter for Record " << i << std::endl;
		std::string template_to_modify = template_str;
		replaceTemplatePlaceholders(separated_db_words, template_to_modify, i);
	}
}

int main()
{
	// Declare filename constants
	const std::string database_file = "database.txt";
	const std::string template_file = "template.txt";

	// Declare ifstream
	std::ifstream ipstrm;

	// Retrieve database contents from file line by line
	ipstrm.open(database_file.c_str());
	std::vector<std::string> database_contents = getFileLinesNoEOLChar(ipstrm);
	if (database_contents.size() < 1)
	{
		std::cout << "The database " << database_file << " is empty. Exit!" << std::endl;
		return 0;
	}
	std::cout << "Database content: " << std::endl;
	printVec(database_contents);
	ipstrm.close();

	std::cout << std::endl;

	// Retrieve template contents from file line by line
	ipstrm.open(template_file.c_str());
	std::vector<std::string> template_contents = getFileLinesWithEOLChar(ipstrm);
	std::string template_whole = makeOneString(template_contents);
	std::cout << "Template content: " << std::endl;
	printVecNoEndL(template_contents);
	ipstrm.close();

	// For looping through each entry of the database
	int num_db_lines = database_contents.size();

	std::vector< std::vector<std::string> > database_words = splitLinesIntoWords(database_contents, '|');

	generateJunkLetterRecord(num_db_lines, template_whole, database_words);

	return 0;
}