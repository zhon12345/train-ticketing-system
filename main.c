#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define MAX_SCHEDULES 50
#define MAX_TRAIN_ID_LENGTH 6
#define MAX_STATION_LENGTH 50
#define MAX_TIME_LENGTH 6

struct TrainSchedule {
    char trainID[MAX_TRAIN_ID_LENGTH];
    char departureStation[MAX_STATION_LENGTH];
    char arrivalStation[MAX_STATION_LENGTH];
    int NumberOfSeats;
    char departureTime[MAX_TIME_LENGTH];
    char arrivalTime[MAX_TIME_LENGTH];
};

void scheduleMenu();
void addSchedule();
void editSchedule();
void deleteSchedule();
void displaySchedule();
void searchSchedule();

void scheduleMenu() {
    int choice;
    do {
        system("cls");
        printf("GS Train System Schedule Management\n\n");
        printf("1. View Schedule\n2. Add Schedule\n3. Edit Schedule\n4. Delete Schedule\n5. Search Schedule\n6. Back\n\n");

        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            displaySchedule();
            system("pause");
            break;
        case 2:
            addSchedule();
            break;
        case 3:
            editSchedule();
            break;
        case 4:
            deleteSchedule();
            break;
        case 5:
            searchSchedule();
            break;
        case 6:
            printf("\nExiting the program...\n");
            break;
        default:
            printf("\nInvalid option!\n");
            break;
        }
    } while (choice != 6);
}

