#include <stdio.h>
#include <string.h>

struct Asset {
    char id[20];
    char name[50];
    char type[30];
    float value;
    char department[50];
    char condition[20];
};

struct Asset assets[100];
int count = 0; // how many assets we have

void addAsset(){
    if(count >= 100){
        printf("Full already, cant add more\n");
        return;
    }

    printf("\nEnter ID: ");
    scanf("%s", assets[count].id);

    printf("Enter Name: ");
    scanf(" %[^\n]", assets[count].name);

    printf("Enter Type: ");
    scanf(" %[^\n]", assets[count].type);

    printf("Enter Value: ");
    scanf("%f", &assets[count].value);

    if(assets[count].value < 0){
        printf("Value cant be negative\n");
        return;
    }

    printf("Enter Department: ");
    scanf(" %[^\n]", assets[count].department);

    printf("Enter Condition: ");
    scanf(" %[^\n]", assets[count].condition);

    count++;
    printf("Asset added.\n");
}

void showAssets(){
    if(count == 0){
        printf("\nNo assets yet\n");
        return;
    }

    printf("\n--- Asset Register ---\n");
    for(int i=0; i<count; i++){
        printf("\nAsset %d\n", i+1);
        printf("ID: %s\n", assets[i].id);
        printf("Name: %s\n", assets[i].name);
        printf("Type: %s\n", assets[i].type);
        printf("Value: %.2f\n", assets[i].value);
        printf("Department: %s\n", assets[i].department);
        printf("Condition: %s\n", assets[i].condition);
    }
}

void findAsset(){
    char searchID[20];
    int found = 0;

    printf("\nEnter ID to search: ");
    scanf("%s", searchID);

    for(int i=0; i<count; i++){
        if(strcmp(assets[i].id, searchID) == 0){
            printf("\nFound it!\n");
            printf("ID: %s\n", assets[i].id);
            printf("Name: %s\n", assets[i].name);
            printf("Type: %s\n", assets[i].type);
            printf("Value: %.2f\n", assets[i].value);
            printf("Department: %s\n", assets[i].department);
            printf("Condition: %s\n", assets[i].condition);
            found = 1;
            break;
        }
    }
    if(found == 0){
        printf("No asset with that ID\n");
    }
}

int main(){
    int choice;

    do{
        printf("\n--- Asset Menu ---\n");
        printf("1. Add Asset\n");
        printf("2. Show Assets\n");
        printf("3. Find Asset\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if(choice == 1){
            addAsset();
        }
        else if(choice == 2){
            showAssets();
        }
        else if(choice == 3){
            findAsset();
        }
        else if(choice == 4){
            printf("Exiting program...Bye!\n");
        }
        else{
            printf("Invalid choice\n");
        }

    }while(choice!= 4);

    return 0;
}