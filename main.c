#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

struct Ticket {
    char destination[50];
    char trainID[6];
    char departureDate[11];
    double price;
};

void staff();
void staffView();
void staffAdd();
void staffEdit();
void staffDelete();

void member();
void memberBuy();
void memberView();
void memberEdit();
void memberDelete();

void displayHeader();

void main() {
    int choice;
    do {
        printf("\nTicket Booking Module:\n1. Staff\n2. Member\n3. Exit\n\nEnter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                staff();
                break;

            case 2:
                member();
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

void staff() {
    int choice;
    do {
        printf("\nStaff Menu:\n1. View Tickets\n2. Add Ticket\n3. Edit Ticket\n4. Delete Ticket\n5. Back\n\nEnter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                staffView();
                break;
            case 2:
                staffAdd();
                break;
            case 3:
                staffEdit();
                break;
            case 4:
                staffDelete();
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
    } while (choice != 5);
}

void staffView() {
    struct Ticket ticket;
    FILE *ptr = fopen("tickets.txt", "r");
    if (ptr == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    displayHeader();

    int count = 0;
    while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%lf\n", &ticket.destination, &ticket.trainID, &ticket.departureDate, &ticket.price) != EOF) {
        count++;
        printf("%2d  %-15s %-10s %-15s %.2lf\n", count, ticket.destination, ticket.trainID, ticket.departureDate, ticket.price);
    }

    if (count == 0) {
        printf("No records found.\n");
    }
    fclose(ptr);
}

void staffAdd() {
    struct Ticket ticket;
    FILE *ptr = fopen("tickets.txt", "a");
    if (ptr == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    char prompt;

    do {
        printf("Enter destination (eg. Kuala Lumpur): ");
        rewind(stdin);
        gets(ticket.destination);

        printf("Enter train ID (eg. T1001): ");
        rewind(stdin);
        gets(ticket.trainID);

        printf("Enter departure date (eg. 21/01/2024): ");
        rewind(stdin);
        gets(ticket.departureDate);

        printf("Enter price (eg. 100.00): ");
        rewind(stdin);
        scanf("%lf", &ticket.price);

        printf("Confirm ticket (y/n)? ");
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

void staffEdit() {
    struct Ticket ticket[50];

    FILE *ptr = fopen("tickets.txt", "r");
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
        char destination[50], trainID[6], departureDate[11];
        double price;
        int id;

        staffView();

        printf("\nEnter No. to edit: ");
        rewind(stdin);
        scanf("%d", &id);

        for (int i = 0; i < count; i++) {
            if (i == id - 1) {
                printf("\nEnter destination (eg. Kuala Lumpur): ");
                rewind(stdin);
                gets(destination);

                printf("Enter train ID (eg. T1001): ");
                rewind(stdin);
                gets(trainID);

                printf("Enter departure date (eg. 21/01/2024): ");
                rewind(stdin);
                gets(departureDate);

                printf("Enter price (eg. 100.00): ");
                rewind(stdin);
                scanf("%lf", &price);

                printf("Confirm update (y/n)? ");
                rewind(stdin);
                char confirm = tolower(getchar());
                if (confirm == 'y') {
                    strcpy(ticket[i].destination, destination);
                    strcpy(ticket[i].trainID, trainID);
                    strcpy(ticket[i].departureDate, departureDate);
                    ticket[i].price = price;
                } else {
                    printf("Update cancelled!");
                }
            }
        }

        printf("\nContinue editing (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());

    } while (prompt != 'n');

    FILE *ptrWrite = fopen("tickets.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(ptr, "%s|%s|%s|%.2lf\n", ticket[i].destination, ticket[i].trainID, ticket[i].departureDate, ticket[i].price);
    }

    printf("\nUpdate successful!\n");
    fclose(ptrWrite);
}

void staffDelete() {
    printf("\nUnder construction!\n");
}

void member() {
    printf("\nUnder construction!\n");
}

void displayHeader() {
    printf("\n%-3s %-15s %-10s %-15s %s\n", "No.", "Destination", "Train ID", "Departure Date", "Price");
    printf("%-3s %-15s %-10s %-15s %s\n", "===", "===============", "==========", "===============", "==========");
}