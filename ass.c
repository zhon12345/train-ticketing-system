#include <stdio.h>
#include <stdlib.h>

struct User {
    int ID;
    char name[50];
    char password[50];
    char gender;
    char ic_num[14];
    char contact_details[12];
};

void staffFunction();
void memberFunction();
void addNewUser();
void displayUserInfo(int searchID);
void displayAllUserInfo();
void deleteUser(int userID);

int main() {
    int choice;

    do {
        system("cls");
        printf("==================\n");
        printf("      Menu\n");
        printf("==================\n");
        printf("1. Staff\n");
        printf("2. Member\n");
        printf("3. Add New User\n");
        printf("4. Exit\n");
        printf("==================\n");
        printf("Enter your choice: ");

        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            staffFunction();
            break;
        case 2:
            memberFunction();
            break;
        case 3:
            addNewUser();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 4.\n");
            break;
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();

    } while (choice != 4);

    return 0;
}

void staffFunction() {
    int choice;
    int displayMenu = 1;

    do {
        if (displayMenu) {
            system("cls");
            printf("==================\n");
            printf("  Staff Function\n");
            printf("==================\n");
            printf("1. Remove User\n");
            printf("2. Check User Info\n");
            printf("3. Return to Menu\n");
            printf("==================\n");
            printf("Enter your choice: ");
            scanf_s("%d", &choice);
        }
        else {
            choice = 3;
        }

        switch (choice) {
        case 1:
            system("cls");
            printf("Remove User\n");
            printf("==========================\n");
            int userID;
            printf("Enter User ID to remove: ");
            scanf_s("%d", &userID);
            getchar();
            displayUserInfo(userID);
            printf("Do you want to delete this user? (Y/N): ");
            char deleteChoice;
            scanf_s(" %c", &deleteChoice, sizeof(deleteChoice));
            if (deleteChoice == 'Y' || deleteChoice == 'y') {
                deleteUser(userID);
                printf("\nPress Enter to continue...");
                getchar();
            }
            printf("Returning to Menu...\n");
            displayMenu = 1;
            break;
        case 2:
            system("cls");
            printf("All User Info\n");
            printf("=======================================\n");
            displayAllUserInfo();
            displayMenu = 0;
            break;
        case 3:
            printf("Returning to Menu...\n");
            displayMenu = 1;
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 3.\n");
            break;
        }
    } while (choice != 3);
}
void memberFunction() {
    system("cls");
    printf("Member Function\n");
    printf("==========================\n");

    char username[50];
    char password[50];
    printf("Enter Username: ");
    scanf_s("%s", username, sizeof(username));
    printf("Password: ");
    scanf_s("%s", password, sizeof(password));

    FILE* file;
    errno_t err = fopen_s(&file, "user.bin", "rb+");
    if (err != 0) {
        printf("Error opening file!\n");
        return;
    }

    struct User currentUser;
    int found = 0;

    while (fread(&currentUser, sizeof(struct User), 1, file)) {
        if (strcmp(currentUser.name, username) == 0 && strcmp(currentUser.password, password) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Wrong username or password.\n");
        fclose(file);
        return;
    }

    printf("User Information\n");
    printf("=====================================\n");
    printf("ID: %d\n", currentUser.ID);
    printf("Name: %s\n", currentUser.name);
    printf("Gender: %c\n", currentUser.gender);
    printf("IC: %s\n", currentUser.ic_num);
    printf("Contact: %s\n", currentUser.contact_details);
    printf("=====================================\n\n");

    char choice;
    printf("Do You Want To Change Info (Y=yes/X=no): ");
    scanf_s(" %c", &choice, sizeof(choice));

    if (choice == 'Y' || choice == 'y') {
        struct User oldUserInfo = currentUser;

        printf("Enter new password: ");
        scanf_s("%s", currentUser.password, sizeof(currentUser.password));
        printf("Enter new contact: ");
        scanf_s("%s", currentUser.contact_details, sizeof(currentUser.contact_details));

        fseek(file, -(long)sizeof(struct User), SEEK_CUR);
        fwrite(&currentUser, sizeof(struct User), 1, file);
        fclose(file);

        printf("User information updated successfully.\n");

        printf("\nUpdated User Information\n");
        printf("=====================================\n");
        printf("ID: %d\n", currentUser.ID);
        printf("Name: %s\n", currentUser.name);
        printf("Gender: %c\n", currentUser.gender);
        printf("IC: %s\n", currentUser.ic_num);
        printf("Contact: %s\n", currentUser.contact_details);
        printf("=====================================\n\n");
    }
    else if (choice == 'X' || choice == 'x') {
        printf("If you don't want to change the info, please exit. Goodbye!\n");
        fclose(file);
        return;
    }
    else {
        printf("Invalid option, exiting to main menu.\n");
        fclose(file);
        return;
    }
}

void addNewUser() {
    system("cls");
    printf("   Add New User\n");
    printf("==================\n");
    struct User newUser;

    FILE* file;
    errno_t err = fopen_s(&file, "user.bin", "ab");
    if (err != 0 || file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    srand((unsigned int)time(NULL));
    newUser.ID = rand() % 9000000 + 1000000;

    printf("Enter Name: ");
    scanf_s("%s", newUser.name, sizeof(newUser.name));

    fseek(file, 0, SEEK_SET);
    struct User existingUser;
    int usernameExists = 0;
    while (fread(&existingUser, sizeof(struct User), 1, file)) {
        if (strcmp(existingUser.name, newUser.name) == 0) {
            printf("Username '%s' already exists. Please enter a different username.\n", newUser.name);
            usernameExists = 1;
            break;
        }
    }

    if (usernameExists) {
        fclose(file);
        return;
    }

    printf("Enter Password: ");
    scanf_s("%s", newUser.password, sizeof(newUser.password));

    printf("Enter Gender (M/F): ");
    scanf_s(" %c", &newUser.gender, sizeof(newUser.gender));

    printf("Enter IC Number (DDMMYY########): ");
    do {
        scanf_s("%13s", newUser.ic_num, sizeof(newUser.ic_num));
        if (strlen(newUser.ic_num) != 12) {
            printf("IC number must be 13 characters long. Please try again: ");
        }
    } while (strlen(newUser.ic_num) != 12);

    printf("Enter Contact Details (########## starting with '01'): ");
    do {
        scanf_s("%11s", newUser.contact_details, sizeof(newUser.contact_details));
        if (strlen(newUser.contact_details) != 11 || strncmp(newUser.contact_details, "01", 2) != 0 || !isdigit(newUser.contact_details[2])) {
            printf("Contact details must start with '01' and be 11 digits long. Please try again: ");
        }
    } while (strlen(newUser.contact_details) != 11 || strncmp(newUser.contact_details, "01", 2) != 0 || !isdigit(newUser.contact_details[2]));

    fseek(file, 0, SEEK_END);
    fwrite(&newUser, sizeof(struct User), 1, file);
    fclose(file);

    printf("User information saved successfully!\n");
}

void displayUserInfo(int searchID) {
    system("cls");

    FILE* file;
    errno_t err = fopen_s(&file, "user.bin", "rb");
    if (err != 0) {
        printf("Error opening file!\n");
        return 0;
    }

    struct User currentUser;
    int found = 0;

    while (fread(&currentUser, sizeof(struct User), 1, file)) {
        if (currentUser.ID == searchID) {
            found = 1;
            printf("=========================================\n");
            printf("ID                : %d\n", currentUser.ID);
            printf("Name              : %s\n", currentUser.name);
            printf("Gender            : %c\n", currentUser.gender);
            printf("IC Number         : %s\n", currentUser.ic_num);
            printf("Contact Details   : %s\n", currentUser.contact_details);
            printf("=========================================\n");
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("User with ID %d not found.\n", searchID);
        return 0;
    }
    return 1;
}

void displayAllUserInfo() {
    FILE* file;
    errno_t err = fopen_s(&file, "user.bin", "rb");
    if (err != 0) {
        printf("Error opening file for reading!\n");
        return;
    }

    printf("User Information\n");
    printf("==============================================================================\n");
    printf("| %-7s | %-20s | %-7s | %-14s | %-12s |\n", "ID", "Name", "Gender", "IC Number", "Contact");
    printf("==============================================================================\n");

    fseek(file, 0, SEEK_SET);

    struct User currentUser;
    int deletedCount = 0;
    while (fread(&currentUser, sizeof(struct User), 1, file)) {
        if (currentUser.ID != -1) {
            printf("| %-5d | %-20s | %-7c | %-14s | %-12s |\n", currentUser.ID - deletedCount, currentUser.name, currentUser.gender, currentUser.ic_num, currentUser.contact_details);
        }
        else {
            deletedCount++;
        }
    }

    printf("==============================================================================\n");

    fclose(file);
}

void deleteUser(int userID) {
    FILE* file;
    FILE* tempFile;
    errno_t err = fopen_s(&file, "user.bin", "rb");
    if (err != 0) {
        printf("Error opening file for reading!\n");
        return;
    }

    err = fopen_s(&tempFile, "temp.bin", "wb");
    if (err != 0) {
        printf("Error opening temp file for writing!\n");
        fclose(file);
        return;
    }

    struct User currentUser;
    int found = 0;

    while (fread(&currentUser, sizeof(struct User), 1, file)) {
        if (currentUser.ID == userID) {
            found = 1;
            continue;
        }
        fwrite(&currentUser, sizeof(struct User), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("User with ID %d not found.\n", userID);
        remove("temp.bin");
        return;
    }

    remove("user.bin");
    rename("temp.bin", "user.bin");

    printf("User with ID %d removed successfully.\n", userID);
    printf("\nPress Enter to continue...");
    getchar();

    return;
}
