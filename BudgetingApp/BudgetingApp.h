#include <vector>

using namespace std;

#ifndef BUDGETINGAPP_H
#define BUDGETINGAPP_H
bool IncomeInfoPresent();

int MainMenu();
int ValidateNumericInput();

double GetTotal();
double GetCurrentBalance(vector<double> entries);

string GetAccountName();
string ResizableBorder(int size);

void FillStartingInfo();
void WipeAllData();
void BudgetingHeader();
void IncomeHeader();
void SettingsHeader();
void BudgetingMenu(vector<string>& namesOfEntries, vector<double>& entries);
void IncomeMenu();
void SettingsMenu();
void AddEntryToList(vector<string>& namesOfEntries, vector<double>& entries);
void LoadFile(vector<string>& namesOfEntries, vector<double>& entries);
void SaveFile(vector<string> namesOfEntries, vector<double> entries);
void SaveIncomeInfo();
#endif // !BUGETINGAPP_H
