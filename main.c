#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define SIZE 100

struct TrainSchedule {
    char trainID[11];
    char departureStation[50];
    char arrivalStation[50];
    int NumberOfSeats;
    char departureTime[11];
    char arrivalTime[11];
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

    char prompt;

    do {
        printf("\nEnter Train ID (eg. T1001): ");
        rewind(stdin);
        gets(schedule.trainID);

        printf("Enter Departure Station: ");
        rewind(stdin);
        gets(schedule.departureStation);

        printf("Enter Arrival Station: ");
        rewind(stdin);
        gets(schedule.arrivalStation);

        printf("Enter number of seats: ");
        rewind(stdin);
        scanf("%d", &schedule.NumberOfSeats);

        printf("Enter Departure Time (eg. 07:00): ");
        rewind(stdin);
        gets(schedule.departureTime);

        printf("Enter Arrival Time (eg. 12:00): ");
        rewind(stdin);
        gets(schedule.arrivalTime);

        printf("\nConfirm add schedule (y/n)? ");
        rewind(stdin);
        char confirm = tolower(getchar());

        if (confirm == 'y') {
            fprintf(ptr, "%s|%s|%s|%s|%s|%d\n", schedule.trainID, schedule.departureStation, schedule.arrivalStation, schedule.departureTime, schedule.arrivalTime, schedule.NumberOfSeats);
        } else {
            printf("\nAdd schedule cancel.\n");
        }
        printf("\nAdd more schedule (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());
    } while (prompt != 'n');

    fclose(ptr);
    displaySchedule();
    system("pause");
}

void editSchedule() {
    struct TrainSchedule schedule[SIZE];
    FILE* fptr = fopen("schedule.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        exit(-1);
    }

    int count = 0;
    while (fscanf(fptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", &schedule[count].trainID, &schedule[count].departureStation, &schedule[count].arrivalStation, &schedule[count].departureTime, &schedule[count].arrivalTime, &schedule[count].NumberOfSeats) != EOF) {
        count++;
    }
    fclose(fptr);

    char prompt;
    do {
        int id;
        char trainID[11], departureStation[50], arrivalStation[50], departureTime[11], arrivalTime[11];
        int NumberOfSeats;

        printf("\nEnter number row to edit: ");
        rewind(stdin);
        scanf("%d", &id);

        if (id != 0) {
            if (id < 1 || id > count) {
                printf("\nNo record found!\n");
            } else {
                printf("\nEnter Train ID (eg. T1001): ");
                rewind(stdin);
                gets(trainID);

                printf("Enter Departure Station: ");
                rewind(stdin);
                gets(departureStation);

                printf("Enter Arrival Station: ");
                rewind(stdin);
                gets(arrivalStation);

                printf("Enter number of seats: ");
                rewind(stdin);
                scanf("%d", &NumberOfSeats);

                printf("Enter Departure Time (eg. 07:00): ");
                rewind(stdin);
                gets(departureTime);

                printf("Enter Arrival Time (eg. 12:00): ");
                rewind(stdin);
                gets(arrivalTime);

                printf("Confirm update (y/n)? ");
                rewind(stdin);
                char confirm = tolower(getchar());
                if (confirm == 'y') {
                    strcpy(schedule[id - 1].trainID, trainID);
                    strcpy(schedule[id - 1].departureStation, departureStation);
                    strcpy(schedule[id - 1].arrivalStation, arrivalStation);
                    schedule[id - 1].NumberOfSeats = NumberOfSeats;
                    strcpy(schedule[id - 1].departureTime, departureTime);
                    strcpy(schedule[id - 1].arrivalTime, arrivalTime);

                    printf("\nSchedule updated successfully!\n");

                    FILE* tempFptr = fopen("temp_schedule.txt", "w");
                    if (tempFptr == NULL) {
                        printf("Error opening temp file.\n");
                        exit(-1);
                    }

                    for (int i = 0; i < count; i++) {
                        fprintf(tempFptr, "%s|%s|%s|%s|%s|%d\n", schedule[i].trainID, schedule[i].departureStation, schedule[i].arrivalStation, schedule[i].departureTime, schedule[i].arrivalTime, schedule[i].NumberOfSeats);
                    }

                    fclose(tempFptr);

                    if (remove("schedule.txt") != 0) {
                        printf("Error deleting original file.\n");
                        exit(-1);
                    }

                    if (rename("temp_schedule.txt", "schedule.txt") != 0) {
                        printf("Error renaming file.\n");
                        exit(-1);
                    }
                } else {
                    printf("\nSchedule not found.\n");
                }
                printf("\nContinue editing (y/n)? ");
                rewind(stdin);
                prompt = tolower(getchar());
            }
        }
    } while (prompt != 'n');
}

void deleteSchedule() {
    char prompt;
    int id;
    do {
        struct TrainSchedule schedule[SIZE];
        FILE* ptr = fopen("schedule.txt", "r");
        if (ptr == NULL) {
            printf("Error opening file.\n");
            exit(-1);
        }

        int count = 0;
        while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", &schedule[count].trainID, &schedule[count].departureStation, &schedule[count].arrivalStation, &schedule[count].departureTime, &schedule[count].arrivalTime, &schedule[count].NumberOfSeats) != EOF) {
            count++;
        }
        fclose(ptr);

        printf("\nEnter number row to delete (0 to exit): ");
        scanf("%d", &id);

        if (id != 0) {
            if (id < 1 || id > count) {
                printf("\nInvalid row number!\n");
            } else {
                FILE* ptrDelete = fopen("temp_schedule.txt", "w");
                if (ptrDelete == NULL) {
                    printf("Error opening temp file.\n");
                    exit(-1);
                }

                for (int i = 0; i < count; i++) {
                    if (id - 1 == i) {
                        printf("\nTrain Schedule\n");
                        printf("----------------------------------------------------------------------------------------------------\n");
                        printf("| Train ID | Departure Station | Arrival Station | Departure Time | Arrival Time | Available Seats |\n");
                        printf("----------------------------------------------------------------------------------------------------\n");
                        printf(" | %-8s | %-17s | %-14s | %-14s | %-12s | %-15d |\n", schedule[i].trainID, schedule[i].departureStation, schedule[i].arrivalStation, schedule[i].departureTime, schedule[i].arrivalTime, schedule[i].NumberOfSeats);

                        printf("\nConfirm delete (y/n)? ");
                        rewind(stdin);
                        char confirm = getchar();
                        if (confirm == 'y' || confirm == 'Y') {
                            printf("\nSchedule deleted successfully\n");
                        } else {
                            printf("\nSchedule not deleted.\n");
                            fprintf(ptrDelete, "%s|%s|%s|%s|%s|%d\n", schedule[i].trainID, schedule[i].departureStation, schedule[i].arrivalStation, schedule[i].departureTime, schedule[i].arrivalTime, schedule[i].NumberOfSeats);
                        }
                    } else {
                        fprintf(ptrDelete, "%s|%s|%s|%s|%s|%d\n", schedule[i].trainID, schedule[i].departureStation, schedule[i].arrivalStation, schedule[i].departureTime, schedule[i].arrivalTime, schedule[i].NumberOfSeats);
                    }
                }
                fclose(ptrDelete);

                if (remove("schedule.txt") != 0) {
                    printf("Error deleting original file.\n");
                    exit(-1);
                }

                if (rename("temp_schedule.txt", "schedule.txt") != 0) {
                    printf("Error renaming file.\n");
                    exit(-1);
                }
            }
        }

        printf("\nContinue deleting (y/n)? ");
        while (getchar() != '\n')
            ;
        prompt = getchar();

    } while (prompt == 'y' || prompt == 'Y');
}

void displaySchedule() {
    struct TrainSchedule schedule;
    FILE* ptr = fopen("schedule.txt", "r");
    if (ptr == NULL) {
        printf("Error opening file.\n");
        exit(-1);
    }

    printf("\nTrain Schedule\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("| Train ID | Departure Station | Arrival Station | Departure Time | Arrival Time | Available Seats |\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    int count = 0;
    while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", &schedule.trainID, &schedule.departureStation, &schedule.arrivalStation, &schedule.departureTime, &schedule.arrivalTime, &schedule.NumberOfSeats) != EOF) {
        count++;
        printf(" %-10s %-20s %-20s %-14s %-14s %-15d\n", schedule.trainID, schedule.departureStation, schedule.arrivalStation, schedule.departureTime, schedule.arrivalTime, schedule.NumberOfSeats);
    }

    if (count == 0) {
        printf("No schedules found!\n");
    }
    fclose(ptr);
}

void searchSchedule() {
    char searchID[11];
    printf("Enter Train ID to search: ");
    rewind(stdin);
    gets(searchID);

    struct TrainSchedule schedule;
    int found = 0;

    FILE* ptr = fopen("schedule.txt", "r");
    if (ptr == NULL) {
        printf("Error opening file.\n");
        exit(-1);
    }

    printf("\nSearch Result\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("| Train ID | Departure Station | Arrival Station | Departure Time | Arrival Time | Available Seats |\n");
    printf("----------------------------------------------------------------------------------------------------\n");

    while (fscanf(ptr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", &schedule.trainID, &schedule.departureStation, &schedule.arrivalStation, &schedule.departureTime, &schedule.arrivalTime, &schedule.NumberOfSeats) != EOF) {
        if (strcmp(schedule.trainID, searchID) == 0) {
            printf("| %-8s | %-17s | %-14s | %-14s | %-12s | %-15d |\n", schedule.trainID, schedule.departureStation, schedule.arrivalStation, schedule.departureTime, schedule.arrivalTime, schedule.NumberOfSeats);
            found = 1;
        }
    }

    if (!found) {
        printf("No schedules found for Train ID: %s\n", searchID);
    }

    fclose(ptr);

    printf("\nPress Enter to return to the main menu...");
    while (getchar() != '\n')
        ;
    getchar();
}

void main() {
    scheduleMenu();
    return 0;
}
