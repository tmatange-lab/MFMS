/*
 * reports.c - Reports module (Section 8 of the Project A brief)
 * MFMS - Municipal Financial Management System
 *
 * Reports: Employee, Budget, Supplier, Asset.
 *
 * The figures come from the other modules through their read-only
 * "Reports module" functions:
 *   employees.h : getEmployeeCount, getAverageSalary, getHighestSalary,
 *                 getLowestSalary
 *   budget.h    : getDepartmentCount, getTotalAllocated, getTotalExpenditure,
 *                 getTotalRemaining, countExceededDepartments,
 *                 displayBudgets, displayExceededDepartments
 *   suppliers.h : displaySuppliers
 *   assets.h    : getAssetCount, getAsset
 *
 * Concepts used: loops, if/else, switch, functions with return values,
 * and string handling (strlen).
 */
#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

/* ---------------- helper functions (private to this file) ---------------- */

static void printLine(char ch, int length)
{
    int i;
    for (i = 0; i < length; i++) {
        putchar(ch);
    }
    putchar('\n');
}

static void printTitle(const char *title)
{
    printf("\n");
    printLine('=', 60);
    printf("%s\n", title);
    printLine('=', 60);
}

/* Turn an amount into text such as "N$18,500.00" (with thousands commas).
 * 'out' must hold at least 32 characters. */
static void formatMoney(double amount, char *out)
{
    char digits[32];
    char grouped[48];
    int negative = 0;
    long long cents, whole;
    int frac, len, i, g = 0, pos = 0;

    if (amount < 0) {
        negative = 1;
        amount = -amount;
    }
    cents = (long long)(amount * 100.0 + 0.5);   /* round to nearest cent */
    whole = cents / 100;
    frac  = (int)(cents % 100);

    sprintf(digits, "%lld", whole);
    len = (int)strlen(digits);

    /* build the digits backwards, inserting a comma after every 3 digits */
    for (i = len - 1; i >= 0; i--) {
        if (g == 3) {
            grouped[pos++] = ',';
            g = 0;
        }
        grouped[pos++] = digits[i];
        g++;
    }
    grouped[pos] = '\0';

    /* flip it back the right way round */
    for (i = 0; i < pos / 2; i++) {
        char tmp = grouped[i];
        grouped[i] = grouped[pos - 1 - i];
        grouped[pos - 1 - i] = tmp;
    }

    sprintf(out, "%sN$%s.%02d", negative ? "-" : "", grouped, frac);
}

/* Read a menu choice between min and max. Keeps asking until it is valid.
 * Returns max if input ends (EOF) so the menu can never loop forever. */
static int readChoice(int min, int max)
{
    int value, c;

    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &value) != 1) {
            if (feof(stdin)) {
                return max;
            }
            while ((c = getchar()) != '\n' && c != EOF) {
                ;   /* throw away the bad input */
            }
            printf("Invalid choice. Please enter a number from %d to %d.\n", min, max);
            continue;
        }
        while ((c = getchar()) != '\n' && c != EOF) {
            ;       /* throw away the rest of the line */
        }
        if (value >= min && value <= max) {
            return value;
        }
        printf("Invalid choice. Please enter a number from %d to %d.\n", min, max);
    }
}

/* ---------------------------- 1. EMPLOYEE REPORT ---------------------------- */

void employeeReport(void)
{
    int count = getEmployeeCount();
    char buf[32];

    printTitle("EMPLOYEE REPORT");

    if (count <= 0) {
        printf("No employees have been registered yet.\n");
        return;
    }

    printf("Total Employees : %d\n", count);
    formatMoney(getAverageSalary(), buf);
    printf("Average Salary  : %s\n", buf);
    formatMoney(getHighestSalary(), buf);
    printf("Highest Salary  : %s\n", buf);
    formatMoney(getLowestSalary(), buf);
    printf("Lowest Salary   : %s\n", buf);
}

/* ----------------------------- 2. BUDGET REPORT ----------------------------- */

void budgetReport(void)
{
    int count = getDepartmentCount();
    int exceeded;
    char buf[32];

    printTitle("BUDGET REPORT");

    if (count <= 0) {
        printf("No departmental budgets have been entered yet.\n");
        return;
    }

    printf("Total Departments : %d\n\n", count);

    /* every department with its allocation, spending and status */
    displayBudgets();

    printf("\n");
    printLine('-', 60);
    formatMoney(getTotalAllocated(), buf);
    printf("Total allocated budget : %s\n", buf);
    formatMoney(getTotalExpenditure(), buf);
    printf("Total expenditure      : %s\n", buf);
    formatMoney(getTotalRemaining(), buf);
    printf("Total remaining budget : %s\n", buf);
    printLine('-', 60);

    exceeded = countExceededDepartments();
    printf("Departments exceeding budget: %d\n", exceeded);
    if (exceeded > 0) {
        displayExceededDepartments();
    } else {
        printf("None - all departments are within budget.\n");
    }
}

/* ---------------------------- 3. SUPPLIER REPORT ---------------------------- */

void supplierReport(void)
{
    printTitle("SUPPLIER REPORT");
    displaySuppliers();
}

/* ----------------------------- 4. ASSET REPORT ------------------------------ */

void assetReport(void)
{
    int count = getAssetCount();
    int i;
    double totalValue = 0.0;
    const struct Asset *a;
    char buf[32];

    printTitle("ASSET REPORT");

    if (count <= 0) {
        printf("No assets have been registered yet.\n");
        return;
    }

    printf("%-8s %-20s %-12s %16s  %-14s %-10s\n",
           "ID", "Asset", "Type", "Purchase Value", "Department", "Condition");
    printLine('-', 88);

    for (i = 0; i < count; i++) {
        a = getAsset(i);
        if (a == NULL) {
            continue;
        }
        totalValue += a->value;
        formatMoney(a->value, buf);
        printf("%-8.8s %-20.20s %-12.12s %16s  %-14.14s %-10.10s\n",
               a->id, a->name, a->type, buf, a->department, a->condition);
    }
    printLine('-', 88);

    formatMoney(totalValue, buf);
    printf("Total assets registered : %d\n", count);
    printf("Total purchase value    : %s\n", buf);
}

/* ------------------------------ REPORTS MENU ------------------------------- */

void reportsMenu(void)
{
    int choice;

    do {
        printTitle("REPORTS MENU");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. All Reports\n");
        printf("6. Back to Main Menu\n");

        choice = readChoice(1, 6);

        switch (choice) {
            case 1: employeeReport(); break;
            case 2: budgetReport();   break;
            case 3: supplierReport(); break;
            case 4: assetReport();    break;
            case 5:
                employeeReport();
                budgetReport();
                supplierReport();
                assetReport();
                break;
            case 6: break;
        }
    } while (choice != 6);
}
