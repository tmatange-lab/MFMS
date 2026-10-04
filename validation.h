#ifndef VALIDATION_H
#define VALIDATION_H

void readText(const char *prompt, char *buf, int size);

float readFloat(const char *prompt, float min);

int readInt(const char *prompt, int min, int max);

int hasLetter(const char *s);
int isValidSupplierID(const char *s);

#endif