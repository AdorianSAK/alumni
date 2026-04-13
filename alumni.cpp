//===
//	Libraries
//===

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>

//===
//	Classes
//===

class Student
{
private:
	char name[15];
	char lastNameA[15];
	char lastNameB[15];
	char career[15];
	int uniqueCode;
	float grade;

	void orderRecord(std::fstream&);

public:
	void record();
	void show();
	void searchCode(int);

	void modify(int);
	void erase(int);
};

//===
//	Prototyping
//===

bool isValidInt(const std::string& input);
bool isValidFloat(const std::string& input);

//===
//	Start of Program
//===

int main()
{
	// Definition of systematic variables
	int cursorPosition;

	Student oneStudent;
	//oneStudent.show();

	//	Menu loop
	do
	{
		std::cout << "PICK AN OPTION:\n"
				  << "1. RECORD\n2. SHOW\n"
				  << "3. SEARCH CODE\n4. SEARCH CAREER\n"
				  << "5. EXIT\nOPTION:\t";

		if (!(std::cin >> cursorPosition)) {
		    std::cin.clear(); // reset error flags
		    std::cin.ignore(1000, '\n'); // discard bad input
		    std::cout << "\nInvalid input. Enter a number.\n\n";
		}else if(cursorPosition < 1 || cursorPosition > 5)
		{
			std::cout << "\nSelection out of range."
					  << " Enter a number from 1 to 5.\n\n";
		}

		switch(cursorPosition)
		{
		case 1:
			oneStudent.record();
			break;
		}

	}while(cursorPosition != 5);

	return 0;
}

//===
//	Class Methods
//===
	
	//	Student
		//	Record
void Student::record()
{
	std::cout << "\nEnter student's name:\n";
	std::cin.getline(name, 16);
	std::cout << "\nEnter paternal surname:\n";
	std::cin.getline(lastNameA, 16);
	std::cout << "\nEnter maternal surname:\n";
	std::cin.getline(lastNameB, 16);

		//	Numerical entries, which are some times problematic.
			//	Code
	std::string input;
	std::cout << "\nEnter student's code:\n";
	while(true)
	{
		std::getline(std::cin, input);
		if(isValidInt(input))
		{
			uniqueCode = std::stoi(input);
			break;
		}
		std::cout << "Invalid code input. Try again:\n";
	}
		//	Not numerical
	std::cout << "\nEnter student's career:\n";
	std::cin.getline(career, 16);
			//	Grades
	std::cout << "\nEnter student's grade:\n";
	while(true)
	{
		std::getline(std::cin, input);
		if(isValidFloat(input))
		{
			grade = std::stof(input);
			break;
		}
		std::cout << "Invalid grade input. Try again:\n";
	}

		//	Creation of file
	std::fstream studentFile("students.txt", std::ios::app | std::ios::binary);
	
		//	Ordering logic goes here if needd
	studentFile.seekg(0, std::ios::end);
	std::streampos size = studentFile.tellg();

	if(size != sizeof(Student))
	{
		//	Ordering here 
		std::cout << "This file has more than one student record.\n";
		orderRecord(studentFile);
	}

		//	Writing of data into the file
	studentFile.write((char*) this, sizeof(*this));

		//	Closing the file
	studentFile.close();
}
	//	Order records
void Student::orderRecord(std::fstream& file)
{
	char tmpName[15];
	strcpy(tmpName, name);
	char tmpLastNameA[15];
	strcpy(tmpLastNameA, lastNameA);
	char tmpLastNameB[15];
	strcpy(tmpLastNameB, lastNameB);
	char tmpCareer[15];
	strcpy(tmpCareer, career);
	int tmpUniqueCode = uniqueCode;
	float tmpGrade = grade;

	file.seekg(0, std::ios::end);
	std::streampos size = file.tellg();

	int count = size / sizeof(Student);
	std::cout << "This file has " << size << " entries.\n";
}

	//	Show
void Student::show()
{
	std::fstream studentFile("students.txt", std::ios::in|std::ios::out);

	if(!studentFile.good())
	{
		std::cout << "\nDamaged or corrupted file.\n";
	}else
	{
		while (studentFile.read((char*)this, sizeof(*this)))
		{
		    std::cout << "Name: " << name << " " << lastNameA << " "
		              << lastNameB << '\n'
		              << "Code: " << uniqueCode << '\n'
		              << "Carrer: " << career << '\n'
		              << "Grade: " << grade << '\n'
		              << "-----------------------------------------\n";
		}
	}
	studentFile.close();
}

//===
//	System functions
//===

	//	int Validation
bool isValidInt(const std::string& input)
{
	if(input.empty()) return false;

	int start = 0;

	if(input[0] == '-' || input[0] == '+')
		start = 1;

	for(int i = start; i < input.size(); i ++)
	{
		if(!isdigit(input[i]))
		{
			return false;
		}
	}

	return true;
}

	//	float Validation
bool isValidFloat(const std::string& input)
{
    if (input.empty()) return false;

    int start = 0;
    bool hasDecimalPoint = false;
    bool hasDigit = false;

    if(input[0] == '-' || input[0] == '+')
        start = 1;

    for(int i = start; i < input.size(); i ++)
    {
        if (isdigit(input[i]))
        {
            hasDigit = true;
        }
        else if(input[i] == '.' && !hasDecimalPoint)
        {
            hasDecimalPoint = true;
        }
        else
        {
            return false;
        }
    }

    return hasDigit;
}