#include <stdio.h>
#include <string.h>
#include "suppliers.h"
const int maxSuppliers = 50;
char supplierIds[50][10];
char supplierNames[50][100];
char supplierEmails[50][100];
char supplierPhones[50][30];
char supplierTowns[50][50];
char supplierInput[200];
int supplierCount = 0;
void readSupplierInput(void) { fgets(supplierInput, sizeof(supplierInput), stdin); supplierInput[strcspn(supplierInput, "\n")] = '\0'; }
char getSupplierChoice(void) { printf("Enter your choice: "); readSupplierInput(); if (strlen(supplierInput) == 1) { return supplierInput[0]; } return '?'; }
int findSupplierById(char id[]) { for (int i = 0; i < supplierCount; i++) { if (strcmp(supplierIds[i], id) == 0) { return i; } } return -1; }
int supplierLengthOk(int size) {
    int length = strlen(supplierInput);
    if (length == 0) { printf("Error: input cannot be empty.\n"); return 0; }
    if (length > size - 1) { printf("Error: input too long (maximum %d characters).\n", size - 1); return 0; }
    return 1;
}
int supplierIdOk(void) { if (findSupplierById(supplierInput) == -1) { return 1; } printf("Error: that supplier ID already exists.\n"); return 0; }
int supplierEmailOk(void) {
    int length = strlen(supplierInput), atPosition = -1, atCount = 0, dotAfterAt = 0, spaces = 0;
    for (int i = 0; i < length; i++) {
        if (supplierInput[i] == ' ') { spaces++; }
        else if (supplierInput[i] == '@') { atCount++; atPosition = i; }
        else if (supplierInput[i] == '.' && atPosition != -1 && i > atPosition + 1 && i < length - 1) { dotAfterAt = 1; }
    }
    if (atCount == 1 && atPosition > 0 && dotAfterAt == 1 && spaces == 0) { return 1; }
    printf("Error: invalid email (example: sales@abc.com).\n"); return 0;
}
int supplierPhoneOk(void) {
    int length = strlen(supplierInput), digits = 0;
    for (int i = 0; i < length; i++) { if (supplierInput[i] >= '0' && supplierInput[i] <= '9') { digits++; } }
    if (length >= 7 && length <= 15 && digits == length) { return 1; }
    printf("Error: phone must be 7 to 15 digits.\n"); return 0;
}
void addSupplier(void) {
    if (supplierCount >= maxSuppliers) { printf("Supplier list is full.\n"); return; }
    do { printf("Enter supplier ID (e.g. S001): "); readSupplierInput(); } while (!supplierLengthOk(10) || !supplierIdOk());
    strcpy(supplierIds[supplierCount], supplierInput);
    do { printf("Enter supplier name: "); readSupplierInput(); } while (!supplierLengthOk(100));
    strcpy(supplierNames[supplierCount], supplierInput);
    do { printf("Enter email: "); readSupplierInput(); } while (!supplierLengthOk(100) || !supplierEmailOk());
    strcpy(supplierEmails[supplierCount], supplierInput);
    do { printf("Enter phone (digits only): "); readSupplierInput(); } while (!supplierPhoneOk());
    strcpy(supplierPhones[supplierCount], supplierInput);
    do { printf("Enter town/location: "); readSupplierInput(); } while (!supplierLengthOk(50));
    strcpy(supplierTowns[supplierCount], supplierInput);
    supplierCount++;
    printf("Supplier added successfully.\n");
}
void displaySuppliers(void) {
    if (supplierCount == 0) { printf("\nNo suppliers registered.\n"); return; }
    printf("\nID | Name | Email | Phone | Town\n------------------------------------------------\n");
    for (int i = 0; i < supplierCount; i++) { printf("%s | %s | %s | %s | %s\n", supplierIds[i], supplierNames[i], supplierEmails[i], supplierPhones[i], supplierTowns[i]); }
    printf("\nTotal suppliers: %d\n", supplierCount);
}
void showSupplier(int index) {
    char summary[200];
    strcpy(summary, supplierNames[index]);
    strcat(summary, " operates in ");
    strcat(summary, supplierTowns[index]);
    strcat(summary, ".");
    printf("\n--- SUPPLIER DETAILS ---\nID   : %s\nName : %s (%zu characters)\n", supplierIds[index], supplierNames[index], strlen(supplierNames[index]));
    printf("Email: %s\nPhone: %s\nTown : %s\n%s\n", supplierEmails[index], supplierPhones[index], supplierTowns[index], summary);
}
void searchSupplier(void) {
    char choice, term[200];
    int found = 0, match;
    if (supplierCount == 0) { printf("\nNo suppliers registered.\n"); return; }
    printf("\nSearch by: 1. ID  2. Name  3. Town\n");
    choice = getSupplierChoice();
    if (choice != '1' && choice != '2' && choice != '3') { printf("Invalid search option.\n"); return; }
    printf("Enter search text (exact match): ");
    readSupplierInput();
    strcpy(term, supplierInput);
    for (int i = 0; i < supplierCount; i++) {
        match = 0;
        if (choice == '1' && strcmp(supplierIds[i], term) == 0) { match = 1; }
        if (choice == '2' && strcmp(supplierNames[i], term) == 0) { match = 1; }
        if (choice == '3' && strcmp(supplierTowns[i], term) == 0) { match = 1; }
        if (match == 1) { showSupplier(i); found++; }
    }
    if (found == 0) { printf("Supplier not found.\n"); } else { printf("\n%d supplier(s) found.\n", found); }
}
void compareSuppliers(void) {
    char idA[200], idB[200];
    int a, b, order;
    if (supplierCount < 2) { printf("\nAt least two suppliers are needed to compare.\n"); return; }
    printf("Enter first supplier ID: ");
    readSupplierInput();
    strcpy(idA, supplierInput);
    printf("Enter second supplier ID: ");
    readSupplierInput();
    strcpy(idB, supplierInput);
    a = findSupplierById(idA);
    b = findSupplierById(idB);
    if (a == -1 || b == -1) { printf("Error: one or both supplier IDs were not found.\n"); return; }
    order = strcmp(supplierNames[a], supplierNames[b]);
    printf("\n--- COMPARISON ---\n");
    if (order == 0) { printf("Both suppliers have the same name: %s\n", supplierNames[a]); }
    else if (order < 0) { printf("%s comes before %s alphabetically.\n", supplierNames[a], supplierNames[b]); }
    else { printf("%s comes after %s alphabetically.\n", supplierNames[a], supplierNames[b]); }
    if (strcmp(supplierTowns[a], supplierTowns[b]) == 0) { printf("Both are based in %s.\n", supplierTowns[a]); }
    else { printf("Different locations: %s and %s.\n", supplierTowns[a], supplierTowns[b]); }
}
void supplierMenu(void) {
    char choice;
    do {
        printf("\n========================================\n          SUPPLIER MANAGEMENT\n========================================\n");
        printf("1. Add Supplier\n2. Display Suppliers\n3. Search Supplier\n4. Compare Two Suppliers\n5. Back to Main Menu\n");
        choice = getSupplierChoice();
        switch (choice) {
            case '1': addSupplier(); break;
            case '2': displaySuppliers(); break;
            case '3': searchSupplier(); break;
            case '4': compareSuppliers(); break;
            case '5': break;
            default: printf("Invalid choice. Please enter 1-5.\n");
        }
    } while (choice != '5');
}
