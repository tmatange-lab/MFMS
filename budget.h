#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20

/* Menu for the Budget module it will called from main.c */
void budgetMenu(void);

void addDepartmentBudget(void);
void recordExpenditure(void);
void displayBudgets(void);
void displayExceededDepartments(void);

/* Calculations done and values are returned. */
float calculateRemaining(float allocated, float spent);
int isWithinBudget(float allocated, float spent); /* 1 = yes, 0 = no */

/* Reports module will use this. */
int getDepartmentCount(void);
float getTotalAllocated(void);
float getTotalExpenditure(void);
float getTotalRemaining(void);
int countExceededDepartments(void);

#endif
