#ifndef ASSETS_H
#define ASSETS_H

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

/* Menu used by main.c (option 4) */
void assetMenu(void);

/* Asset functions */
void addAsset(void);
void showAssets(void);
void findAsset(void);

/* Read-only access for the Reports module */
int getAssetCount(void);
const struct Asset *getAsset(int index);

#endif /* ASSETS_H */