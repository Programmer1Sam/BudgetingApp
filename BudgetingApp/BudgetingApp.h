#include <vector>

using namespace std;

#ifndef BUDGETINGAPP_H
#define BUDGETINGAPP_H
int BudgetingMainMenu();
int ValidateNumericInput();

double GetTotal();
double GetCurrentBalance(vector<double> entries);

string GetAccountName();
string ResizableBorder(int size);

void FillStartingInfo();
void WipeAllData();
void AddEntryToList(vector<string>& namesOfEntries, vector<double>& entries);
void LoadFile(vector<string>& namesOfEntries, vector<double>& entries);
void SaveFile(vector<string> namesOfEntries, vector<double> entries);
#endif // !BUGETINGAPP_H
