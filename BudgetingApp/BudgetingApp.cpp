#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "BudgetingApp.h"

using namespace std;

/*************************************************************
* Menu from which all main budgeting processes can be accessed
*************************************************************/
int BudgetingMainMenu() {
	int menuChoice = 0;

	cout << "------------------------------------------" << endl;
	cout << "           1 = Load budget data           " << endl;
	cout << "           2 = Save budget data           " << endl;
	cout << "        3 = Add entry to expenses         " << endl;
	cout << "4 = calculate new spending limit for month" << endl;
	cout << "5 = Create new budgetfile if non existent " << endl;
	cout << "                0 = Quit                  " << endl;
	cout << "------------------------------------------" << endl;
	
	menuChoice = ValidateNumericInput();

	return menuChoice;
}

/***********************************************************
* function checks to make sure inputted character is numeric
***********************************************************/
int ValidateNumericInput() {
	int choice = 0;
	
	cin >> choice;

	if (cin.fail()) {
		cin.clear();

		cin >> choice;
	}

	return choice;
}

/****************************************************************************
* Function returns the first line in the file which will be the current total
****************************************************************************/
double GetTotal() {
	ifstream loadFile;
	double total = 0;
	try {
		loadFile.open("BudgetList.txt");
		
		if (!loadFile.is_open()) {
			throw runtime_error("File not open.");
		}
		loadFile >> total;
		//if (total == NULL) {
			//FillStartingInfo();
		//}
		loadFile.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
	return total;
}

string GetAccountName() {
	ifstream loadFile;

	string garbageInput = "";
	string accountName = "";
	try {
		loadFile.open("BudgetList.txt");

		if (!loadFile.is_open()) {
			throw runtime_error("File not open.");
		}
		getline(loadFile, garbageInput);

		loadFile.clear();

		getline(loadFile, accountName);
		loadFile.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
	return accountName;
}

/*******************************************************************************************************
* Function takes the user through filling out the starting information to a file if nothing is contained
* inside one so the user may create a base balance and register a name with the file
*******************************************************************************************************/
void FillStartingInfo() {
	WipeAllData();

	ofstream saveStartingInfo;
	double startingBalance = 0; // starting balance for user
	string nameOfAccount = ""; //users name that they will use to register the account
	try
	{
		saveStartingInfo.open("BudgetList.txt");

		if (!saveStartingInfo.is_open()) {
			throw runtime_error("File not open.");
		}
		
		cout << "Enter starting balance for account: ";

		cin >> startingBalance;

		cout << "Enter name you would like to register account with(full name please): ";
		cin.clear();
		cin.ignore();

		getline(cin, nameOfAccount);


		saveStartingInfo << startingBalance << endl;
		saveStartingInfo << nameOfAccount << endl;
		saveStartingInfo.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
}
 
/*********************
* Loads data from file
*********************/
void LoadFile(vector<string>& namesOfEntries, vector<double>& entries) {
	ifstream loadData;

	double entry;// amount of money in entry

	string name = ""; // name of entry
	string garbageData = ""; // meant to be used on the lines not needed to be loaded to skip them
	
	try {
		loadData.open("BudgetList.txt");
		
		if (!loadData.is_open()) {
			throw runtime_error("File not open.");
		}

		getline(cin, garbageData);
		getline(cin, garbageData);
		

		
		while (loadData >> name >> entry) {
			namesOfEntries.push_back(name);
			entries.push_back(entry);
		}
		getline(cin, garbageData);
		getline(cin, garbageData);

		loadData.close();

	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
}

/********************************
* Saves data from vectors to file
********************************/
void SaveFile(vector<string> namesOfEntries, vector<double> entries) {
	ofstream saveDataToFile;
	
	double beginningTotal = GetTotal();

	string accountName = GetAccountName();
	try {
		saveDataToFile.open("BudgetList.txt");

		if (!saveDataToFile.is_open()) {
			throw runtime_error("File unable to be opened.");
		}

		saveDataToFile << beginningTotal << endl;
		saveDataToFile << accountName << endl;
		saveDataToFile << ResizableBorder(accountName.size()) << endl;

		for (int i = 0; i < namesOfEntries.size() && i < entries.size(); i++) {
			saveDataToFile << namesOfEntries.at(i) << " " << entries.at(i) << endl;
		}

		saveDataToFile << ResizableBorder(accountName.size()) << endl;
		saveDataToFile << GetCurrentBalance(entries) << endl;
		saveDataToFile.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what();
	}
}

/*****************************************************************************
* Function allowing for a border that may be resized to be able to be returned
*****************************************************************************/
string ResizableBorder(int size) {
	string border = "";

	for (int i = 0; i < size; i++) {
		border += "-";
	}

	return border;
}

void WipeAllData() {
	ofstream dataRemoval;

	try {
		dataRemoval.open("BudgetList.txt");
		
		if (!dataRemoval.is_open()) {
			throw runtime_error("File unable to be opened.");
		}
		dataRemoval << "";
		dataRemoval.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
}

/*****************************************************************************************
* Adds entry to the end of the list updating the two vectors to be later saved to the file
*****************************************************************************************/
void AddEntryToList(vector<string>& namesOfEntries, vector<double>& entries) {
	string entryName = "";
	double amountInEntry = 0;

	cout << "Enter the name of the transaction: ";

	cin >> entryName;

	cout << "Enter the amount of transaction if income use positive if spending use -: ";

	cin >> amountInEntry;

	namesOfEntries.push_back(entryName);
	entries.push_back(amountInEntry);
}

/***************************************************************************
* calculates the current amount of money in the users account and returns it
***************************************************************************/
double GetCurrentBalance(vector<double> entries) {
	double startingBalance = GetTotal();
	double currentBalance = startingBalance;

	for (int i = 0; i < entries.size(); i++) {
		currentBalance += entries.at(i);
	}

	return currentBalance;
}