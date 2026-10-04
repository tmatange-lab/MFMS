#include <stdio.h>
#include <string.h>
#include "employees.h"

struct Employee {
    int EmpID;
    char EmpName[100];
    char Department[100];
    double BasicSalary;
};

static struct Employee employees[100]; // global array
static int count = 0;                  // number of employees added

void addEmployee(void) {
    printf("Employee ID: ");
    scanf("%d", &employees[count].EmpID);
    getchar(); // clear newline

    printf("Name: ");
    fgets(employees[count].EmpName, sizeof(employees[count].EmpName), stdin);
    employees[count].EmpName[strcspn(employees[count].EmpName, "\n")] = '\0';

    printf("Department: ");
    fgets(employees[count].Department, sizeof(employees[count].Department), stdin);
    employees[count].Department[strcspn(employees[count].Department, "\n")] = '\0';

    printf("Basic Salary: ");
    scanf("%lf", &employees[count].BasicSalary);

    count++;
    printf("\nEmployee added successfully!\n");
}

void displayEmployees(void) {
    printf("\n--- Employee List ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\n", employees[i].EmpID);
        printf("Name: %s\n", employees[i].EmpName);
        printf("Department: %s\n", employees[i].Department);
        printf("Salary: %.2lf\n\n", employees[i].BasicSalary);
    }
}

void searchEmployee(void) {
    int searchID, found = 0;
    printf("Enter Employee ID to search: ");
    scanf("%d", &searchID);

    for (int i = 0; i < count; i++) {
        if (employees[i].EmpID == searchID) {
            printf("\nEmployee Found:\n");
            printf("ID: %d\n", employees[i].EmpID);
            printf("Name: %s\n", employees[i].EmpName);
            printf("Department: %s\n", employees[i].Department);
            printf("Salary: %.2lf\n", employees[i].BasicSalary);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Employee not found.\n");
    }
}

void calculateSalary(void) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += employees[i].BasicSalary;
    }
    if (count > 0) {
        printf("Total Salary: %.2lf\n", total);
        printf("Average Salary: %.2lf\n", total / count);
    } else {
        printf("No employees to calculate.\n");
    }
}

void employeeMenu(void) {
    int UserChoice;
    do {
        printf("\n---EMPLOYEE MANAGEMENT---\n");
        printf("Menu\n");
        printf("1. Add an employee\n");
        printf("2. Display employees\n");
        printf("3. Search for an employee\n");
        printf("4. Calculate employee salary information\n");
        printf("5. Exit\n");
        printf("What do you want to do: ");
        scanf("%d", &UserChoice);
        getchar(); // clear newline

        switch (UserChoice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: calculateSalary(); break;
            case 5: printf("Exiting program...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (UserChoice != 5);
}
