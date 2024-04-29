#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)

typedef struct {
    char ID[7];
    char username[50];
    char password[50];
    char gender;
    char ic_num[13];
    char phoneNo[12];
} User;

struct Ticket {
    char destination[50];
    char trainID[6];
    char departureDate[11];
    char departureTime[6];
    double price;
};

typedef struct {
    char bookingID[6];
    char memberID[7];
    char bookingDate[11];
    struct Ticket ticket;
    char seats[4][5];
    int quantity;
    double total;
    char status[20];
} MemberTickets;

// Member Functions
void member();
void newMember();
void memberLogin();
void memberInfo(User);

void buyTicket(User);
void viewTickets(User);

// Staff Functions
void staff();
void memberMenu();
void displayMembers();
void deleteMember();

void ticketMenu();
void addTicket();
void editTicket();
void deleteTicket();

// Misc Functions
void generateID(char, int, char*);
void memberHeader();
void ticketHeader();
void displayTickets();

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
    } while (choice != 3);
    system("pause");
}

void member() {
    int choice;
    do {
        system("cls");
        printf(" _   _               ___               _\n");
        printf("| | | |___ ___ _ _  | _ \\__ _ _ _  ___| |\n");
        printf("| |_| (_-</ -_) '_| |  _/ _` | ' \\/ -_) |\n");
        printf(" \\___//__/\\___|_|   |_| \\__,_|_||_\\___|_|\n\n");

        printf("1. Login\n2. Register\n3. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                memberLogin();
                break;
            case 2:
                newMember();
                break;
            case 3:
                break;
            default:
                printf("\nInvalid option!\n");
                system("pause");
                break;
        }
    } while (choice != 3);
}

void staff() {
    int choice;
    do {
        system("cls");
        printf(" ___ _         __  __   ___               _\n");
        printf("/ __| |_ __ _ / _|/ _| | _ \\__ _ _ _  ___| |\n");
        printf("\\__ \\  _/ _` |  _|  _| |  _/ _` | ' \\/ -_) |\n");
        printf("|___/\\__\\__,_|_| |_|   |_| \\__,_|_||_\\___|_|\n\n");

        printf("1. User Management\n2. Staff Management\n3. Schedule Management\n4. Ticket Management\n5. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                memberMenu();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                ticketMenu();
                break;
            case 5:
                break;
            default:
                printf("\nInvalid option!\n");
                system("pause");
                break;
        }
    } while (choice != 5);
}

