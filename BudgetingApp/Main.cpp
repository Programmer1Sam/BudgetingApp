#include <string>
#include "BudgetingApp.h"

using namespace std;

int main() {
	double total = GetTotal();

	vector<string> namesOfEntries;
	vector<double> amountOfEntry;

	BudgetingMainMenu();
	return 0;
}