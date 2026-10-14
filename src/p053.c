#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/rand.h>

#define MIN_LENGTH 8
#define MAX_LENGTH 16

const char LOWERCASE[] = "abcdefghijklmnopqrstuvwxyz";
const char UPPERCASE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char NUMBERS[] = "0123456789";
const char SPECIAL_CHARACTERS[] = "!@#$%^&*()_-+=[]{}|;:,.<>/?";

unsigned int sslRand () {
    unsigned int randNum;
    int result = RAND_bytes((unsigned char *)&randNum, sizeof(randNum));
    if (result != 1) {
        printf("RAND_bytes failed\n");
        exit(1);
    }
    return randNum;
}

void generatePassword(char password[], int length);

int main() {
    int length;
    char password[MAX_LENGTH+1];

    printf("Welcome to the C Password Generator!\n");
    printf("Password length must be between %d and %d characters.\n", MIN_LENGTH, MAX_LENGTH);

    do {
        printf("Enter password length: ");
        scanf("%9d", &length);

        if (length < MIN_LENGTH || length > MAX_LENGTH) {
            printf("Password length must be between %d and %d characters.\n", MIN_LENGTH, MAX_LENGTH);
        }
    } while (length < MIN_LENGTH || length > MAX_LENGTH);
    generatePassword(password, length);
    printf("Your randomly generated password is: %s\n", password);

    return 0;
}

void generatePassword(char password[], int length) {
    int i, rnd, category;
    int numCategories = 4;
    int categoriesNeeded = 1;
    int numCharsInCategory[numCategories];
    int minCharsInCategory = 2;

    memset(numCharsInCategory, 0, sizeof(numCharsInCategory));

    for (i=0; i<length; i++) {
        if (categoriesNeeded == 1) {
            category = sslRand() % numCategories;
        } else {
            do {
                category = sslRand() % numCategories;
            } while (numCharsInCategory[category] >= minCharsInCategory);
        }

        switch (category) {
            case 0:
                rnd = sslRand() % strlen(LOWERCASE);
                password[i] = LOWERCASE[rnd];
                numCharsInCategory[category]++;
                break;

            case 1:
                rnd = sslRand() % strlen(UPPERCASE);
                password[i] = UPPERCASE[rnd];
                numCharsInCategory[category]++;
                break;

            case 2:
                rnd = sslRand() % strlen(NUMBERS);
                password[i] = NUMBERS[rnd];
                numCharsInCategory[category]++;
                break;

            case 3:
                rnd = sslRand() % strlen(SPECIAL_CHARACTERS);
                password[i] = SPECIAL_CHARACTERS[rnd];
                numCharsInCategory[category]++;
                break;
        }

        if (i == length-1 && categoriesNeeded < numCategories) {
            categoriesNeeded++;
        }
    }

    password[length] = '\0';
}
