/* -----------------------------------------------------------------------------

FILE:           proj2.cpp
DESCRIPTION:    Project 2 for Fall 2019 CS 202-1001 at UNR; Assists users
					in renting a car
COMPILER:       MinGW C++ compiler
NOTES:          

MODIFICATION HISTORY:
Author				Date			Version
---------------		----------		--------------
Version 1			YYYY-MM-DD		x.x Description
Nick Learner		2019-09-05		1.0	Created program
Nick Learner		2019-09-07		1.1	Created func protos for required funcs
Nick Learner		2019-09-08		1.2	Created UserMenu() and some functions
Nick Learner		2019-09-09		1.3	Added case 3 to UserMenu()
Nick Learner		2019-09-11		1.4	Added SelectionSort(), more functions
----------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>

using namespace std;

// Global variables
const int NUM_OF_CARS = 5;
const int MAX_CHAR_ARRAY_LENGTH = 10;

struct RentalCar
{
	int year;
	char make[MAX_CHAR_ARRAY_LENGTH];
	char model[MAX_CHAR_ARRAY_LENGTH];
	float price;
	bool available;
};

// Function prototypes
size_t myStringLength(const char * str);
int myStringCompare(const char * str1, const char * str2);
char * myStringCopy(char * destination, const char * source);
char * myStringCat(char * destination, const char * source);
void UserMenu();
void DisplayUserMenu(ostream&);
void UserInputFileName(char[], char[], int);
bool OpenInputFile(char[], fstream&);
void FileInput(RentalCar[], int[], fstream&);
void PrintCarData(RentalCar[], int[]);
bool OpenOutputFile(char[], fstream&);
void PrintCarDataToFile(RentalCar[], int[], ostream&);
void SelectionSort(RentalCar[], int[]);
void FifthMenuOption(RentalCar[], int[]);
void PrintAvailableCarData(RentalCar[], int[], int);
void SixthMenuOption(RentalCar[], int[]);
void Error();

int main()
{
	UserMenu();
	
	return 0;
}


/* -----------------------------------------------------------------------------
FUNCTION:          UserMenu()
DESCRIPTION:       Displays a menu the user picks an option from
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void UserMenu()
{
	char inputfilename[32] = {' ', ' '};
	char outputfilename[32] = {' ', ' '};
	char inputfiletype[32] = "Input";
	char outputfiletype[32] = "Output";
	fstream inputfile;
	fstream outputfile;
	
	bool hasfilebeenopened = false;
	bool continuemenu = true;
	int choice;
	
	RentalCar cardata[NUM_OF_CARS];
	int order[NUM_OF_CARS];
	
	while (continuemenu)
	{
		DisplayUserMenu(cout);
		
		cin >> choice;
		
		switch (choice)
		{
		case 1:
			UserInputFileName(inputfiletype, inputfilename, 32);
			hasfilebeenopened = OpenInputFile(inputfilename, inputfile);
			if (hasfilebeenopened)
			{
				cout << "File " << inputfilename << " has been opened." << "\n";
				FileInput(cardata, order, inputfile);
				cout << "Car data has been inputted." << "\n";
				inputfile.close();
				cout << "File " << inputfilename << " has been closed." << "\n\n";
			}else
			  Error();
			break;
		case 2:
			if (!hasfilebeenopened)
			{
				cout << endl;
				cout << "Data has not yet been inputted. Please choose Option 1).\n\n";
			}else
			{
				cout << "\n\n";
				PrintCarData(cardata, order);
				cout << "\n\n";
			}
			break;
		case 3:
			UserInputFileName(outputfiletype, outputfilename, 32);
			if (OpenOutputFile(outputfilename, outputfile))
			{
				cout << "File " << outputfilename << " has been opened." << "\n";
				PrintCarDataToFile(cardata, order, outputfile);
				cout << "Data has been entered into the file." << "\n";
				outputfile.close();
				cout << "File " << outputfilename << " has been closed." << "\n\n";
			}else
			        Error();
			break;
		case 4:
			SelectionSort(cardata, order);
			cout << endl;
			cout << "The list has been sorted by ascending price." << "\n\n";
			break;
		case 5:
			FifthMenuOption(cardata, order);
			break;
		case 6:
			SixthMenuOption(cardata, order);
			break;
		case 7:
			cout << endl;
			cout << "Thank you for using Let's Rent a Car" << "\n\n";
			continuemenu = false;
			break;
		default:
			cout << endl;
			Error();
			break;
		}
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          DisplayUserMenu()
DESCRIPTION:       Displays a menu the user picks an option from
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void DisplayUserMenu(ostream& out)
{
	// Menu prompt as per Proj2 instructions
	out << "Let's Rent a Car" << endl;
	out << "1) Input the name of the rental car datafile" << endl;
	out << "2) Print all rental car data to console" << endl;
	out << "3) Print all rental car data to output file" << endl;
	out << "4) Sort the rental cars by ascending price" << endl;
	out << "5) Input the number of days the rental car is needed" << endl;
	out << "6) Select car for rental" << endl;
	out << "7) Quit program" << endl;
	
	out << "Enter your choice [ 1 2 3 4 5 6 7 ]: ";
}


/* -----------------------------------------------------------------------------
FUNCTION:          UserInputFileName()
DESCRIPTION:       Gets a filename from user
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------*/

