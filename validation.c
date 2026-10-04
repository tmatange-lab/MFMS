
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validation.h"

#define LINE_SIZE 128

static int getLine(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
        return 0;
    buf[strcspn(buf, "\n")] = '\0';
    return 1;
}

static int isBlank(const char *s)
{
    while (*s) {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

void readText(const char *prompt, char *buf, int size)
{
    char line[LINE_SIZE];

    while (1) {
        printf("%s", prompt);
        if (!getLine(line, sizeof line))
            exit(1);
        if (isBlank(line) || strlen(line) >= (size_t)size) {
            printf("  Invalid input. Enter 1-%d characters.\n", size - 1);
            continue;
        }
        strcpy(buf, line);
        return;
    }
}

float readFloat(const char *prompt, float min)
{
    char line[LINE_SIZE];
    char *end;
    float value;

    while (1) {
        printf("%s", prompt);
        if (!getLine(line, sizeof line))
            exit(1);
        value = strtof(line, &end);
        if (end == line || !isBlank(end)) {
            printf("  Invalid number. Please try again.\n");
        } else if (value < min) {
            printf("  Value must be at least %.2f.\n", min);
        } else {
            return value;
        }
    }
}

int readInt(const char *prompt, int min, int max)
{
    char line[LINE_SIZE];
    char *end;
    long value;

    while (1) {
        printf("%s", prompt);
        if (!getLine(line, sizeof line))
            exit(1);
        value = strtol(line, &end, 10);
        if (end == line || !isBlank(end))
            printf("  Invalid input. Enter a whole number.\n");
        else if (value < min || value > max)
            printf("  Choose a number between %d and %d.\n", min, max);
        else
            return (int)value;
    }
}

/* Returns 1 if the string contains at least one letter */
int hasLetter(const char *s)
{
    for (; *s != '\0'; s++) {
        if (isalpha((unsigned char)*s))
            return 1;
    }
    return 0;
}

/* Supplier ID format: capital S followed by 1 to 6 digits (e.g. S001) */
int isValidSupplierID(const char *s)
{
    size_t i, digits = 0;

    if (s[0] != 'S')
        return 0;
    for (i = 1; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i]))
            return 0;
        digits++;
    }
    return digits >= 1 && digits <= 6;
}