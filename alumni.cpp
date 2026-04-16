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
	void orderRecord(int&);
	void binarySearch(int);
	void searchCareer(int);

	void modify(int, bool&);
	void erase(int, int&);
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
	int indexChose;

	Student oneStudent;

	int entries = entriesCounter();
	//oneStudent.show();

	//	Menu loop
	do
	{
		std::cout << "PICK AN OPTION:\n"
				  << "1. RECORD\n2. SHOW\n"
				  << "3. SEARCH CODE\n4. SEARCH CAREER\n"
				  << "5. EDIT\n6. DELETE\n7. EXIT\nOPTION:\t";
		if(!(std::cin >> cursorPosition))
		{
		    std::cin.clear(); // reset error flags
		    std::cin.ignore(1000, '\n'); // discard bad input
		    std::cout << "\nInvalid input. Enter a number.\n\n";
		}else if(cursorPosition < 1 || cursorPosition > 7)
		{
			std::cout << "\nSelection out of range."
					  << " Enter a number from 1 to 7.\n\n";
		}
		std::cin.ignore();
		bool editedCode = false;
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
		case 5:
			if(entries == 0)
			{
				std::cout << "\nNo entries found.\n\n";
				break;
			}
			std::cout << "\nWhich entry will you edit? (pick 0 to cancel):\t";
			if(!(std::cin >> indexChose))
			{
		  		std::cin.clear(); // reset error flags
		  		std::cin.ignore(1000, '\n'); // discard bad input
		 		std::cout << "\nInvalid input. Enter a number.\n\n";
			}else if(indexChose == 0)
			{
				std::cout << "\nCancelled\n\n";
				break;
			}else if(indexChose < 1 || indexChose > entries)
			{
				std::cout << "\nSelection out of range."
						  << " Enter a number from 1 to " << entries << ".\n\n";
				break;
			}
			std::cin.ignore();
			oneStudent.modify(indexChose, editedCode);
			if(editedCode)
			{
				Student tmpStudent = oneStudent;
				oneStudent.erase(indexChose, entries);
				tmpStudent.orderRecord(entries);
				std::cout << "\nEntry location was changed due to code modification.\n\n";
			}
			break;
		case 6:
			if(entries == 0)
			{
				std::cout << "\nNo entries found.\n\n";
				break;
			}
			std::cout << "\nWhich entry will you delete? (pick 0 to cancel):\t";
			if(!(std::cin >> indexChose))
			{
		  		std::cin.clear(); // reset error flags
		  		std::cin.ignore(1000, '\n'); // discard bad input
		 		std::cout << "\nInvalid input. Enter a number.\n\n";
			}else if(indexChose == 0)
			{
				std::cout << "\nCancelled\n\n";
				break;
			}else if(indexChose < 1 || indexChose > entries)
			{
				std::cout << "\nSelection out of range."
						  << " Enter a number from 1 to " << entries << ".\n\n";
				break;
			}
			std::cin.ignore();
			oneStudent.erase(indexChose, entries);
			std::cout << "\nEntry " << indexChose << " erased correctly\n\n";
			break;
		}

	}while(cursorPosition != 7);

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
void Student::orderRecord(int& entries)
{
	std::fstream studentFile("students.txt", std::ios::in | std::ios::out | std::ios::binary);

	//std::cout << "This file has " << count << " entries.\n";

	if(entries == 0)	//	File is empty? Then continue and write.
	{
		studentFile.write((char*) this, sizeof(*this));
		studentFile.close();
		entries ++;
		return;
	}

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

	int* allCodes = new int[entries];
	int p = 0;

	while(studentFile.read((char*)this, sizeof(*this)))
	{
		allCodes[p] = uniqueCode;
		p ++;
	}
	studentFile.clear();

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
	entries ++;

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
	if(entries == 0)
	{
		std::cout << "\nThere's no records here!\n\n";
		return;
	}

	std::ifstream studentFile("students.txt", std::ios::in | std::ios::binary);

	int* array = new int[entries];
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
	int r = entries - 1;
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

	//	Editing
void Student::modify(int entry,bool& editedCode)
{
	int pickModify;

	std::fstream studentFile("students.txt", std::ios::in | std::ios::out | std::ios::binary);
	studentFile.seekg((entry - 1) * sizeof(Student), std::ios::beg);
	studentFile.read((char*)this, sizeof(*this));
	std::cout << "1. Name: " << name << '\n'
			  << "2. Paternal surname: " << lastNameA << '\n'
	          << "3. Paternal surname: " << lastNameB << '\n'
	          << "4. Code: " << uniqueCode << '\n'
	          << "5. Carrer: " << career << '\n'
	          << "6. Average grade: " << grade << '\n'
	          << "-----------------------------------------\n";
	std::cout << "\nWhat data will you modify? (pick 0 to cancel):\t";

	if(!(std::cin >> pickModify))
	{
	    std::cin.clear(); // reset error flags
	    std::cin.ignore(1000, '\n'); // discard bad input
	    std::cout << "\nInvalid input. Enter a number.\n\n";
	}else if(pickModify == 0)
	{
		std::cout << "\nCancelled\n\n";
		studentFile.close();
		return;
	}else if(pickModify < 1 || pickModify > 6)
	{
		std::cout << "\nSelection out of range."
				  << " Enter a number from 1 to 6.\n\n";
		studentFile.close();
		return;
	}
	std::cin.ignore();

	std::string input;
	switch(pickModify)
	{
	case 1:
		std::cout << "\nEnter student's new name:\n";
		std::cin.getline(name, 15);
		std::cout << "\nNew name saved correctly\n\n";
		break;
	case 2:
		std::cout << "\nEnter new paternal surname:\n";
		std::cin.getline(lastNameA, 15);
		std::cout << "\nNew paternal surname saved correctly\n\n";
		break;
	case 3:
		std::cout << "\nEnter new maternal surname:\n";
		std::cin.getline(lastNameB, 15);
		std::cout << "\nNew maternal surname saved correctly\n\n";
		break;
	case 4:
		std::cout << "\nEnter student's new code:\n";
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
		std::cout << "\nNew studen's code saved correctly\n\n";
		editedCode = true;
		break;
	case 5:
		std::cout << "\nEnter student's new career:\n";
		std::cin.getline(career, 15);
		std::cout << "\nNew career saved correctly\n\n";
		break;
	case 6:
		std::cout << "\nEnter new student's average grade:\n";
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
		std::cout << "\nNew average grade saved correctly\n\n";
		break;
	}

	studentFile.seekg((entry - 1) * sizeof(Student), std::ios::beg);
	studentFile.clear();
	studentFile.write((char*) this, sizeof(*this));
	studentFile.close();
}
	//	Erase entry
void Student::erase(int entry, int& entries)
{
	std::ifstream originalFile("students.txt", std::ios::in | std::ios::binary);
	std::ofstream tmpFile("tmp.txt", std::ios::out | std::ios::binary);

	int counter = 1;
	while(originalFile.read((char*)this, sizeof(*this)))
	{
		if(counter != entry)
		{
			tmpFile.write((char*)this, sizeof(*this));
		}
		counter ++;
	}
	originalFile.close();
	tmpFile.close();

	std::remove("students.txt");
	std::rename("tmp.txt", "students.txt");

	entries --;
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