void UserInputFileName(char type[], char filename[], int length)
{
	cout << endl;
	cout << type << " filename: ";
	
	cin >> filename;
	cin.clear();
	cin.ignore(1000, '\n');
	
	// For-loop to switch every space with an underscore
	for (int i = 0; i < length; i++)
	{
		if (filename[i] == ' ')
		{
			filename[i] = '_';
		}else;
	}
	
	cout << endl;
}


/* -----------------------------------------------------------------------------
FUNCTION:          OpenInputFile()
DESCRIPTION:       Opens a file from which the names are inputted
RETURNS:           bool (true if file is opened, false if file is not found)
NOTES:             
------------------------------------------------------------------------------*/

bool OpenInputFile(char filename[], fstream& inputfile)
{
	int count = 0;
	
	inputfile.open(filename, ios::in);
	if (inputfile.fail())
	{
		cout << "File " << filename << " failed to open." << "\n\n";
		return false;
	}
	else
		return true;
}


/* -----------------------------------------------------------------------------
FUNCTION:          FileInput()
DESCRIPTION:       Inputs the car data into an array of RentalCar structs
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------*/

void FileInput(RentalCar cardata[], int order[], fstream& inputfile)
{
	for (int i = 0; i < NUM_OF_CARS; i++)
	{
		order[i] = i;
		
		inputfile >> cardata[i].year;
		
		inputfile >> cardata[i].make;
		
		inputfile >> cardata[i].model;
		
		inputfile >> cardata[i].price;
		
		inputfile >> cardata[i].available;
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          PrintCarData()
DESCRIPTION:       Prints the info for each car to the console
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void PrintCarData(RentalCar cardata[], int order[])
{
	for (int i = 0; i < NUM_OF_CARS; i++)
	{
		cout << '[' << order[i] << "]: " << cardata[i].year << ' '
			<< cardata[i].make << ' ' << cardata[i].model << ", $"
			<< cardata[i].price << " per day. This option is ";
		if (cardata[i].available)
		{
			cout << "available.";
		}else
		{
			cout << "not available.";
		}
		
		cout << endl;
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          OpenOutputFile()
DESCRIPTION:       Opens a file to output data into
RETURNS:           bool
NOTES:             
------------------------------------------------------------------------------- */
 
bool OpenOutputFile(char filename[], fstream& outputfile)
{
	outputfile.open(filename, ios::out);
	if (outputfile.fail())
	{
		cout << "File " << filename << " failed to open." << "\n\n";
		return false;
	}
	else
		return true;
}


/* -----------------------------------------------------------------------------
FUNCTION:          PrintCarDataToFile()
DESCRIPTION:       Prints the info for each car to a file
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void PrintCarDataToFile(RentalCar cardata[], int order[], ostream& out)
{
	for (int i = 0; i < NUM_OF_CARS; i++)
	{
		out << cardata[i].year << ' '
			<< cardata[i].make << ' ' << cardata[i].model << ' '
			<< cardata[i].price << ' ' << boolalpha << cardata[i].available;
		out << endl;
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          SelectionSort()
DESCRIPTION:       Sorts an array of structs of cars from cheapest to least cheap
RETURNS:		   void
NOTES:             This is a heavily edited version of an original function from
					the Starting Out With C++: From Control Structures through
					Objects textbook by Tony Gaddis (8th Ed.)
------------------------------------------------------------------------------- */

void SelectionSort(RentalCar cardata[], int order[])
{
	int startscan, minindex, temporder, tempyear;
	double minvalue;
	char tempname[MAX_CHAR_ARRAY_LENGTH];
	bool tempavailable;
	
	for (startscan = 0; startscan < (NUM_OF_CARS-1); startscan++)
	{
		minindex = startscan;
		minvalue = cardata[startscan].price;
		
		for (int index = startscan + 1; index < NUM_OF_CARS; index++)
		{
			if (cardata[index].price < minvalue)
			{
				minvalue = cardata[index].price;
				minindex = index;
			}else;
		}
		
		cardata[minindex].price = cardata[startscan].price;
		cardata[startscan].price = minvalue;
		
		temporder = order[minindex];
		order[minindex] = order[startscan];
		order[startscan] = temporder;
		
		tempavailable = cardata[minindex].available;
		cardata[minindex].available = cardata[startscan].available;
		cardata[startscan].available = tempavailable;
		
		tempyear = cardata[minindex].year;
		cardata[minindex].year = cardata[startscan].year;
		cardata[startscan].year = tempyear;
		
		for (int i = 0; i < MAX_CHAR_ARRAY_LENGTH; i++)
		{
			tempname[i] = cardata[minindex].make[i];
			cardata[minindex].make[i] = cardata[startscan].make[i];
			cardata[startscan].make[i] = tempname[i];
			
			tempname[i] = cardata[minindex].model[i];
			cardata[minindex].model[i] = cardata[startscan].model[i];
			cardata[startscan].model[i] = tempname[i];
		}
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          FifthMenuOption()
DESCRIPTION:       Asks user for number of days the car is needed, etc.
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void FifthMenuOption(RentalCar cardata[], int order[])
{
	int days;
	
	cout << endl;
	cout << "Enter many days you would like to rent a car: ";
	cin >> days;
	
	SelectionSort(cardata, order);
	
	PrintAvailableCarData(cardata, order, days);
}


/* -----------------------------------------------------------------------------
FUNCTION:          PrintAvailableCarData()
DESCRIPTION:       Prints the data for available cars
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void PrintAvailableCarData(RentalCar cardata[], int order[], int days)
{
	for (int i = 0; i < NUM_OF_CARS; i++)
	{
		if (cardata[i].available)
		{
			cout << '[' << order[i] << "]: " << cardata[i].year << ' '
				<< cardata[i].make << ' ' << cardata[i].model << ", $"
				<< (cardata[i].price * days) << " for " << days << " days.";
		}else;
		
		cout << endl;
	}
	
	cout << endl;
}


/* -----------------------------------------------------------------------------
FUNCTION:          SixthMenuOption()
DESCRIPTION:       Asks user which car they want
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void SixthMenuOption(RentalCar cardata[], int order[])
{
	int choice;
	int index = 0;
	int days;
	
	cout << endl;
	cout << "Enter the index number of the car you would like to rent: ";
	cin >> choice;
	cout << endl;
	
	for (int i = 0; i < NUM_OF_CARS; i++)
	{
		if (order[i]==choice)
		{
			index = i;
		}else;
	}
	
	if (cardata[index].available)
	{
		cout << endl;
		cout << "Enter many days you would like to rent the car: ";
		cin >> days;
		cout << endl;
		
		cout << "You have succesfully rented the " << cardata[index].year
			<< "\n" << cardata[index].make << " " << cardata[index].model
			<< " for " << days << " days at a total cost of $"
			<< (cardata[index].price * days) << ". Thank you!";
		cout << "\n\n";
		
		cardata[index].available = false;
	}else
	{
		Error();
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          Error()
DESCRIPTION:       Gives error message
RETURNS:           void
NOTES:             
------------------------------------------------------------------------------- */

void Error()
{
	cout << "Incorrect input! Please enter a correct input." << "\n\n";
}
