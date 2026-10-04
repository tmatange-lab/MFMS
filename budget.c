#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "validation.h"

#define DEPT_LEN 30

static char deptName[MAX_DEPARTMENTS][DEPT_LEN];
static float deptAllocated[MAX_DEPARTMENTS];
static float deptSpent[MAX_DEPARTMENTS];
static int deptCount = 0;

float calculateRemaining(float allocated, float spent)
{
    return allocated - spent;
}

int isWithinBudget(float allocated, float spent)
{
    return spent <= allocated;
}

static int findDepartment(const char *name)
{
    int i;
    for (i = 0; i < deptCount; i++)
    {
        if (strcmp(deptName[i], name) == 0)
            return i;
    }
    return -1;
}

static void printDepartment(int i)
{
    float remaining = calculateRemaining(deptAllocated[i], deptSpent[i]);

    printf("\nDepartment       : %s\n", deptName[i]);
    printf("Allocated Budget : N$%.2f\n", deptAllocated[i]);
    printf("Expenditure      : N$%.2f\n", deptSpent[i]);
    printf("Remaining Budget : N$%.2f\n", remaining);
    printf("Status           : %s\n",
           isWithinBudget(deptAllocated[i], deptSpent[i])
               ? "WITHIN BUDGET"
               : "OVER BUDGET");
}

void addDepartmentBudget(void)
{
    char name[DEPT_LEN];

    if (deptCount >= MAX_DEPARTMENTS)
    {
        printf("Department list is full (%d).\n", MAX_DEPARTMENTS);
        return;
    }

    readText("Department name: ", name, DEPT_LEN);
    if (findDepartment(name) != -1)
    {
        printf("%s already has a budget.\n", name);
        return;
    }

    strcpy(deptName[deptCount], name);
    deptAllocated[deptCount] = readFloat("Allocated budget: N$", 0.0f);
    deptSpent[deptCount] = 0.0f;
    deptCount++;
    printf("Budget saved for %s.\n", name);
}

void recordExpenditure(void)
{
    char name[DEPT_LEN];
    int index;
    float amount;

    if (deptCount == 0)
    {
        printf("No departments yet. Add a department budget first.\n");
        return;
    }

    readText("Department name: ", name, DEPT_LEN);
    index = findDepartment(name);
    if (index == -1)
    {
        printf("Department %s not found.\n", name);
        return;
    }

    amount = readFloat("Expenditure to record: N$", 0.0f);
    deptSpent[index] += amount;

    if (!isWithinBudget(deptAllocated[index], deptSpent[index]))
        printf("WARNING: %s has exceeded its budget!\n", deptName[index]);
    printDepartment(index);
}

void displayBudgets(void)
{
    int i;

    if (deptCount == 0)
    {
        printf("No budgets entered yet.\n");
        return;
    }
    for (i = 0; i < deptCount; i++)
        printDepartment(i);
}

void displayExceededDepartments(void)
{
    int i, found = 0;

    printf("\nDepartments over budget:\n");
    for (i = 0; i < deptCount; i++)
    {
        if (!isWithinBudget(deptAllocated[i], deptSpent[i]))
        {
            printf("  - %s (over by N$%.2f)\n", deptName[i],
                   -calculateRemaining(deptAllocated[i], deptSpent[i]));
            found = 1;
        }
    }
    if (!found)
        printf("  None. All departments are within budget.\n");
}

int getDepartmentCount(void)
{
    return deptCount;
}

float getTotalAllocated(void)
{
    float total = 0.0f;
    int i;
    for (i = 0; i < deptCount; i++)
        total += deptAllocated[i];
    return total;
}

float getTotalExpenditure(void)
{
    float total = 0.0f;
    int i;
    for (i = 0; i < deptCount; i++)
        total += deptSpent[i];
    return total;
}

float getTotalRemaining(void)
{
    return calculateRemaining(getTotalAllocated(), getTotalExpenditure());
}

int countExceededDepartments(void)
{
    int i, count = 0;
    for (i = 0; i < deptCount; i++)
    {
        if (!isWithinBudget(deptAllocated[i], deptSpent[i]))
            count++;
    }
    return count;
}

int getBudgetCount(void)
{
    return deptCount;
}

const char *getBudgetDepartment(int index)
{
    if (index < 0 || index >= deptCount)
        return "";
    return deptName[index];
}

double getBudgetAllocated(int index)
{
    if (index < 0 || index >= deptCount)
        return 0.0;
    return deptAllocated[index];
}

double getBudgetExpenditure(int index)
{
    if (index < 0 || index >= deptCount)
        return 0.0;
    return deptSpent[index];
}

void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Enter departmental budget\n");
        printf("2. Record expenditure\n");
        printf("3. Display budget information\n");
        printf("4. Show departments over budget\n");
        printf("5. Back to main menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
        case 1:
            addDepartmentBudget();
            break;
        case 2:
            recordExpenditure();
            break;
        case 3:
            displayBudgets();
            break;
        case 4:
            displayExceededDepartments();
            break;
        case 5:
            break;
        }
    } while (choice != 5);
}
