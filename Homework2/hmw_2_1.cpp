//
// hmw_2_1.cpp
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

// Tasks
// Implement classes Person, Student and Instructor described in P8.2
// Write a program that reads
// 1) a name and a birthday for a Person
// 2) a name, a birthday, and a salary for an Instructor
// 3) a name, a birthday, and a major for a Student
// Write a member function print() to print out the information about each person on the screen

// P8.2
// Implement a base class Person. Derive classes Student and Instructor from Person.
//  A person has a name and a birthday.
// A student has a major
// An instructor has a salary.
// Write the class definitions, the constructors, and the member functions print() for all classes.

// Declare class Person
class Person
{
public:
	Person() {}
	Person(std::string input_name, std::string input_birthday) { name = input_name; birthday = input_birthday; }

	void set_name(std::string input_name) { name = input_name; }
	void set_birthday(std::string input_birthday) { birthday = input_birthday; }

	std::string get_name() const { return name; }
	std::string get_birthday() const { return birthday; }

	virtual void print() const {
		std::cout << "Name: " << get_name() << std::endl;
		std::cout << "Birthday: " << get_birthday() << std::endl;
	}

	virtual ~Person() {}

protected:
	std::string name;
	std::string birthday;
};

class Instructor : public Person
{
public:
	Instructor() {}
	Instructor(std::string input_name, std::string input_birthday, int input_salary) : Person(input_name, input_birthday), salary(input_salary) {}

	void set_salary(int input_salary) { salary = input_salary; }

	int get_salary() const { return salary; }

	virtual void print() const {
		std::cout << "Name: " << get_name() << std::endl;
		std::cout << "Birthday: " << get_birthday() << std::endl;
		std::cout << "Salary: " << get_salary() << std::endl;
	}

	virtual ~Instructor() {}

private:
	int salary;
};

class Student : public Person
{
public:
	Student() {}
	Student(std::string input_name, std::string input_birthday, std::string input_major) : Person(input_name, input_birthday), major(input_major) {}

	void set_major(std::string input_major) { major = input_major; }

	std::string get_major() const { return major; }

	virtual void print() const {
		std::cout << "Name: " << get_name() << std::endl;
		std::cout << "Birthday: " << get_birthday() << std::endl;
		std::cout << "Major: " << get_major() << std::endl;
	}

	virtual ~Student() {}

private:
	std::string major;
};

// Overload function for different intakes of derived classes of Person
/**
* @param who literal name of person being taken in
* @param person base instance of class person
*/
void intake_information(std::string who, Person* person)
{
	std::string user_input_string;

	std::cout << who << "'s full name: ";
	getline(std::cin, user_input_string);
	person->set_name(user_input_string);
	std::cout << "Person's birthday (mm/dd/yyyy): ";
	getline(std::cin, user_input_string);
	person->set_birthday(user_input_string);
	std::cout << std::endl;
}

/**
* @param who literal name of person being taken in
* @param instructor derived class instance of base class person
*/
void intake_information(std::string who, Instructor* instructor)
{
	std::string user_input_string;
	int user_input_int;

	std::cout << who << "'s full name: ";
	getline(std::cin, user_input_string);
	instructor->set_name(user_input_string);
	std::cout << "Instructor's birthday (mm/dd/yyyy): ";
	getline(std::cin, user_input_string);
	instructor->set_birthday(user_input_string);
	std::cout << "Instructor's salary: ";
	std::cin >> user_input_int;
	instructor->set_salary(user_input_int);
	std::cin.ignore();
	std::cout << std::endl;
}

/**
* @param who literal name of person being taken in
* @param student derived class instance of base class person
*/
void intake_information(std::string who, Student* student)
{
	std::string user_input_string;

	std::cout << "Student's full name: ";
	getline(std::cin, user_input_string);
	student->set_name(user_input_string);
	std::cout << "Student's birthday (mm/dd/yyyy): ";
	getline(std::cin, user_input_string);
	student->set_birthday(user_input_string);
	std::cout << "Student's major: ";
	getline(std::cin, user_input_string);
	student->set_major(user_input_string);
	std::cout << std::endl;
}

// Overload function for different derived classes of Person
/**
* @param who literal name of person being taken in
* @param person base instance of class person
*/
void print_information(std::string who, Person* person)
{
	std::cout << who << "'s Information:" << std::endl;
	person->print();
	std::cout << std::endl;
}

/**
* @param who literal name of person being taken in
* @param instructor derived class instance of base class person
*/
void print_information(std::string who, Instructor* instructor)
{
	std::cout << who << "'s Information:" << std::endl;
	instructor->print();
	std::cout << std::endl;
}

/**
* @param who literal name of person being taken in
* @param student derived class instance of base class person
*/
void print_information(std::string who, Student* student)
{
	std::cout << who << "'s Information:" << std::endl;
	student->print();
	std::cout << std::endl;
}

int main()
{
	// Declare pointers and dynamically allocate memory for each inputted object
	Person* p = new Person();
	Instructor* i = new Instructor();
	Student* s = new Student();

	// Collect person's information
	intake_information("Person", p);

	// Collect Instructor's information
	intake_information("Instructor", i);

	// Collect Student's information
	intake_information("Student", s);

	// Print out information to console
	print_information("Person", p);
	print_information("Instructor", i);
	print_information("Student", s);

	// Deallocate dynamic memory for People pointers
	delete p;
	delete i;
	delete s;

	return 0;
}
