//
// hmw_7_1.cpp
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
#include <vector>
#include <string>
#include <tuple>

using namespace std;

class HeapTasks
{
public:
	HeapTasks();

	void push(pair<string, int> new_element);
	pair<string, int> top() const;
	void pop();
	int size() const;

	void fix_heap();
	int get_left_child_index(int index);
	int get_right_child_index(int index);
	int get_parent_index(int index);
	pair<string, int> get_left_child(int index);
	pair<string, int> get_right_child(int index);
	pair<string, int> get_parent(int index);

	vector<pair<string, int>> elements;
};

HeapTasks::HeapTasks()
{
	elements.push_back(pair<string, int>("", 0));
}

void HeapTasks::push(pair<string,int> new_element)
{
	elements.push_back(pair<string, int>("", 0));
	int index = elements.size() - 1;

	while (index > 1 && (get_parent(index).second < new_element.second))
	{
		elements[index] = get_parent(index);
		index = get_parent_index(index);
	}
	elements[index] = new_element;
}

int HeapTasks::size() const
{
	return elements.size() - 1;
}

pair<string, int> HeapTasks::top() const
{
	return elements[1];
}

void HeapTasks::pop()
{
	int last_index = elements.size() - 1;
	pair<string, int> last = elements[last_index];
	elements.pop_back();

	if (last_index > 1)
	{
		elements[1] = last;
		fix_heap();
	}
}

void HeapTasks::fix_heap()
{
	pair<string, int> root = elements[1];
	int last_index = elements.size() - 1;

	int index = 1;
	bool more = true;
	while (more)
	{
		int child_index = get_left_child_index(index);
		if (child_index <= last_index)
		{
			// Get larger child
			pair<string, int> child = get_left_child(index);
			if (get_right_child_index(index) <= last_index && get_right_child(index).second > child.second)
			{
				child_index = get_right_child_index(index);
				child = get_right_child(index);
			}

			// Check if smaller child is larger than root
			if (child.second > root.second)
			{
				// Promote child
				elements[index] = child;
				index = child_index;
			}

			else
			{
				// Root is larger than both children
				more = false;
			}
		}

		else
		{
			// No children
			more = false;
		}
	}

	// Store root element in vacant slot
	elements[index] = root;
}

int HeapTasks::get_left_child_index(int index)
{
	return 2 * index;
}

int HeapTasks::get_right_child_index(int index)
{
	return 2 * index + 1;
}

int HeapTasks::get_parent_index(int index)
{
	return index / 2;
}

pair<string, int> HeapTasks::get_left_child(int index)
{
	return elements[2 * index];
}

pair<string, int> HeapTasks::get_right_child(int index)
{
	return elements[2 * index + 1];
}

pair<string, int> HeapTasks::get_parent(int index)
{
	return elements[index / 2];
}

vector<string> getFileLines(ifstream & in)
{
	string file_contents;
	vector<string> lines;

	while (getline(in, file_contents))
	{
		lines.push_back(file_contents);
	}

	return lines;
}

tuple<vector<string>, vector<int>> separateInput(vector<string> in, char delim)
{
	vector<string> task_names;
	vector<int> priorities;

	for (int i = 0; i < in.size(); i++)
	{
		stringstream ss(in[i]);
		string line_val = "";

		string tmp_task_name;
		string tmp_priority;

		while (getline(ss, line_val))
		{
			stringstream sep(line_val);

			getline(sep, tmp_task_name, delim);
			task_names.push_back(tmp_task_name);

			getline(sep, tmp_priority, delim);
			priorities.push_back(stoi(tmp_priority));
		}
	}

	return make_tuple(task_names, priorities);
}

void printVecPair(vector<string> in_one, vector<int> in_two)
{
	for (int i = 0; i < in_one.size(); i++)
	{
		std::cout << in_one[i] << "|" << in_two[i] << endl;
	}
}

int main()
{
	char user_continue; // for looping until user exits

	do
	{
		// Get file name and tasks from txt file
		cout << "Enter the file name containing tasks: ";
		string input_file = "";
		getline(cin, input_file);
		ifstream fstream(input_file.c_str());
		vector<string> file_contents = getFileLines(fstream);
		fstream.close();

		cout << "\nDisplaying uploaded list of tasks (before heap):" << endl;

		// Split file contents via Tuple
		vector<string> taskNames;
		vector<int> taskPriorities;
		tie(taskNames, taskPriorities) = separateInput(file_contents, '|');

		// Print the pre-heap priority sorted elements
		printVecPair(taskNames, taskPriorities);
		
		// Initialize tasks of HeapTasks
		HeapTasks tasks;

		size_t numTasks = taskNames.size();
		for (size_t i = 0; i < numTasks; ++i)
		{
			tasks.push(make_pair(taskNames[i], taskPriorities[i]));
		}

		cout << "\nDisplaying HeapTasks:" << endl;
		while (tasks.size() > 0)
		{
			pair<string, int> task = tasks.top();
			tasks.pop();
			cout << task.first << "|" << task.second << "\n";
		}

		cout << "\nContinue (y/n)? ";
		cin >> user_continue;
		cin.ignore();
		if (user_continue == 'y' || user_continue == 'Y')
		{
			cout << endl;
		}
	} while (user_continue == 'y' || user_continue == 'Y');
	
	return 0;
}