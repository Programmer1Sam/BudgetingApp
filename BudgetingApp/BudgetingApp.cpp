#include <iostream>
#include <fstream>
#include <stdexcept>

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
			
		}
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
	return total;
}

void FillStartingInfo() {

}