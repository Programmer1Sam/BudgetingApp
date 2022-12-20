 #include <iostream> // used for basic input output operations
#include <fstream> // used for basic file operations
#include <stdexcept> // for handling exceptions with files
#include <string> // used for string operations such as getline
#include <iomanip> // allows for input output manipulation

#include "BudgetingApp.h" // header file containing all function prototypes

/*******************************************************************
* DATE:12.14.2022
* AUTHOR:SAM TAYLOR
* FILENAME:BUDGETINGAPP
* PURPOSE:HOLD ALL FUNCTIONS NEEDED TO RUN THE BUDGETING APP PROGRAM
*******************************************************************/

using namespace std; // declaration of namespace

//global variables
double globalCurrentBalance; // used to pull currentBalance from the budgetlist to IncomeData

/***********************************************************
* Prompt for an enter key to be pressed after all operations
***********************************************************/
void EnterKeyPrompt() {
	string garbageInput = ""; // input used as a filler without actually needing to grab anything

	cout << "|-----------------------------------------|" << endl;
	cout << "| Please press the enter key to continue. |" << endl;
	cout << "|-----------------------------------------|" << endl;
	getline(cin, garbageInput); // gets the line when user presses enter key
	cin.clear();
	cin.ignore();

}
/*************************************************************
* Menu from which all main budgeting processes can be accessed
*************************************************************/
int MainMenu() {
	int menuChoice = 0; // used for choosing which operation to be run

	system("CLS"); // clears console screen

	cout << "|------------------------------------------|" << endl;
	cout << "|         1 = Budgeting Operations         |" << endl;
	cout << "|          2 = Income Operations           |" << endl;
	cout << "|               3 = Settings               |" << endl;
	cout << "|                0 = Quit                  |" << endl;
	cout << "|------------------------------------------|" << endl;
	cout << endl << "Please select a choice by entering the number: ";
	menuChoice = ValidateNumericInput(); // checks to make sure the chosen choice is numeric

	return menuChoice; // returns menu choice for operations to be chosen 
}

/******************************
* Header for the budgeting menu
******************************/
void BudgetingHeader() {
	system("CLS");

	cout << "|------------------------------------------|" << endl;
	cout << "|       1 = Save current budget data       |" << endl;
	cout << "|       2 = Add entry to Budget data       |" << endl;
	cout << "|            3 = Delete all data           |" << endl;
	cout << "|        0 =  Return to main menu          |" << endl;
	cout << "|------------------------------------------|" << endl;
	cout << endl << "Please select a choice by entering the number: ";
}

/*************************************************
* Menu for budgeting operations in the application
*************************************************/
void BudgetingMenu(vector<string>& namesOfEntries, vector<double>& entries) {
	int menuChoice = -1;
	
	while (menuChoice != 0) {
		BudgetingHeader();

		menuChoice = ValidateNumericInput();

		switch (menuChoice)
		{
		default:
			break;
		case 0:
			break;
		case 1:
			SaveBudgetFile(namesOfEntries, entries);
			EnterKeyPrompt();
			break;
		case 2:
			AddEntryToList(namesOfEntries, entries);
			EnterKeyPrompt();
			break;
		case 3:
			WipeAllData("BudgetList.txt");
			EnterKeyPrompt();
			break;
		}
	}
	


}

/***************************
* Header for the income menu
***************************/
void IncomeHeader() {
	system("CLS");

	cout << "|-----------------------------------------------------|" << endl;
	cout << "|           1 = Create/update Income Data file        |" << endl;
	cout << "|          2 = Load previous Income Data file         |" << endl;
	cout << "|              3 = Save Income Data file              |" << endl;
	cout << "|4 = Set percentage of money to be spent for the month|" << endl;
	cout << "|               0 = Return to main menu               |" << endl;
	cout << "|-----------------------------------------------------|" << endl;
	cout << endl << "Please select a choice by entering the number: ";
}

/**********************************************
* Menu for income operations in the application
**********************************************/
void IncomeMenu() {
	int menuChoice = -1;

	while (menuChoice != 0) {
		IncomeHeader();

		menuChoice = ValidateNumericInput();

		switch (menuChoice)
		{
		default:
			break;
		case 1:
			CreateIncomeDataFile();
			EnterKeyPrompt();
			break;
		case 2:
			EnterKeyPrompt();
			break;
		case 3: 
			EnterKeyPrompt();
			break;
		}
	}
}

