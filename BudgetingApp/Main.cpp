#include <string>
#include "BudgetingApp.h"

using namespace std;

int main() {
	double startingBalance = GetTotal();

	int menuChoice = -1;

	vector<string> namesOfEntries;
	vector<double> amountOfEntry;

	LoadFile(namesOfEntries, amountOfEntry);

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