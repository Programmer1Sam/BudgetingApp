#include <string>
#include "BudgetingApp.h"

using namespace std;

int main() {
	double startingBalance = GetTotal();

	int menuChoice = 0;

	vector<string> namesOfEntries;
	vector<double> amountOfEntry;

	menuChoice = BudgetingMainMenu();

	switch (menuChoice) {
	default:
		break;
	case 1:
		LoadFile(namesOfEntries, amountOfEntry);
		break;
	case 2:
		SaveFile(namesOfEntries, amountOfEntry);
	}

	return 0;
}