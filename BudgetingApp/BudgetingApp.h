#include <vector> // used so data can be stored with vectors

using namespace std;

/**********************************
* DATE: 12.18.2022
* AUTHOR: SAM TAYLOR
* FILE NAME: BUDGETINGAPP_H
* FILE PURPOSE:FILE STORES FUNCTION
* PROTOTYPES FOR THE ENTIRE PROGRAM
**********************************/
#ifndef BUDGETINGAPP_H
#define BUDGETINGAPP_H

// General functions
int MainMenu(); // loads the main menu from which the user can select the operation they would like to do
int ValidateNumericInput(); // checks to make sure a number has been entered and not a string

bool FileInfoPresent(string FILENAME);

string ResizableBorder(int size); // allows for the creation of a line border with adjustable size

void PrintFileToScreen(string FILENAME);
void SettingsHeader(); // header for the settings menu
void SettingsMenu(); // setings menu 
void EnterKeyPrompt(); // prompts the user to hit the enter key allowing for a transition between operations back to menus
void WipeAllData(string FILENAME); // wipes all data in specified file

/********************
* Budgeting functions
********************/
double GetTotal(); // gets starting balance of user
double GetCurrentBalance(vector<double> entries); // gets the current balance using the balance from GetTotal

void FillStartingInfo(); // if no information is present in the file this function is called to get some basic information 
void BudgetingHeader(); // header for the budgeting menu
void BudgetingMenu(vector<string>& namesOfEntries, vector<double>& entries); // budgeting menu must use parameters for vectors
void AddEntryToList(vector<string>& namesOfEntries, vector<double>& entries); // adds an entry to the end of the list recorded in file
void LoadBudgetFile(vector<string>& namesOfEntries, vector<double>& entries); // function run at program start to fill vectors
void SaveBudgetFile(vector<string> namesOfEntries, vector<double> entries); // puts data from vectors into files

string GetAccountName(); // retrieves the name registered in the file


/*****************
* Income functions
*****************/
bool IncomeInfoPresent(); // checks to see if any income info is present in the file

void IncomeHeader(); // header for the income menu
void IncomeMenu(string userName, double balance, double income, double hoursPerWeek, double monthlyIncome, double spendingPercentage, double& spendingAmount); // menu from which all income operations are run
void UpdateIncomeDataFile(string userName, double balance, double income, 
	double hoursPerWeek, double monthlyIncome, double spendingPercentage, double spendingAmount); // function for creating an income file
void SaveIncomeInfo(); // save function for income data
void LoadIncomeData(string& userName, double& balance, double& income, 
	double& hoursPerWeek, double& monthlyIncome, double& spendingPercentage, double& spendingAmount); // loads and stores data from the income file into variables
void SkipWords(int loops, ifstream& lif);

double GetTotalIncomeInMonth(double hoursPerWeek, double income); // gets the projected income in a month
double CalculateSpendingAmount(double percentage, double income);
double GetUserIncome(); // gets user income if file has none
double GetHoursWorkedPerWeek(); // returns the users hours per week at their job
#endif // !INCOMEDATA_H
