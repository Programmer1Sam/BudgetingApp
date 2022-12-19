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
	double startingBalance = GetTotal();

	int menuChoice = -1;

	vector<string> namesOfEntries;
	vector<double> amountOfEntry;

	LoadBudgetFile(namesOfEntries, amountOfEntry);

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

	return 0;
}