//
// hmw_2_2.cpp
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
// Implement base class "Appointment" and derived classes "Onetime", "Daily", "Weekly", and "Monthly"
// Make sure to tackle edge case of Leap Year (i.e., check if it is a leap year)

/**
* @param search input string in MM/DD/YYYY format to extract dates into separate elements in vector of strings
* @return vector<string> separated components of MM/DD/YYYY input format
*/
std::vector<std::string> ExtractDates(const std::string search)
{
	// Get all occurances of '/' from inputted year and store their indices
	std::vector<int> indices;
	for (size_t i = 0; i < search.size(); i++)
	{
		if (search[i] == '/')
		{
			indices.push_back(i);
		}
	}
	int startIdx = 0;
	int strLength = 0;
	std::vector<std::string> dates;
	std::string date_substr;
	for (size_t i = 0; i < indices.size() + 1; i++)
	{
		if (i < indices.size())
		{
			startIdx = indices[i] - 2; // start 1 char position after the '/'
			strLength = 2;
			date_substr = search.substr(startIdx, strLength);
			dates.push_back(date_substr);
		}
		else {
			int yearIdx = indices[indices.size() - 1];
			startIdx = yearIdx + 1; // start 1 char position after the '/'
			strLength = 4;
			date_substr = search.substr(startIdx, strLength);
			dates.push_back(date_substr);
		}
	}

	return dates;
}

// Zeller's Congruence: Return day of the week of a given date (Gregorian Calendar)
/**
* @param year 4 digit year number
* @param month 2 digit month number
* @param day 1 or 2 digit day number
* @return int numerical digit representing day of the week (0 = Saturday, 1 = Sunday, 2 = Monday, ..., 6 = Friday)
*/
int GetDayOfWeek(int year, int month, int day)
{
	int h = 0;

	// corrections for edge cases to the Zeller's Congruence
	if (month == 1) // For January
	{
		month = 13;
		year--;
	}
	if (month == 2) // For February
	{
		month = 14;
		year--;
	}

	int year_of_century = year % 100;
	int zero_based_century = year / 100;

	h = (day + (13 * (month + 1) / 5) + year_of_century + (year_of_century / 4) + (zero_based_century / 4) - (2 * zero_based_century)) % 7;

	return h;
}

// Declare base class Appointment
class Appointment
{
public:
	Appointment() {}

	Appointment(std::string input_description, std::string input_date, std::string input_time)
	{
		description = input_description;
		startDate = input_date;
		time = input_time;
	}

	void set_description(std::string input_description) { description = input_description; }
	void set_date(std::string input_date) { startDate = input_date; }
	void set_time(std::string input_time) { time = input_time; }

	std::string get_description() const { return description; }
	std::string get_date() const { return startDate; }
	std::string get_time() const { return time; }

	virtual bool occurs_on(int year, int month, int day)
	{
		return false;
	}

	~Appointment() {}

protected:
	std::string description;
	std::string startDate;
	std::string time;
};

class Onetime : public Appointment
{
public:
	Onetime() {}
	Onetime(std::string input_description, std::string input_date, std::string input_time) : Appointment(input_description, input_date, input_time) {}

	virtual bool occurs_on(int year, int month, int day)
	{
		std::vector<std::string> tmp_date = ExtractDates(startDate);
		int tmp_month = std::stoi(tmp_date[0]);
		int tmp_day = std::stoi(tmp_date[1]);
		int tmp_year = std::stoi(tmp_date[2]);
		if (tmp_year == year && tmp_month == month && tmp_day == day)
		{
			return true;
		}
		else
		{
			return false;
		}
		return false;
	}

	~Onetime() {}
};

class Daily : public Appointment
{
public:
	Daily() {}
	Daily(std::string input_description, std::string input_date, std::string input_time) : Appointment(input_description, input_date, input_time) {}

	virtual bool occurs_on(int year, int month, int day)
	{
		return true;
	}
};

class Weekly : public Appointment
{
public:
	Weekly() {}
	Weekly(std::string input_description, std::string input_date, std::string input_time) : Appointment(input_description, input_date, input_time) {}

	virtual bool occurs_on(int year, int month, int day)
	{
		std::vector<std::string> tmp_date = ExtractDates(startDate);
		int tmp_month = std::stoi(tmp_date[0]);
		int tmp_day = std::stoi(tmp_date[1]);
		int tmp_year = std::stoi(tmp_date[2]);

		if (GetDayOfWeek(tmp_year, tmp_month, tmp_day) == GetDayOfWeek(year, month, day))
		{
			return true;
		}
		else
		{
			return false;
		}
		return false;
	}

	~Weekly() {}
};

