#include <string>

#include "BudgetingApp.h"

/*******************************************
* DATE:12.18.2022
* AUTHOR: SAM TAYLOR
* FILE NAME: MAIN
* PURPOSE: RUN ALL CODE FROM HERE AND SERVES
* AS THE STARTING POINT BEFORE THE PROGRAM 
* BRANCHES OFF INTO THE FUNCTIONS IN THE 
* BUDGETING APP FILE ONCE IT STARTS
*******************************************/
using namespace std;

int main() {
	double startingBalance = GetTotal(); // gets the starting balance for the budgetfile

	int menuChoice = -1; // menu choice starts at -1 so that it runs the while loop at least once

	vector<string> namesOfEntries; // vector used for entry names
	vector<double> amountOfEntry; // vector used for amounts in transactions

	LoadBudgetFile(namesOfEntries, amountOfEntry);
	SaveBudgetFile(namesOfEntries, amountOfEntry); // necessary here for balance to be imported to the income data file

	while (menuChoice != 0) {
		menuChoice = MainMenu();

		switch (menuChoice) {
		default:
			break;
		case 1:
			BudgetingMenu(namesOfEntries, amountOfEntry);
			break;
		case 2:
			IncomeMenu();
			break;
		case 3 :
			SettingsMenu();
			break;
		}

	}

	CreateIncomeDataFile(); // makes sure program ends with updated income data file

	return 0;
}