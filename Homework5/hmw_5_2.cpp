//
// hmw_5_2.cpp
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
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>

/* Tasks
* Modify the merge sort alogrithm to sort a vector of Employees by salary.
* Write a program that reads the list of people's records from a file data2.txt,
* creates a corresponding vector<Employee> and displays the name and salary for each employee.
* After that the program should sort vector<Employee> and display the name and the salary of
* employees in the sorted vector.
*/

class Employee
{
public:
	Employee(std::string e_name, double e_salary) : name(e_name), salary(e_salary) { }

	std::string get_name() const { return name; }
	double get_salary() const { return salary; }

protected:
	std::string name;
	double salary;
};

/**
* Reads in contents of file line-by-line and stores them in a vector of strings.
* @param in referenced ifstream to read in file contents
* @return vector<string> of text file's line contents
*/
std::vector<std::string> getFileLines(std::ifstream &in)
{
	std::string file_contents;
	std::vector<std::string> file_line_contents;

	while (getline(in, file_contents))
	{
		file_line_contents.push_back(file_contents);
	}

	return file_line_contents;
}

/**
* Separates lines of file by char delimiter.
* @param input_vec input vector of strings to separate
* @param delim char delimiter value to separate values by
* @return vector of strings representing employee names (first part of each line)
*/
std::tuple<std::vector<std::string>, std::vector<int>> getEmployeeDetails(std::vector<std::string> input_vec, char delim)
{
	std::vector<std::string> names;
	std::vector<int> salaries;
	std::vector<int> indices;

	for (int i = 0; i < input_vec.size(); i++)
	{
		std::stringstream ss(input_vec[i]);
		std::string line_value = "";

		std::string tmp_name;
		std::string tmp_salary;

		while (getline(ss, line_value))
		{
			std::stringstream sep(line_value);

			getline(sep, tmp_name, delim);
			names.push_back(tmp_name);

			getline(sep, tmp_salary, delim);
			salaries.push_back(stoi(tmp_salary));
		}
	}

	return std::make_tuple(names, salaries);
}

/**
* Prints two vectors as an employee to the console.
* @param names input vector of employee names to print
* @param salaries input veector of employee salaries to print
*/
void printEmployees(std::vector<std::string> names, std::vector<int> salaries)
{
	for (int i = 0; i < names.size(); i++)
	{
		std::cout << names[i] << ", $" << salaries[i] << std::endl;
	}
}

// Merge sort algorithm
/**
* Merges two adjacent ranges in a vector.
* @param a the vector with the elements to merge
* @param from the start of the first range
* @param mid the end of the first range
* @param to the end of the second range
*/
void merge(std::vector<int> &a, std::vector<std::string> &n_names, int from, int mid, int to)
{
	int n = to - from + 1; // size of range to be merged

						   // Merge both halves into a temp vector b
	std::vector<int> b(n);

	// Merge vector of strings for employee names
	std::vector<std::string> names_b(n);

	int i1 = from; // Next element to consider in the first half
	int i2 = mid + 1; // Next element to consider in the second half
	int j = 0; // Next open position in b

			   // As long as neither i1 or i2 are past the end,
			   // move the smaller element into b
	while (i1 <= mid && i2 <= to)
	{
		if (a[i1] < a[i2])
		{
			b[j] = a[i1];
			names_b[j] = n_names[i1];
			i1++;
		}
		else
		{
			b[j] = a[i2];
			names_b[j] = n_names[i2];
			i2++;
		}
		j++;
	}

	// Note that only one of the two while loops below are executed

	// Copy any remaining entries of the first half
	while (i1 <= mid)
	{
		b[j] = a[i1];
		names_b[j] = n_names[i1];
		i1++;
		j++;
	}

	// Copy any remaining entries of the second half
	while (i2 <= to)
	{
		b[j] = a[i2];
		names_b[j] = n_names[i2];
		i2++;
		j++;
	}

	// Copy back from the temporary vector
	for (j = 0; j < n; j++)
	{
		a[from + j] = b[j];
		n_names[from + j] = names_b[j];
	}
}

/**
* Sorts the elements in a range of a vector.
* @param a the vector with the elements to sort
* @param from start of the range to sort
* @param to end of the range to sort
*/
void merge_sort(std::vector<int> &a, std::vector<std::string> &n_names, int from, int to)
{
	// Edge case to break out of recursion
	if (from == to) return;

	// Get the middle of the vector (midpoint)
	int mid = (from + to) / 2;

	// Sort the first and the second half
	merge_sort(a, n_names, from, mid);
	merge_sort(a, n_names, mid + 1, to);
	merge(a, n_names, from, mid, to);
}

/**
* Swaps two strings.
* @param string_one is the first string to swap
* @param string_two is the second string to swap
*/
void swap(std::string &string_one, std::string &string_two)
{
	std::string temp = string_one;
	string_one = string_two;
	string_two = temp;
}

int main()
{
	std::vector<std::string> infile_lines;
	std::vector<std::string> file_names;
	std::vector<int> file_salaries;

	// Get contents from textfile
	std::string filename = "data2.txt";
	std::ifstream fstream(filename.c_str());
	infile_lines = getFileLines(fstream);
	fstream.close();

	// Return employee details from tuple into two separate vectors (string, int)
	std::tie(file_names, file_salaries) = getEmployeeDetails(infile_lines, '|');

	std::cout << std::endl;

	// Before sorting
	std::cout << "Employees, before sorting:" << std::endl;
	printEmployees(file_names, file_salaries);

	// After sorting
	std::cout << "\nEmployees, after sorting:" << std::endl;
	merge_sort(file_salaries, file_names, 0, file_salaries.size() - 1);
	printEmployees(file_names, file_salaries);

	std::cout << std::endl;

	return 0;
}