/***************************************
* Creates base file for income data file
***************************************/
void CreateIncomeDataFile() {
	ofstream cif; // cif stands for create income file
	
	string accountName = GetAccountName(); // pulls account name from budget file since the two files are likely under the same name

	double currentIncome = GetUserIncome(); // Income of user
	double hoursPerWeek = GetHoursWorkedPerWeek(); // hours user works per week
	double currentTotalBalance = globalCurrentBalance; // gets current balance that is at the bottom of the budgetlist file
	try {
		cif.open("IncomeDataFile.txt");
	
		if (!cif.is_open()) {
			throw runtime_error("File not able to be opened!");
		}

		cif << "User: " << accountName << endl;
		cif << "Balance: " << currentTotalBalance << endl;
		cif << ResizableBorder(20) << endl;
		cif << "Income: " << currentIncome << endl;
		cif << "Hours working per week: " << hoursPerWeek << endl;

		cif.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
}

/**********************************************************************************************
* Function checks to make sure the user has an amount of hours filled out each week and if that 
* amount is zero the user will be prompted to enter an amount of hours worked each week
**********************************************************************************************/
double GetHoursWorkedPerWeek() {
	ifstream ruh; // stands for read user hours

	string garbageInput = ""; // used to pass empty lines

	double userHours = 0; // hours worked by user

	try
	{
		ruh.open("IncomeDataFile.txt");

		if (!ruh.is_open())
		{
			throw runtime_error("File unable to be accessed.");
		}

		getline(ruh, garbageInput);
		getline(ruh, garbageInput);
		getline(ruh, garbageInput);

		ruh >> garbageInput >> garbageInput >> garbageInput >> garbageInput >> userHours;

		ruh.close();

		if (userHours <= 0)
		{
			cout << "You have not entered an amount of hours worked please enter it here: ";

			cin >> userHours;
		}
		return userHours;
	}
	catch (runtime_error& excpt)
	{
		cout << "Error: " << excpt.what() << endl;
	}

	return 0;
}

/*********************************************************************************
* Returns the income the user has and adds the income if it does not already exist
*********************************************************************************/
double GetUserIncome() 
{
	ifstream rui; // stands for read user income, used to read the file

	string garbageInput = ""; // used to get rid of the unnecessary lines for the check

	double userIncome = 0; // stores income data
	if (IncomeInfoPresent()) 
	{
		try
		{
			rui.open("IncomeDataFile.txt");

			if (!rui.is_open()) 
			{
				throw runtime_error("File unable to be accessed.");
			}

			getline(rui, garbageInput);
			getline(rui, garbageInput);
			getline(rui, garbageInput);

			rui >> garbageInput >> userIncome;

			rui.close();

			if (userIncome <= 0)
			{
				cout << "You have not entered an income amount please enter it here: ";

				cin >> userIncome;
			}
			return userIncome;
		}
		catch (runtime_error& excpt)
		{
			cout << "Error: " << excpt.what() << endl;
		}
	}

	else {
		return 0;
	}
}

/*****************************
* Header for the settings menu
*****************************/
void SettingsHeader() {
	system("CLS");
}

/*************************************
* Menu for settings in the application
*************************************/
void SettingsMenu() {

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

/*******************************************************************************************
* Finds and returns the holder of the account's name, located at the second line of the file
*******************************************************************************************/
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
	WipeAllData("BudgetList.txt");

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
void LoadBudgetFile(vector<string>& namesOfEntries, vector<double>& entries) {
	ifstream loadData;

	double entry = 0;// amount of money in entry

	string name = ""; // name of entry
	string garbageData = ""; // meant to be used on the lines not needed to be loaded to skip them


	system("CLS");

	try {
		loadData.open("BudgetList.txt");
		
		if (!loadData.is_open()) {
			throw runtime_error("File not open.");
		}

		getline(loadData, garbageData);
		getline(loadData, garbageData);
		getline(loadData, garbageData);

		while (loadData >> entry >> name) {
			namesOfEntries.push_back(name);
			entries.push_back(entry);
		}

		loadData.close();

		if (entries.size() == 0) {
			cout << "|------------------|" << endl;
			cout << "|No data to load...|" << endl;
			cout << "|------------------|" << endl;
		}

		else {
			cout << "|-------------------------|" << endl;
			cout << "|Data loaded successfully!|" << endl;
			cout << "|-------------------------|" << endl;
		}
	

	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
	}
}

/********************************
* Saves data from vectors to file
********************************/
void SaveBudgetFile(vector<string> namesOfEntries, vector<double> entries) {
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

		for (int i = 0; i < namesOfEntries.size(); i++) {
			saveDataToFile << entries.at(i) << " " << namesOfEntries.at(i) << endl;
		}

		saveDataToFile << ResizableBorder(accountName.size()) << endl;
		saveDataToFile << GetCurrentBalance(entries) << endl << endl;
		saveDataToFile.close();
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what();
	}
}

/**************************
* Saves user income to file
**************************/
void SaveIncomeInfo() {
	ofstream saveIncome;
	

	try {
		saveIncome.open("IncomeData.txt");

		if (!saveIncome.is_open()) {
			throw runtime_error("File unable to be opened.");
		}
		
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what()  << endl;
	}
}

/***************************************************************
* Checks to see if income info is already present in the file, a 
* crucial part of the save info function
***************************************************************/
bool IncomeInfoPresent() {
	ifstream fileCheck;

	string checker;

	try {
		fileCheck.open("IncomeDataFile.txt");

		if (!fileCheck.is_open()) {
			throw runtime_error("File unable to be opened.");
		}
		fileCheck >> checker;
		if (fileCheck.fail()) {
			return false;
		}

		return true;
	}
	catch (runtime_error& excpt) {
		cout << "Error: " << excpt.what() << endl;
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

/***************************************************
* Meant to erase all data contained in the .txt file
***************************************************/
void WipeAllData(string FILENAME) {
	ofstream dataRemoval;

	try {
		dataRemoval.open(FILENAME);
		
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

	globalCurrentBalance = currentBalance;

	return currentBalance;
}