//===
//	Libraries
//===

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string.h>

//	Checks if it's Windows, to use correct function

#ifdef _WIN32
    #define strcasecmp _stricmp
#endif

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

public:
	void record();
	void show(int);
	void searchCode(int);
	void orderRecord(int);
	void binarySearch(int);
	void searchCareer(int);

	void modify(int);
	void erase(int);
};

//===
//	Prototyping
//===

bool isValidInt(const std::string& input);
bool isValidFloat(const std::string& input);
int entriesCounter();

//===
//	Start of Program
//===

int main()
{
	// Definition of systematic variables
	int cursorPosition;

	Student oneStudent;

	int entries = entriesCounter();
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
		std::cin.ignore();

		//	Swtich and situations
		switch(cursorPosition)
		{
		case 1:
			oneStudent.record();
			oneStudent.orderRecord(entries);
			// Stuff has been added.
			std::cout << "\nStudent's record added successfully\n\n";
			break;
		case 2:
			oneStudent.show(entries);
			break;
		case 3:
			oneStudent.binarySearch(entries);
			break;
		case 4:
			oneStudent.searchCareer(entries);
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
	std::cin.getline(name, 15);
	std::cout << "\nEnter paternal surname:\n";
	std::cin.getline(lastNameA, 15);
	std::cout << "\nEnter maternal surname:\n";
	std::cin.getline(lastNameB, 15);

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
	std::cin.getline(career, 15);
			//	Grades
	std::cout << "\nEnter student's average grade:\n";
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
	//std::ofstream studentFile("students.txt", std::ios::app | std::ios::binary);
	
		//	Ordering logic goes here if needed
/*
	studentFile.seekg(0, std::ios::end);
	std::streampos size = studentFile.tellg();

	if(size != sizeof(Student))
	{
		//	Ordering here 
		std::cout << "This file has more than one student record.\n";
		orderRecord(studentFile);
	}
*/
		//	Writing of data into the file
	//studentFile.write((char*) this, sizeof(*this));

		//	Closing the file
	//studentFile.close();
}
	//	Order records
void Student::orderRecord(int entries)
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

	std::fstream studentFile("students.txt", std::ios::in | std::ios::out | std::ios::binary);

	//std::cout << "This file has " << count << " entries.\n";

	if(entries == 0)	//	File is empty? Then continue and write.
	{
		studentFile.write((char*) this, sizeof(*this));
		studentFile.close();
		return;
	}

	int* allCodes = new int[entries];
	int p = 0;

	while(studentFile.read((char*)this, sizeof(*this)))
	{
		allCodes[p] = uniqueCode;
		p ++;
	}

	p = 0;
	while (p < entries && allCodes[p] < tmpUniqueCode)
	{
	    p++;	//	Location of the new record
	}

	int lastIndex = entries - 1;
	
	for (int i = lastIndex; i >= p; i--)
	{
	    // read record at i
	    studentFile.seekg(i * sizeof(Student), std::ios::beg);
	    studentFile.read((char*)this, sizeof(*this));

	    studentFile.clear();

	    // write it at i+1
	    studentFile.seekp((i + 1) * sizeof(Student), std::ios::beg);
	    studentFile.write((char*)this, sizeof(*this));

	    studentFile.clear();
	}

	//	Reasignation of object
	strcpy(name, tmpName);
	strcpy(lastNameA, tmpLastNameA);
	strcpy(lastNameB, tmpLastNameB);
	strcpy(career, tmpCareer);
	uniqueCode = tmpUniqueCode;
	grade = tmpGrade;

	//	Write object to designed place.
	studentFile.seekp(p * sizeof(Student), std::ios::beg);
	studentFile.write((char*)this, sizeof(*this));

	studentFile.close();
	delete[] allCodes;
}

	//	Show