void addSchedule() {
    struct TrainSchedule schedule;
    FILE* ptr = fopen("schedule.txt", "a");
    if (ptr == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    int validFormat = 0;
    while (!validFormat) {
        printf("\nEnter Train ID (eg. T1001): ");
        rewind(stdin);
        fgets(schedule.trainID, sizeof(schedule.trainID), stdin);
        schedule.trainID[strcspn(schedule.trainID, "\n")] = '\0';

        if (((schedule.trainID[0] >= 'A' && schedule.trainID[0] <= 'Z') ||
            (schedule.trainID[0] >= '0' && schedule.trainID[0] <= '9')) &&
            (strlen(schedule.trainID) >= 4 && strlen(schedule.trainID) <= 6)) {
            int digits = 0;
            for (int i = 1; i < strlen(schedule.trainID); i++) {
                if (isdigit(schedule.trainID[i])) {
                    digits++;
                }
            }
            if (digits >= 3 && digits <= 5) {
                validFormat = 1;
            }
        }
        if (!validFormat) {
            printf("Invalid Train ID format! Please enter again.\n");
        }
    }

    printf("Enter Departure Station: ");
    fgets(schedule.departureStation, sizeof(schedule.departureStation), stdin);
    schedule.departureStation[strcspn(schedule.departureStation, "\n")] = '\0';

    printf("Enter Arrival Station: ");
    fgets(schedule.arrivalStation, sizeof(schedule.arrivalStation), stdin);
    schedule.arrivalStation[strcspn(schedule.arrivalStation, "\n")] = '\0';

    printf("Enter number of seats: ");
    scanf("%d", &schedule.NumberOfSeats);
    getchar();

    printf("Enter Departure Time (eg. 07:00): ");
    fgets(schedule.departureTime, sizeof(schedule.departureTime), stdin);
    schedule.departureTime[strcspn(schedule.departureTime, "\n")] = '\0';
    getchar();

    printf("Enter Arrival Time (eg. 12:00): ");
    fgets(schedule.arrivalTime, sizeof(schedule.arrivalTime), stdin);
    schedule.arrivalTime[strcspn(schedule.arrivalTime, "\n")] = '\0';
    getchar();

    fprintf(ptr, "%s|%s|%s|%s|%s|%d\n", schedule.trainID, schedule.departureStation, schedule.arrivalStation, schedule.departureTime, schedule.arrivalTime, schedule.NumberOfSeats);
    fclose(ptr);

    printf("\nSchedule added successfully!\n");

    system("pause");
}

void editSchedule() {
    struct TrainSchedule schedule[MAX_SCHEDULES] = { 0 };
    int count = 0;

    FILE* ptr = fopen("schedule.txt", "r");
    if (ptr == NULL) {
        printf("An error occurred, please try again!\n");
        exit(-1);
    }

    while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", schedule[count].trainID, schedule[count].departureStation, schedule[count].arrivalStation, schedule[count].departureTime, schedule[count].arrivalTime) != EOF) {
        count++;
    }
    fclose(ptr);

    char prompt;
    do {
        int id;

        printf("\nEnter number row to edit (0 to exit): ");
        rewind(stdin);
        scanf("%d", &id);

        if (id == 0) {
            break;
        }

        if (id < 0 || id > count) {
            printf("\nNo record found!\n");
        }
        else {
            printf("\nEnter Train ID (eg. T1001): ");
            rewind(stdin);
            fgets(schedule[id - 1].trainID, sizeof(schedule[id - 1].trainID), stdin);
            schedule[id - 1].trainID[strcspn(schedule[id - 1].trainID, "\n")] = '\0';

            printf("Enter Departure Station: ");
            fgets(schedule[id - 1].departureStation, sizeof(schedule[id - 1].departureStation), stdin);
            schedule[id - 1].departureStation[strcspn(schedule[id - 1].departureStation, "\n")] = '\0';

            printf("Enter Arrival Station: ");
            fgets(schedule[id - 1].arrivalStation, sizeof(schedule[id - 1].arrivalStation), stdin);
            schedule[id - 1].arrivalStation[strcspn(schedule[id - 1].arrivalStation, "\n")] = '\0';

            printf("Enter Departure Time (eg. 07:00): ");
            fgets(schedule[id - 1].departureTime, sizeof(schedule[id - 1].departureTime), stdin);
            schedule[id - 1].departureTime[strcspn(schedule[id - 1].departureTime, "\n")] = '\0';
            getchar();

            printf("Enter Arrival Time (eg. 12:00): ");
            fgets(schedule[id - 1].arrivalTime, sizeof(schedule[id - 1].arrivalTime), stdin);
            schedule[id - 1].arrivalTime[strcspn(schedule[id - 1].arrivalTime, "\n")] = '\0';
            getchar();

            FILE* ptrWrite = fopen("schedule_temp.txt", "w");
            for (int i = 0; i < count; i++) {
                fprintf(ptrWrite, "%s|%s|%s|%s|%s\n", schedule[i].trainID, schedule[i].departureStation, schedule[i].arrivalStation, schedule[i].departureTime, schedule[i].arrivalTime);
            }
            fclose(ptrWrite);

            remove("schedule.txt");

            rename("schedule_temp.txt", "schedule.txt");

            printf("\nSchedule updated successfully!\n");
        }

        printf("\nContinue editing (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());

    } while (prompt != 'n');
}

void deleteSchedule() {
    struct TrainSchedule schedule[MAX_SCHEDULES] = { 0 };
    char prompt;
    int id;
    do {
        FILE* ptr = fopen("schedule.txt", "r");
        if (ptr == NULL) {
            printf("An error occurred, please try again!\n");
            exit(-1);
        }

        int count = 0;
        while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", schedule[count].trainID, schedule[count].departureStation, schedule[count].arrivalStation, schedule[count].departureTime, schedule[count].arrivalTime) != EOF) {
            count++;
        }
        fclose(ptr);

        printf("\nEnter number row to delete (0 to exit): ");
        rewind(stdin);
        scanf("%d", &id);

        if (id == 0) {
            break;
        }

        if (id < 0 || id > count) {
            printf("\nNo record found!\n");
        }
        else {
            FILE* ptrWrite = fopen("schedule_temp.txt", "w");
            for (int i = 0; i < count; i++) {
                if (i != id - 1) {
                    fprintf(ptrWrite, "%s|%s|%s|%s|%s\n", schedule[i].trainID, schedule[i].departureStation, schedule[i].arrivalStation, schedule[i].departureTime, schedule[i].arrivalTime);
                }
            }
            fclose(ptrWrite);

            printf("\nSchedule deleted successfully!\n");
        }

        printf("\nContinue deleting (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());

    } while (prompt != 'n');

    system("pause");
}

void displaySchedule() {
    FILE* ptr = fopen("schedule.txt", "r");
    if (ptr == NULL) {
        printf("No schedules found!\n");
        printf("\nPress Enter to return to the main menu...");
        while (getchar() != '\n');
        return;
    }

    printf("\nTrain Schedule\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("| Train ID | Departure Station | Arrival Station | Departure Time | Arrival Time | Available Seats |\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    struct TrainSchedule schedule;
    int found = 0;
    while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", schedule.trainID, schedule.departureStation, schedule.arrivalStation, schedule.departureTime, schedule.arrivalTime, &schedule.NumberOfSeats) == 6) {
        found = 1;
        printf("| %-8s | %-17s | %-14s | %-14s | %-12s | %-15d |\n", schedule.trainID, schedule.departureStation, schedule.arrivalStation, schedule.departureTime, schedule.arrivalTime, schedule.NumberOfSeats);
    }
    fclose(ptr);

    if (!found) {
        printf("No schedules found!\n");
    }

    printf("\nPress Enter to return to the main menu...");
    while (getchar() != '\n');

    system("pause");
}


void searchSchedule() {
    char searchID[MAX_TRAIN_ID_LENGTH];
    printf("Enter Train ID to search: ");
    rewind(stdin);
    gets(searchID);

    FILE* ptr = fopen("schedule.txt", "r");
    if (ptr == NULL) {
        printf("No schedules found!\n");
        printf("\nPress Enter to return to the main menu...");
        return;
    }

    printf("\nSearch Result\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("| Train ID | Departure Station | Arrival Station | Departure Time | Arrival Time | Available Seats |\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    struct TrainSchedule schedule;
    int found = 0;
    while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", schedule.trainID, schedule.departureStation, schedule.arrivalStation, schedule.departureTime, schedule.arrivalTime) != EOF) {
        printf(searchID);

        if (strcmp(schedule.trainID, searchID) == 0) {
            found = 1;
            printf("| %-8s | %-17s | %-14s | %-14s | %-12s | %-15d |\n", schedule.trainID, schedule.departureStation, schedule.arrivalStation, schedule.departureTime, schedule.arrivalTime, schedule.NumberOfSeats);
            break;
        }
    }
    fclose(ptr);

    printf("\nPress Enter to return to the main menu...");
    while (getchar() != '\n');

    system("pause");
}
int main() {
    scheduleMenu();
    return 0;
}
