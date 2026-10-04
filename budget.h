#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20

void budgetMenu(void);

void addDepartmentBudget(void);
void recordExpenditure(void);
void displayBudgets(void);
void displayExceededDepartments(void);

float calculateRemaining(float allocated, float spent);
int   isWithinBudget(float allocated, float spent);

int   getDepartmentCount(void);
float getTotalAllocated(void);
float getTotalExpenditure(void);
float getTotalRemaining(void);
int   countExceededDepartments(void);

#endif