class Monthly : public Appointment
{
public:
	Monthly() {}
	Monthly(std::string input_description, std::string input_date, std::string input_time) : Appointment(input_description, input_date, input_time) {}

	virtual bool occurs_on(int year, int month, int day)
	{
		std::vector<std::string> tmp_date = ExtractDates(startDate);
		int tmp_day = std::stoi(tmp_date[1]);
		if (tmp_day == day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	~Monthly() {}
};

/**
* @param year input 4 digit year number
* @return bool true if year is a leap year
*/
bool CheckIfLeapYear(int year)
{
	if (year % 4 != 0)
	{
		return false;
	}
	else if (year % 100 != 0)
	{
		return true;
	}
	else if (year % 400 != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
* @param year 4 digit year number
* @param month 2 digit month number
* @param day 1 or 2 digit day number
* @return bool true if valid date, not an out of bounds date or a day in a leap year that doesn't exist
*/
bool ValidDate(int year, int month, int day)
{
	if (month == 2)
	{
		if (CheckIfLeapYear(year))
		{
			return day <= 29;
		}
		else {
			return day <= 28;
		}
	}

	if (month < 1 || month > 12)
	{
		return false;
	}

	if (day < 1 || day > 31)
	{
		return false;
	}

	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		return day <= 30;
	}

	return true;
}



/**
* @param Appointment* reference address to instance of base class appointment
* @param vector<Appointment*> reference address to vector of instances of base classes appointment
* @param string reference address to string of the description of the appointment
*/
void CaptureAppointment(Appointment*& a, std::vector<Appointment*> &aps, std::string &ipt_desc)
{
	std::string input_text;

	a->set_description(ipt_desc);
	std::cout << "Appointment's starting date: ";
	getline(std::cin, input_text);
	a->set_date(input_text);
	std::cout << "Appointment's time: ";
	getline(std::cin, input_text);
	a->set_time(input_text);
	std::cout << std::endl;

	aps.push_back(a);
}

// Deallocate memory from vector of pointers to Appointment
/**
* @param vector<Appointment*> reference address to vector of instances of base classes appointment
*/
void deallocmem(std::vector<Appointment*> &appt)
{
	for (std::vector<Appointment*>::iterator i = appt.begin(); i != appt.end(); ++i)
	{
		delete (*i);
	}

	appt.clear();
}

int main()
{
	std::cout << "Enter the list of appointments.\n" << std::endl;

	std::vector<Appointment*> appointments;

	std::string input_text;
	std::string appt_type;

	char user_cont;

	do {
		std::cout << "Appointment's description: ";
		getline(std::cin, input_text);

		std::cout << "Appointment's type: ";
		getline(std::cin, appt_type);

		if (appt_type == "Onetime")
		{
			Appointment* appt = new Onetime();
			CaptureAppointment(appt, appointments, input_text);
		}
		else if (appt_type == "Daily")
		{
			Appointment* appt = new Daily();
			CaptureAppointment(appt, appointments, input_text);
		}
		else if (appt_type == "Weekly")
		{
			Appointment* appt = new Weekly();
			CaptureAppointment(appt, appointments, input_text);
		}
		else if (appt_type == "Monthly")
		{
			Appointment* appt = new Monthly();
			CaptureAppointment(appt, appointments, input_text);
		}
		else
		{
			std::cout << "You have entered an invalid appointment type!" << std::endl;
			std::cout << "Must be of type: ('Onetime', 'Daily', 'Weekly', 'Monthly')." << std::endl;
			return 0;
		}

		std::cout << "Another appointment (y/n)? ";
		std::cin >> user_cont;
		std::cin.ignore();
		std::cout << std::endl;

	} while (user_cont == 'y');

	std::cout << "------------------------" << std::endl;
	std::cout << "Enter a date: ";
	getline(std::cin, input_text);
	std::cout << std::endl;

	// check if the appointment date exists

	// Break apart user inputted date into ints
	std::vector<std::string> tmp_date = ExtractDates(input_text);
	int tmp_month = std::stoi(tmp_date[0]);
	int tmp_day = std::stoi(tmp_date[1]);
	int tmp_year = std::stoi(tmp_date[2]);

	if (ValidDate(tmp_year, tmp_month, tmp_day))
	{
		std::cout << "The list of appointments that happen on " << input_text << ":\n" << std::endl;

		for (size_t i = 0; i < appointments.size(); i++)
		{
			if (appointments[i]->occurs_on(tmp_year, tmp_month, tmp_day))
			{
				std::cout << " " << i << " " << appointments[i]->get_description() << ", " << appointments[i]->get_time() << std::endl;
			}
		}

	}
	else
	{
		std::cout << "You have entered an invalid date! " << std::endl;
		return 0;
	}

	deallocmem(appointments);

	std::cout << std::endl;
	return 0;
}