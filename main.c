#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef struct {
    int ID;
    char username[50];
    char password[50];
    char gender;
    char ic_num[13];
    char phoneNo[12];
} User;

// Member Functions
void member();
void newMember();

// Staff Functions
void staff();

// Misc Functions

void main() {
    int choice;
    do {
        system("cls");
        printf("_____   ____________________________^__\n");
        printf(" ___ |||  ___   ___   ___  |   __  ,----\n");
        printf("|   |||| |   | |   | |   | |  |  | |_____\\\n");
        printf("|___|||| |___| |___| | O | |  |  |        \\\n");
        printf("     |||             |___| |  |__|         )\n");
        printf("_____|||___________________|______________/\n");
        printf("     |||                             /\n");
        printf("-----'''----------------------------'\n");

        printf("================================================\n\nWelcome to GS Train Systems!\n\n1. Member\n2. Staff\n3. Exit\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                member();
                break;
            case 2:
                staff();
                break;
            case 3:
                printf("\nHave a good day!\n");
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
        system("pause");
    } while (choice != 3);
}

void member() {
    int choice;
    do {
        printf("1. Login\n2. Register\n3. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                /* code */
                break;
            case 2:
                newMember();
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
    } while (choice != 3);
}

void staff() {
    printf("\nUnder construction!\n");
}

void newMember() {
    User newUser, existingUser;

    system("cls");
    printf("Member Registration\n=====================\n");

    FILE* file = fopen("user.bin", "ab+");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    srand((unsigned int)time(NULL));
    newUser.ID = rand() % 9000000 + 1000000;

    printf("Enter Username: ");
    rewind(stdin);
    scanf("%[^\n]", &newUser.username);

    int usernameExists = 0;
    while (fread(&existingUser, sizeof(User), 1, file)) {
        if (strcmp(existingUser.username, newUser.username) == 0) {
            printf("Username '%s' already exists. Please enter a different username.\n", newUser.username);
            usernameExists = 1;
            break;
        }
    }

    if (!usernameExists) {
        printf("Enter Password: ");
        rewind(stdin);
        scanf("%s", &newUser.password);

        do {
            printf("Enter Gender (M/F): ");
            rewind(stdin);
            newUser.gender = toupper(getchar());
        } while (newUser.gender != 'M' && newUser.gender != 'F');

        do {
            printf("Enter IC Number (DDMMYY########): ");
            rewind(stdin);
            scanf("%s", &newUser.ic_num);

            if (strlen(newUser.ic_num) != 12) {
                printf("\nIC number must be 12 digits long.\n\n");
            }
        } while (strlen(newUser.ic_num) != 12);

        do {
            printf("Enter Phone Number (01#########): ");
            rewind(stdin);
            scanf("%s", newUser.phoneNo);

            if ((strlen(newUser.phoneNo) < 10 || strlen(newUser.phoneNo) > 11)) {
                printf("\nPhone Number must be between 10 and 11 digits long.\n\n");
            } else if (strncmp(newUser.phoneNo, "01", 2)) {
                printf("\nPhone Number must start with \"01\".\n\n");
            }
        } while ((strlen(newUser.phoneNo) < 10 || strlen(newUser.phoneNo) > 11) || strncmp(newUser.phoneNo, "01", 2));

        fwrite(&newUser, sizeof(User), 1, file);
        fclose(file);

        printf("\nYou have been successfully registered!\n\n");
    }
}