// Member Functions
void newMember() {
    User newUser, existingUser;

    system("cls");
    printf("Member Registration\n=====================\n");

    FILE* file = fopen("user.bin", "ab+");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    generateID('M', 6, newUser.ID);

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
        scanf("%[^\n]", &newUser.password);

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

void memberLogin() {
    User currentUser;
    char username[50], password[50];

    FILE* file = fopen("user.bin", "rb");
    if (file == NULL) {
        printf("\nNo registered user!\n");
        system("pause");
        return;
    }

    printf("\nEnter Username: ");
    rewind(stdin);
    scanf("%[^\n]", &username);

    printf("Password: ");
    rewind(stdin);
    scanf("%[^\n]", &password);

    int found = 0;
    while (fread(&currentUser, sizeof(User), 1, file)) {
        if (strcmp(currentUser.username, username) == 0 && strcmp(currentUser.password, password) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        int choice;

        do {
            system("cls");
            printf("Welcome %s, what would you like to do?\n\n", currentUser.username);
            printf("1. View User Information\n2. Buy Tickets\n3. View My Tickets\n4. Logout\n\n");

            printf("Enter option: ");
            rewind(stdin);
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    memberInfo(currentUser);
                    system("pause");
                    break;
                case 2:
                    buyTicket(currentUser);
                    system("pause");
                    break;
                case 3:
                    viewTickets(currentUser);
                    system("pause");
                    break;
                case 4:
                    break;
                default:
                    printf("\nInvalid option!\n");
                    system("pause");
                    break;
            }
        } while (choice != 4);
    } else {
        printf("\nInvalid Username or password.\n");
        system("pause");
    }
    fclose(file);
}

void memberInfo(User currentUser) {
    char choice;
    printf("\nUser Information\n");
    printf("==========================\n");
    printf("Name: %s\n", currentUser.username);
    printf("Gender: %c\n", currentUser.gender);
    printf("IC: %s\n", currentUser.ic_num);
    printf("Contact: %s\n", currentUser.phoneNo);
    printf("==========================\n\n");

    printf("Edit User Information (y/n)? ");
    rewind(stdin);
    choice = toupper(getchar());

    if (choice == 'Y') {
        FILE* file = fopen("user.bin", "rb+");
        if (file == NULL) {
            printf("Error opening file!\n");
            exit(-1);
        }

        User updatedUser = currentUser;

        printf("Enter new gender (M/F): ");
        rewind(stdin);
        scanf(" %c", &updatedUser.gender);

        printf("Enter new IC number (DDMMYY########): ");
        rewind(stdin);
        scanf("%s", updatedUser.ic_num);

        printf("Enter new phone number (01#########): ");
        rewind(stdin);
        scanf("%s", updatedUser.phoneNo);

        fseek(file, -sizeof(User), SEEK_CUR);

        fwrite(&updatedUser, sizeof(User), 1, file);
        printf("\nUser information updated successfully.\n");

        fclose(file);

        printf("\nUpdated User Information\n");
        printf("=====================================\n");
        printf("Name: %s\n", updatedUser.username);
        printf("Gender: %c\n", updatedUser.gender);
        printf("IC: %s\n", updatedUser.ic_num);
        printf("Contact: %s\n", updatedUser.phoneNo);
        printf("=====================================\n\n");

        system("pause");
    }
}

void buyTicket(User currentUser) {
    struct Ticket ticket[50];
    MemberTickets memberTicket;

    displayTickets();

    FILE* ptrView = fopen("tickets.txt", "r");

    if (ptrView == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    int count = 0;
    while (fscanf(ptrView, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &ticket[count].destination, &ticket[count].trainID, &ticket[count].departureDate, &ticket[count].departureTime, &ticket[count].price) != EOF) {
        count++;
    }
    fclose(ptrView);

    if (count > 0) {
        int id;

        printf("\nEnter ID of ticket you'd like to buy: ");
        rewind(stdin);
        scanf("%d", &id);

        if (id < 1 || id > count) {
            printf("\nNo record found!\n");
        } else {
            do {
                printf("Enter quantity of tickets to buy (max 5): ");
                rewind(stdin);
                scanf("%d", &memberTicket.quantity);
            } while (memberTicket.quantity > 5);

            memberTicket.total = ticket[id - 1].price * memberTicket.quantity;

            char confirm;
            printf("\nGrand total: %.2lf\n", memberTicket.total);
            printf("Proceed (y/n)? ");
            rewind(stdin);
            confirm = tolower(getchar());

            if (confirm == 'y') {
                FILE* ptrWrite = fopen("memberTickets.txt", "a+");

                time_t now = time(NULL);
                struct tm* local = localtime(&now);

                int day, month, year;
                char date[11];

                day = local->tm_mday;
                month = local->tm_mon + 1;
                year = local->tm_year + 1900;

                sprintf(date, "%02d/%02d/%d", day, month, year);

                generateID('B', 5, memberTicket.bookingID);
                memberTicket.ticket = ticket[id - 1];

                strcpy(memberTicket.bookingDate, date);

                for (int i = 0; i < memberTicket.quantity; i++) {
                    char coach;
                    int seat;

                    do {
                        printf("\nEnter desired seat for ticket %d (coach: A-F, seat: 1-48) eg. A14: ", i + 1);
                        rewind(stdin);
                        scanf("%c%d", &coach, &seat);

                        coach = toupper(coach);
                    } while ((coach < 'A' || coach > 'F') || (seat < 1 || seat > 48));

                    sprintf(memberTicket.seats[i], "%c%02d", coach, seat);
                }

                strcpy(memberTicket.status, "Booked");

                fprintf(ptrWrite, "%s|%s|%s|%s|%s|%s|", currentUser.ID, memberTicket.bookingID, memberTicket.ticket.destination, memberTicket.ticket.trainID, memberTicket.ticket.departureDate, memberTicket.ticket.departureTime, memberTicket.bookingDate);

                for (int i = 0; i < memberTicket.quantity; i++) {
                    fprintf(ptrWrite, "%s", memberTicket.seats[i]);
                    if (i < memberTicket.quantity - 1) {
                        fprintf(ptrWrite, ",");
                    }
                }

                fprintf(ptrWrite, "|%d|%.2lf|%s\n", memberTicket.quantity, memberTicket.total, memberTicket.status);

                printf("Booking Successful!\n");
                fclose(ptrWrite);
            }
        }
    }
}

void viewTickets(User currentUser) {
    MemberTickets memberTicket;

    printf("\n%-15s %-15s %-10s %-10s %-15s %-15s %-15s %-10s %s\n", "Booking ID", "Destination", "Train ID", "Seat(s)", "Departure Date", "Departure Time", "Booking Date", "Total", "Status");
    printf("========================================================================================================================\n");

    FILE* ptr = fopen("memberTickets.txt", "r");
    if (ptr == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%lf|%s\n", &memberTicket.memberID, &memberTicket.bookingID, &memberTicket.ticket.destination, &memberTicket.ticket.trainID, &memberTicket.ticket.departureDate, &memberTicket.ticket.departureTime, &memberTicket.bookingDate, &memberTicket.seats, &memberTicket.quantity, &memberTicket.total, &memberTicket.status) != EOF) {
        if (strcmp(memberTicket.memberID, currentUser.ID) == 0) {
            printf("%-15s %-15s %-10s %-10s %-15s %-15s %-15s %-10.2lf %s\n", memberTicket.bookingID, memberTicket.ticket.destination, memberTicket.ticket.trainID, memberTicket.seats, memberTicket.ticket.departureDate, memberTicket.ticket.departureTime, memberTicket.bookingDate, memberTicket.total, memberTicket.status);
        } else {
            printf("No records found.\n");
        }
    }
    fclose(ptr);
    int choice;
    do {
        printf("\nWhat would you like to do? \n\n");
        printf("1. Change Time\n2. Cancel Ticket\n3. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("\nInvalid option!\n");
                system("pause");
                break;
        }
    } while (choice != 3);
}

// Staff Functions
void memberMenu() {
    int choice;
    do {
        system("cls");
        printf("GS Train System Member Management\n\n");
        printf("1. View Members\n2. Delete Members\n3. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewMembers();
                system("pause");
                break;
            case 2:
                deleteMembers();
                break;
            case 3:
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
    } while (choice != 3);
}

void viewMembers() {
    User users;
    FILE* file = fopen("user.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    memberHeader();

    while (fread(&users, sizeof(User), 1, file)) {
        printf("%-10s %-20s %-7c %-14s %s\n", users.ID, users.username, users.gender, users.ic_num, users.phoneNo);
    }

    fclose(file);
}

void deleteMembers() {
    char prompt;
    do {
        User member[50];

        FILE* ptr = fopen("user.bin", "rb");
        if (ptr == NULL) {
            printf("An error occurred, please try again!\n");
            exit(-1);
        }

        int count = 0;
        while (fread(&member[count], sizeof(User), 1, ptr)) {
            count++;
        }
        fclose(ptr);

        viewMembers();

        FILE* ptrDelete = fopen("user.bin", "wb");
        char id[7];

        printf("\nEnter ID to delete: ");
        rewind(stdin);
        scanf("%s", &id);

        for (int i = 0; i < count; i++) {
            if (strcmp(id, member[i].ID) == 0) {
                memberHeader();
                printf("%-10s %-20s %-7c %-14s %s\n", member[i].ID, member[i].username, member[i].gender, member[i].ic_num, member[i].phoneNo);

                printf("\nConfirm delete (y/n)? ");
                rewind(stdin);
                char confirm = tolower(getchar());
                if (confirm == 'y') {
                } else {
                    printf("\nUpdate cancelled!\n");
                    fwrite(&member[i], sizeof(User), 1, ptrDelete);
                }
            } else {
                fwrite(&member[i], sizeof(User), 1, ptrDelete);
            }
        }
        fclose(ptrDelete);

        printf("\nContinue deleting (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());
    } while (prompt == 'y');
}

void ticketMenu() {
    int choice;
    do {
        system("cls");
        printf("GS Train System Ticket Management\n\n");
        printf("1. View Tickets\n2. Add Ticket\n3. Edit Ticket\n4. Delete Ticket\n5. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayTickets();
                system("pause");
                break;
            case 2:
                addTicket();
                break;
            case 3:
                editTicket();
                break;
            case 4:
                deleteTicket();
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
    } while (choice != 5);
}

void addTicket() {
    struct Ticket ticket;
    FILE* ptr = fopen("tickets.txt", "a");
    if (ptr == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    char prompt;

    do {
        printf("\nEnter destination (eg. Kuala Lumpur): ");
        rewind(stdin);
        gets(ticket.destination);

        printf("Enter train ID (eg. T1001): ");
        rewind(stdin);
        gets(ticket.trainID);

        printf("Enter departure date (eg. 21/01/2024): ");
        rewind(stdin);
        gets(ticket.departureDate);

        printf("Enter departure time (eg. 07:00): ");
        rewind(stdin);
        gets(ticket.departureTime);

        printf("Enter price (eg. 100.00): ");
        rewind(stdin);
        scanf("%lf", &ticket.price);

        printf("\nConfirm ticket (y/n)? ");
        rewind(stdin);
        char confirm = tolower(getchar());

        if (confirm == 'y') {
            fprintf(ptr, "%s|%s|%s|%.2lf\n", ticket.destination, ticket.trainID, ticket.departureDate, ticket.price);
        } else {
            printf("No changes made!\n");
        }

        printf("\nAdd more ticket (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());

    } while (prompt != 'n');
    fclose(ptr);
}

void editTicket() {
    struct Ticket ticket[50];

    FILE* ptr = fopen("tickets.txt", "r");
    if (ptr == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    int count = 0;
    while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%lf\n", &ticket[count].destination, &ticket[count].trainID, &ticket[count].departureDate, &ticket[count].price) != EOF) {
        count++;
    }
    fclose(ptr);

    char prompt;
    do {
        char destination[50], trainID[6], departureDate[11], departureTime[6];
        double price;
        int id;

        displayTickets();

        printf("\nEnter No. to edit (0 to exit): ");
        rewind(stdin);
        scanf("%d", &id);

        if (id == 0) {
            break;
        }

        if (id < 0 || id > count) {
            printf("\nNo record found!\n");
        } else {
            printf("\nEnter destination (eg. Kuala Lumpur): ");
            rewind(stdin);
            gets(destination);

            printf("Enter train ID (eg. T1001): ");
            rewind(stdin);
            gets(trainID);

            printf("Enter departure date (eg. 21/01/2024): ");
            rewind(stdin);
            gets(departureDate);

            printf("Enter departure time (eg. 07:00): ");
            rewind(stdin);
            gets(departureTime);

            printf("Enter price (eg. 100.00): ");
            rewind(stdin);
            scanf("%lf", &price);

            printf("Confirm update (y/n)? ");
            rewind(stdin);
            char confirm = tolower(getchar());
            if (confirm == 'y') {
                strcpy(ticket[id - 1].destination, destination);
                strcpy(ticket[id - 1].trainID, trainID);
                strcpy(ticket[id - 1].departureDate, departureDate);
                strcpy(ticket[id - 1].departureTime, departureTime);
                ticket[id - 1].price = price;
            } else {
                printf("\nUpdate cancelled!\n");
            }
        }

        printf("\nContinue editing (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());

    } while (prompt != 'n');

    FILE* ptrWrite = fopen("tickets.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(ptr, "%s|%s|%s|%.2lf\n", ticket[i].destination, ticket[i].trainID, ticket[i].departureDate, ticket[i].price);
    }

    fclose(ptrWrite);
}

void deleteTicket() {
    char prompt;
    int id;
    do {
        struct Ticket ticket[50];

        FILE* ptr = fopen("tickets.txt", "r");
        if (ptr == NULL) {
            printf("An error occurred, please try again!\n");
            exit(-1);
        }

        int count = 0;
        while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%lf\n", &ticket[count].destination, &ticket[count].trainID, &ticket[count].departureDate, &ticket[count].price) != EOF) {
            count++;
        }
        fclose(ptr);

        displayTickets();

        printf("\nEnter No. to delete (0 to exit): ");
        rewind(stdin);
        scanf("%d", &id);

        if (id != 0) {
            if (id < 0 || id > count) {
                printf("\nNo record found!\n");
            } else {
                FILE* ptrDelete = fopen("tickets.txt", "w");

                ticketHeader();
                printf("%2d  %-15s %-10s %-15s %.2lf\n", id, ticket[id - 1].destination, ticket[id - 1].trainID, ticket[id - 1].departureDate, ticket[id - 1].price);

                printf("\nConfirm delete (y/n)? ");
                rewind(stdin);
                char confirm = tolower(getchar());
                if (confirm == 'y') {
                } else {
                    printf("\nUpdate cancelled!\n");
                    fprintf(ptr, "%s|%s|%s|%.2lf\n", ticket[id - 1].destination, ticket[id - 1].trainID, ticket[id - 1].departureDate, ticket[id - 1].price);
                }
                fclose(ptrDelete);
            }
        }

        printf("\nContinue deleting (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());
    } while (prompt == 'y' || id == 0);
}

// Misc Functions
void generateID(char head, int length, char* id) {
    id[0] = head;
    srand(time(NULL));
    for (int i = 1; i < length; i++) {
        id[i] = '0' + rand() % 10;
    }
    id[length] = '\0';
}
void memberHeader() {
    printf("\n%-10s %-20s %-7s %-14s %s\n", "ID", "Username", "Gender", "IC Number", "Phone Number");
    printf("=========================================================================\n");
}

void ticketHeader() {
    printf("\n%-3s %-15s %-10s %-15s %-15s %s\n", "ID", "Destination", "Train ID", "Departure Date", "Departure Time", "Price");
    printf("=======================================================================\n");
}

void displayTickets() {
    struct Ticket ticket;
    FILE* ptrView = fopen("tickets.txt", "r");
    if (ptrView == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    ticketHeader();

    int count = 0;
    while (fscanf(ptrView, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &ticket.destination, &ticket.trainID, &ticket.departureDate, &ticket.departureTime, &ticket.price) != EOF) {
        count++;
        printf("%-3d %-15s %-10s %-15s %-15s %.2lf\n", count, ticket.destination, ticket.trainID, ticket.departureDate, ticket.departureTime, ticket.price);
    }

    if (count == 0) {
        printf("No records found.\n\n");
    }
    fclose(ptrView);
}
