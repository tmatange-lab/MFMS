#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "validation.h"

#define ID_LEN   10
#define NAME_LEN 50
#define DEPT_LEN 30

/* ---- Simplified payroll rules (confirm exact rates with your lecturer) ---- */
#define SSC_RATE 0.009f          /* 0.9% of basic salary */
#define SSC_CAP  81.0f           /* maximum SSC per month */

/* Parallel arrays: index i holds the data of employee i. */
static char  empId[MAX_EMPLOYEES][ID_LEN];
static char  empName[MAX_EMPLOYEES][NAME_LEN];
static char  empDept[MAX_EMPLOYEES][DEPT_LEN];
static float empBasic[MAX_EMPLOYEES];
static float empHousing[MAX_EMPLOYEES];
static float empTransport[MAX_EMPLOYEES];
static int   empCount = 0;

/* ------------------------- Calculations ------------------------- */

float calculateGross(float basic, float housing, float transport)
{
    return basic + housing + transport;
}

float calculateSSC(float basic)
{
    float ssc = basic * SSC_RATE;
    if (ssc > SSC_CAP)
        ssc = SSC_CAP;
    return ssc;
}

/* Simplified monthly tax brackets (illustrative, not official PAYE). */
float calculateTax(float gross)
{
    if (gross <= 4000.0f)
        return 0.0f;
    else if (gross <= 8000.0f)
        return (gross - 4000.0f) * 0.18f;
    else if (gross <= 15000.0f)
        return 720.0f + (gross - 8000.0f) * 0.25f;
    else
        return 2470.0f + (gross - 15000.0f) * 0.32f;
}

float calculateNet(float gross, float ssc, float tax)
{
    return gross - ssc - tax;
}

/* --------------------------- Helpers ---------------------------- */

/* Returns the index of the employee with this ID, or -1 if not found. */
static int findById(const char *id)
{
    int i;
    for (i = 0; i < empCount; i++) {
        if (strcmp(empId[i], id) == 0)
            return i;
    }
    return -1;
}

static void printEmployeeRow(int i)
{
    float gross = calculateGross(empBasic[i], empHousing[i], empTransport[i]);
    printf("%-8s %-20s %-15s N$%10.2f\n", empId[i], empName[i], empDept[i], gross);
}

static void printPayslip(int i)
{
    float gross = calculateGross(empBasic[i], empHousing[i], empTransport[i]);
    float ssc   = calculateSSC(empBasic[i]);
    float tax   = calculateTax(gross);
    float net   = calculateNet(gross, ssc, tax);

    printf("\n--- Salary Details ---\n");
    printf("Employee ID  : %s\n", empId[i]);
    printf("Name         : %s\n", empName[i]);
    printf("Department   : %s\n", empDept[i]);
    printf("Basic Salary : N$%.2f\n", empBasic[i]);
    printf("Housing      : N$%.2f\n", empHousing[i]);
    printf("Transport    : N$%.2f\n", empTransport[i]);
    printf("Gross Salary : N$%.2f\n", gross);
    printf("Social Sec.  : N$%.2f\n", ssc);
    printf("Tax          : N$%.2f\n", tax);
    printf("Net Pay      : N$%.2f\n", net);
}

/* ------------------------- Menu actions ------------------------- */

void addEmployee(void)
{
    char id[ID_LEN];

    if (empCount >= MAX_EMPLOYEES) {
        printf("Employee list is full (%d).\n", MAX_EMPLOYEES);
        return;
    }

    readText("Employee ID: ", id, ID_LEN);
    if (findById(id) != -1) {
        printf("An employee with ID %s already exists.\n", id);
        return;
    }

    strcpy(empId[empCount], id);
    readText("Full name: ", empName[empCount], NAME_LEN);
    readText("Department: ", empDept[empCount], DEPT_LEN);
    empBasic[empCount]     = readFloat("Basic salary: N$", 0.0f);
    empHousing[empCount]   = readFloat("Housing allowance: N$", 0.0f);
    empTransport[empCount] = readFloat("Transport allowance: N$", 0.0f);

    empCount++;
    printf("Employee added successfully.\n");
}

void displayEmployees(void)
{
    int i;

    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }
    printf("\n%-8s %-20s %-15s %12s\n", "ID", "Name", "Department", "Gross");
    printf("-----------------------------------------------------------\n");
    for (i = 0; i < empCount; i++)
        printEmployeeRow(i);
}

void searchEmployee(void)
{
    char id[ID_LEN];
    int index;

    if (empCount == 0) {
        printf("No employees registered yet.\n");
        return;
    }
    readText("Enter Employee ID to search: ", id, ID_LEN);
    index = findById(id);
    if (index == -1)
        printf("Employee %s not found.\n", id);
    else
        printPayslip(index);
}

/* --------------------- Statistics for Reports --------------------- */

int getEmployeeCount(void)
{
    return empCount;
}

float getAverageSalary(void)
{
    float total = 0.0f;
    int i;

    if (empCount == 0)
        return 0.0f;
    for (i = 0; i < empCount; i++)
        total += calculateGross(empBasic[i], empHousing[i], empTransport[i]);
    return total / empCount;
}

float getHighestSalary(void)
{
    float highest, g;
    int i;

    if (empCount == 0)
        return 0.0f;
    highest = calculateGross(empBasic[0], empHousing[0], empTransport[0]);
    for (i = 1; i < empCount; i++) {
        g = calculateGross(empBasic[i], empHousing[i], empTransport[i]);
        if (g > highest)
            highest = g;
    }
    return highest;
}

float getLowestSalary(void)
{
    float lowest, g;
    int i;

    if (empCount == 0)
        return 0.0f;
    lowest = calculateGross(empBasic[0], empHousing[0], empTransport[0]);
    for (i = 1; i < empCount; i++) {
        g = calculateGross(empBasic[i], empHousing[i], empTransport[i]);
        if (g < lowest)
            lowest = g;
    }
    return lowest;
}

/* ----------------------------- Menu ----------------------------- */

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n===== EMPLOYEE MANAGEMENT =====\n");
        printf("1. Add employee\n");
        printf("2. Display employees\n");
        printf("3. Search employee / salary details\n");
        printf("4. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addEmployee();      break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee();   break;
            case 4: break;
        }
    } while (choice != 4);
}
