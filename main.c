#include <stdio.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"
#include "validation.h"



static void displayMenu(void)
{
    printf("\n=======================================\n"); // This is  Main Menu ,This will help user navigate the sytem
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("=======================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
      printf("6. Exit\n");

}

int main(void)
{
    int choice;

    do {
        displayMenu();
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice) {
            case 1: employeeMenu(); break;
            case 2: budgetMenu();   break;
            case 3: supplierMenu(); break;
            case 4: assetMenu();    break;
            case 5: reportsMenu();  break;
            case 6: printf("Thank you for using our system.\n"); break;
        }
    } while (choice != 6);

    return 0;
}