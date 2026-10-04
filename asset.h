#ifndef ASSET_H
#define ASSET_H

#include <stdio.h>
#include <string.h>

/* Maximum number of assets the register can hold */
#define MAX_ASSETS 100

/* Asset record */
struct Asset {
    char id[20];
    char name[50];
    char type[30];
    float value;
    char department[50];
    char condition[20];
};

/* Global data (defined in the .c file) */
extern struct Asset assets[MAX_ASSETS];
extern int count;   /* number of assets currently stored */

/* Function prototypes */
void addAsset(void);    /* prompt user and add a new asset */
void showAssets(void);  /* display all assets */
void findAsset(void);   /* search for an asset by ID */

#endif /* ASSET_H */