#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "BudgetingApp.h"

using namespace std;

/********************************************************************************************
* DATE:12.12.2022
* AUTHOR:SAM TAYLOR
* FILENAME:BUDGETINGAPP
* PURPOSE:STORE ALL MAIN FUNCTIONS FOR THE BUDGETINGAPP PROGRAM AND BE RUN FROM THE MAIN FILE
********************************************************************************************/

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
	cout << "                0 = Quit                  " << endl;
	cout << "------------------------------------------" << endl;
	
	return menuChoice;
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
		if (total == NULL) {
			FillStartingInfo();
		}
		loadFile.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
	return total;
}

/*******************************************************************************************************
* Function takes the user through filling out the starting information to a file if nothing is contained
* inside one so the user may create a base balance and register a name with the file
*******************************************************************************************************/
void FillStartingInfo() {
	ofstream saveStartingInfo;
	double startingBalance = 0; // starting balance for user
	string nameOfAccount = ""; //users name that they will use to register the account
	try
	{
		saveStartingInfo.open("BudgetList.txt");

		if (!saveStartingInfo.is_open()) {
			throw runtime_error("File not open.");
		}
		cout << "Enter name you would like to register account with(full name please): ";

		getline(cin, nameOfAccount);

		cout << "Enter starting balance for account: ";

		cin >> startingBalance;

		saveStartingInfo << startingBalance << endl;
		saveStartingInfo << nameOfAccount << endl;
		saveStartingInfo.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
}

void LoadFile(vector<string>& namesOfEntries, vector<double>& entries) {
	ifstream loadData;

	double entry;// amount of money in entry

	string name; // name of entry listed is loaded
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
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
}

/*********************************************************************************
* Totals up all entries income and expenses alike and gives you your total balance
*********************************************************************************/
double GetCurrentBalance(vector<double> entries) {
	double startingBalance = GetTotal();
	double endBalance = startingBalance;
	for (int i = 0; i < entries.size(); i++) {
		endBalance += entries.at(i);
	}

	return endBalance;
}

/********************************************
* Meant to save currently loaded data to file
********************************************/
void SaveFile(vector<string> namesOfEntries, vector<double> entries) {
	double startingBalance = GetTotal();
	double endBalance = GetCurrentBalance(entries);

	ofstream saveFile;
}

/*****************************************************************************************
* Adds entry to the end of the list updating the two vectors to be later saved to the file
*****************************************************************************************/
void AddEntryToList(vector<string>& namesOfEntries, vector<double>& entries) {

}

//