void Student::show(int entries)
{
	std::ifstream studentFile("students.txt", std::ios::in);

	if(!studentFile.good())
	{
		std::cout << "\nDamaged, corrupted or inexistant file.\n\n";
	}else
	{

		std::cout << "\nThis file has " << entries << " student entries.\n\n";

		studentFile.clear();
		studentFile.seekg(0, std::ios::beg);

		int count = 1;

		while(studentFile.read((char*)this, sizeof(*this)))
		{
			std::cout << "Entry " << count << '\n';

		    std::cout << "Name: " << name << " " << lastNameA << " "
		              << lastNameB << '\n'
		              << "Code: " << uniqueCode << '\n'
		              << "Carrer: " << career << '\n'
		              << "Average grade: " << grade << '\n'
		              << "-----------------------------------------\n";
		    count ++;
		}
	}
	studentFile.close();
}

	//	Binary search
void Student::binarySearch(int entries)
{
	if(entries = 0)
	{
		std::cout << "\nThere's no records here!\n\n";
		return;
	}

	std::ifstream studentFile("students.txt", std::ios::in | std::ios::binary);

	int arrayLength = entries;

	int* array = new int[arrayLength];
	int p = 0;
	while(studentFile.read((char*)this, sizeof(*this)))
	{
		array[p] = uniqueCode;
		p ++;
	}

	std::string inputToSearch;
	int validCode;
	std::cout << "\nEnter a student's code to search\n";
	while(true)
	{
		std::getline(std::cin, inputToSearch);
		if(isValidInt(inputToSearch))
		{
			validCode = std::stoi(inputToSearch);
			break;
		}
		std::cout << "Invalid code. Try again:\n";
	}

	int l = 0;
	int r = arrayLength - 1;
	bool found = false;
	int m;
	while(l <= r)
	{
		m = l + (r - l) / 2;

		if(array[m] < validCode)
		{
			l = m + 1;
		}else if(array[m] > validCode)
		{
			r = m - 1;
		}else
		{
			found = true;
			break;
		}
	}

	if(found)
	{
		std::cout << "\nMatch found:\tEntry number "
				  << m + 1 << "\n\n";
		studentFile.clear();
		studentFile.seekg(m * sizeof(Student), std::ios::beg);
		studentFile.read((char*)this, sizeof(*this));
		std::cout << "Name: " << name << " " << lastNameA << " "
	              << lastNameB << '\n'
	              << "Code: " << uniqueCode << '\n'
	              << "Carrer: " << career << '\n'
	              << "Average grade: " << grade << '\n'
	              << "-----------------------------------------\n";

	}else
	{
		std::cout << "\nNo match found!\n\n";
	}

	delete[] array;
	studentFile.close();
}

void Student::searchCareer(int entries)
{
	std::ifstream studentFile("students.txt", std::ios::in | std::ios::binary);

/*
	if(!studentFile)
	{
		std::cout << "\nThere's no records here!\n\n";
		studentFile.close();
		return;
	}
*/

	if(entries == 0)
	{
		std::cout << "\nThere's no record here!\n\n";
		studentFile.close();
		return;
	}

	std::cout << "\nEnter a career to search:\n";
	char searchByCareer[15];
	std::cin.getline(searchByCareer, 15);

	int matches = 0;
	int i = 0;
	while(studentFile.read((char*)this, sizeof(*this)))
	{
		if(strcasecmp(career, searchByCareer) == 0)
		{
			std::cout << "\nEntry " << i + 1 << '\n';

			std::cout << "Name: " << name << " " << lastNameA << " "
		              << lastNameB << '\n'
		              << "Code: " << uniqueCode << '\n'
		              << "Carrer: " << career << '\n'
		              << "Average grade: " << grade << '\n'
		              << "-----------------------------------------\n";

			matches ++;
		}
		i ++;
	}

	//int* array = new int[matches];

	std::cout << "\nA total of " << matches << " matches were found.\n\n";
	//delete[] array;
	studentFile.close();
}

//===
//	Functions
//===

int entriesCounter()
{
	std::fstream studentFile("students.txt", std::ios::in | std::ios::out | std::ios::binary);

	if (!studentFile)
	{
	    // create file if not there
	    std::ofstream create("students.txt", std::ios::binary);
	    create.close();

	    // reopen to keep working on it
	    studentFile.open("students.txt", std::ios::in | std::ios::out | std::ios::binary);
	    return 0;
	}

	studentFile.seekg(0, std::ios::end);
	std::streampos size = studentFile.tellg();

	int valueToReturn = size / sizeof(Student);

	studentFile.close();

	return valueToReturn;
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