#include <string>
#include "BudgetingApp.h"

using namespace std;

int main() {
	double startingBalance = GetTotal();

	int menuChoice = -1;

	vector<string> namesOfEntries;
	vector<double> amountOfEntry;


	while (menuChoice != 0) {
		menuChoice = BudgetingMainMenu();

		switch (menuChoice) {
		default:
			break;
		case 1:
			LoadFile(namesOfEntries, amountOfEntry);
			break;
		case 2:
			SaveFile(namesOfEntries, amountOfEntry);
			break;
		case 3:
			AddEntryToList(namesOfEntries, amountOfEntry);
			break;
		case 5:
			FillStartingInfo();
			break;
		}
	}

	return 0;
}