//
// hmw_1_1.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <string>
#include <vector>

// Declare function prototypes
bool user_continue(char);

// Declaration of class: Person
class Person
{
public:
	Person()
	{
		bestFriend = NULL;
		popCounter = 0;
	}

	Person(std::string person_name)
	{
		bestFriend = NULL;
		popCounter = 0;
		this->name = person_name;
	}

	Person(std::string person_name, Person* person_bestFriend)
	{
		this->bestFriend = person_bestFriend;
		popCounter = 0;
		this->name = person_name;
	}

	void set_best_friend(Person* person_bestFriend)
	{
		this->bestFriend = person_bestFriend;
		person_bestFriend->popCounter++;
	}

	std::string get_name() const
	{
		return this->name;
	}

	std::string get_best_friend() const
	{
		if (this->bestFriend != NULL)
		{
			return bestFriend->name;
		}
		else
		{
			return "NONE";
		}
	}

	int get_popularity() const
	{
		return this->popCounter;
	}

private:
	std::string name;
	Person* bestFriend;
	int popCounter;
};

int main()
{
	bool userInput = true; // for continuation of entering people's names
	std::string inputName; // string to store user input

	// declare vector for pointing to inputted Persons
	std::vector<Person*> inputPeople;

	// do while userInput is true (controlled by user input)
	do
	{
		// intake user input for names and push_back to vector of pointers to Persons
		std::cout << "Name: ";
		std::cin >> inputName;
		inputPeople.push_back(new Person(inputName));

		// receive user input to see if they will continue to enter more people's names
		char decision;
		std::cout << "\nContinue (y/n)? ";
		std::cin >> decision;
		userInput = user_continue(decision);
		std::cout << std::endl;
	} while (userInput);

	// user will input the names of the best friends for each of the pointers to Persons in the vector
	std::cout << "Enter the name of best friends: \n" << std::endl;
	for (int i = 0; i < inputPeople.size(); i++)
	{
		std::cout << "Best friend of " << inputPeople[i]->get_name() << ": ";
		std::cin >> inputName;
		for (int j = 0; j < inputPeople.size(); j++)
		{
			if (inputPeople[j]->get_name() == inputName)
			{
				inputPeople[i]->set_best_friend(inputPeople[j]);
				break;
			}
		}
	}

	// output display to console the related information of best friends and popularity
	std::cout << "\nInformation:" << std::endl;
	for (int i = 0; i < inputPeople.size(); i++)
	{
		std::cout << inputPeople[i]->get_name() << " : " << inputPeople[i]->get_best_friend() << " : " << inputPeople[i]->get_popularity() << std::endl;
	}

	// deallocate memory from vector of pointers to Persons
	for (std::vector<Person*>::iterator i = inputPeople.begin(); i != inputPeople.end(); ++i)
	{
		delete (*i);
	}

	inputPeople.clear();

	return 0;
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