#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

/* Menu for the Employee Management module (called from main.c). */
void employeeMenu(void);

void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);

/* Salary calculations: values are passed in and results returned. */
float calculateGross(float basic, float housing, float transport);
float calculateSSC(float basic);
float calculateTax(float gross);
float calculateNet(float gross, float ssc, float tax);

/* Used by the Reports module. */
int   getEmployeeCount(void);
float getAverageSalary(void);   /* average gross salary */
float getHighestSalary(void);
float getLowestSalary(void);

#endif
