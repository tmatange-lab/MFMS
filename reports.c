/*
 * reports.c - Reports module (Section 8 of the Project A brief)
 * MFMS - Municipal Financial Management System
 *
 * Reports: Employee, Budget, Supplier, Asset.
 *
 * Employee and budget data are read through "getter" functions that the
 * employees and budget modules provide (see employees.h and budget.h).
 * Supplier and asset reports reuse displaySuppliers() / displayAssets().
 *
 * Concepts used: loops, if/else, switch, functions with parameters and
 * return values, and string functions (strlen, strncpy).
 */
#include <stdio.h>
#include <string.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"

#define NAME_BUF 100

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
    int i, highIdx = 0, lowIdx = 0;
    double salary, total = 0.0, highest = 0.0, lowest = 0.0;
    char highName[NAME_BUF], lowName[NAME_BUF], buf[32];

    printTitle("EMPLOYEE REPORT");

    if (count <= 0) {
        printf("No employees have been registered yet.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        salary = getEmployeeSalary(i);
        total += salary;

        if (i == 0 || salary > highest) {
            highest = salary;
            highIdx = i;
        }
        if (i == 0 || salary < lowest) {
            lowest = salary;
            lowIdx = i;
        }
    }

    strncpy(highName, getEmployeeName(highIdx), NAME_BUF - 1);
    highName[NAME_BUF - 1] = '\0';
    strncpy(lowName, getEmployeeName(lowIdx), NAME_BUF - 1);
    lowName[NAME_BUF - 1] = '\0';

    printf("Total Employees : %d\n", count);
    formatMoney(total / count, buf);
    printf("Average Salary  : %s\n", buf);
    formatMoney(highest, buf);
    printf("Highest Salary  : %s  (%s)\n", buf, highName);
    formatMoney(lowest, buf);
    printf("Lowest Salary   : %s  (%s)\n", buf, lowName);
    formatMoney(total, buf);
    printf("Total Payroll   : %s\n", buf);
}

/* ----------------------------- 2. BUDGET REPORT ----------------------------- */

void budgetReport(void)
{
    int count = getBudgetCount();
    int i, exceeded = 0;
    double allocated, spent, totalAllocated = 0.0, totalSpent = 0.0;
    char a[32], e[32], r[32];

    printTitle("BUDGET REPORT");

    if (count <= 0) {
        printf("No departmental budgets have been entered yet.\n");
        return;
    }

    printf("%-20s %16s %16s %16s  %s\n",
           "Department", "Allocated", "Expenditure", "Remaining", "Status");
    printLine('-', 88);

    for (i = 0; i < count; i++) {
        allocated = getBudgetAllocated(i);
        spent = getBudgetExpenditure(i);
        totalAllocated += allocated;
        totalSpent += spent;

        formatMoney(allocated, a);
        formatMoney(spent, e);
        formatMoney(allocated - spent, r);

        printf("%-20.20s %16s %16s %16s  %s\n",
               getBudgetDepartment(i), a, e, r,
               (spent > allocated) ? "OVER BUDGET" : "WITHIN BUDGET");
    }
    printLine('-', 88);

    formatMoney(totalAllocated, a);
    formatMoney(totalSpent, e);
    formatMoney(totalAllocated - totalSpent, r);
    printf("Total allocated budget : %s\n", a);
    printf("Total expenditure      : %s\n", e);
    printf("Total remaining budget : %s\n\n", r);

    printf("Departments exceeding budget:\n");
    for (i = 0; i < count; i++) {
        allocated = getBudgetAllocated(i);
        spent = getBudgetExpenditure(i);
        if (spent > allocated) {
            formatMoney(spent - allocated, r);
            printf("  - %s (over by %s)\n", getBudgetDepartment(i), r);
            exceeded++;
        }
    }
    if (exceeded == 0) {
        printf("  None - all departments are within budget.\n");
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
    printTitle("ASSET REPORT");
    displayAssets();
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
