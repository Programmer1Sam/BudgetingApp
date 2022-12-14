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
		menuChoice = BudgetingMainMenu();

		switch (menuChoice) {
		default:
			break;
		case 1:
			WipeAllData();
			break;
		case 2:
			AddEntryToList(namesOfEntries, amountOfEntry);
			break;
		case 4:
			FillStartingInfo();
			break;
		}

	}

	return 0;
}