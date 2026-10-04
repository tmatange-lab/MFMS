#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "validation.h"

/* Private to this module: other files use getAssetCount()/getAsset() */
static struct Asset assets[MAX_ASSETS];
static int assetCount = 0;

/* Returns the index of the asset with this ID, or -1 if not found */
static int findAssetIndex(const char *id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (strcmp(assets[i].id, id) == 0)
            return i;
    }
    return -1;
}

static void printAsset(const struct Asset *a)
{
    printf("ID:         %s\n", a->id);
    printf("Name:       %s\n", a->name);
    printf("Type:       %s\n", a->type);
    printf("Value:      N$%.2f\n", a->value);
    printf("Department: %s\n", a->department);
    printf("Condition:  %s\n", a->condition);
}

void addAsset(void)
{
    char id[20];
    struct Asset *a;

    if (assetCount >= MAX_ASSETS) {
        printf("\nAsset register is full. Cannot add more.\n");
        return;
    }

    a = &assets[assetCount];
    printf("\n--- Add Asset ---\n");

    /* Keep asking until the ID is not already used */
    while (1) {
        readText("Enter asset ID (e.g. A001): ", id, sizeof id);
        if (findAssetIndex(id) == -1)
            break;
        printf("  That asset ID already exists.\n");
    }
    strcpy(a->id, id);

    do {
        readText("Enter asset name: ", a->name, sizeof a->name);
        if (!hasLetter(a->name))
            printf("  Name must contain letters.\n");
    } while (!hasLetter(a->name));

    do {
        readText("Enter asset type (e.g. Vehicle): ", a->type, sizeof a->type);
        if (!hasLetter(a->type))
            printf("  Type must contain letters.\n");
    } while (!hasLetter(a->type));

    a->value = readFloat("Enter purchase value (N$): ", 0);

    do {
        readText("Enter department: ", a->department, sizeof a->department);
        if (!hasLetter(a->department))
            printf("  Department must contain letters.\n");
    } while (!hasLetter(a->department));

    readText("Enter condition (e.g. Good): ", a->condition, sizeof a->condition);

    assetCount++;
    printf("Asset added successfully.\n");
}

void showAssets(void)
{
    int i;

    if (assetCount == 0) {
        printf("\nNo assets registered yet.\n");
        return;
    }

    printf("\n--- Asset Register ---\n");
    for (i = 0; i < assetCount; i++) {
        printf("\nAsset %d\n", i + 1);
        printAsset(&assets[i]);
    }
    printf("\nTotal assets: %d\n", assetCount);
}

void findAsset(void)
{
    char searchID[20];
    int index;

    if (assetCount == 0) {
        printf("\nNo assets registered yet.\n");
        return;
    }

    readText("\nEnter asset ID to search: ", searchID, sizeof searchID);
    index = findAssetIndex(searchID);

    if (index == -1) {
        printf("No asset with that ID.\n");
    } else {
        printf("\nAsset found:\n");
        printAsset(&assets[index]);
    }
}

int getAssetCount(void)
{
    return assetCount;
}

const struct Asset *getAsset(int index)
{
    if (index < 0 || index >= assetCount)
        return NULL;
    return &assets[index];
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("           ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset by ID\n");
        printf("4. Back to Main Menu\n");

        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addAsset();   break;
            case 2: showAssets(); break;
            case 3: findAsset();  break;
            case 4: break;
        }
    } while (choice != 4);
}