#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void staffMain();
void modeSelection();
void staffLogin();
void staffInformation();
void staffAdd();
void staffDisplay();
void staffModify();
void staffDelete();
void staffPassRecovery();

typedef struct {
	char employeeID[10], employeeName[40], password[20], passRecovery[20], position[30], gender;
	int age;
}Staff;

void staffMain()
{
	printf("_____Welcome to Adminstration Page._____\n");
	staffLogin();
	modeSelection();
	
}
void modeSelection() 
{
	int choice;
	do {
		printf("Select Mode (1-8): \n");
		printf("Mode 1: Add new Staff.\n");
		printf("Mode 2: Display Staff.\n");
		printf("Mode 3: Modify Staff Details.\n");
		printf("Mode 4: Delete Staff.\n");
		printf("Mode 5: Password Recovery\n");
		printf("Enter 6 to exit the program.\n\n");
		printf("Enter you selection:");
		rewind(stdin);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			staffAdd();
			break;
		case 2:
			staffDisplay();
			break;
		case 3:
			staffModify();
			break;
		case 4:
			staffDelete();
			break;
		case 5:
			staffPassRecovery();
			break;
		case 6:
			exit(-1);
		default:
			printf("Invalid mode selection, please enter again.\n\n");
		}
	} while (choice != 6);
};

void staffLogin()
{
    FILE* file = fopen("staff.bin", "r");
    if (file == NULL) {
        printf("Error opening file");
        return -1;
    }

    Staff staff[2];
    int count = 0;

    while (fscanf(file, "%s %s", staff[count].employeeID, staff[count].password) == 2) {
        count++;
        if (count >= 2) {
            break;
        }
    }
    fclose(file);

    char enteredID[10], enteredPassword[20];
    printf("Enter your Employee ID: ");
    scanf("%s", enteredID);
    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    int i, isAuthenticated = 0;
    for (i = 0; i < count; i++) {
        if (strcmp(enteredID, staff[i].employeeID) == 0 && strcmp(enteredPassword, staff[i].password) == 0) {
            isAuthenticated = 1;
            break;
        }
    }

    if (isAuthenticated) {
        printf("Login successful. Welcome, %s!\n", staff[i].employeeName);
    }
    else {
        printf("Invalid Employee ID or password.\n");
    }

    return 0;
}

void staffAdd()
{
	Staff info[size];
	FILE * fptr;
	fptr = fopen("employeeInfo.txt", "a");
	int i = 0;

	if (fptr == NULL)
	{
		printf("Error opening file.");
		exit(-1);
	}

	char nextEmployee;

	do {

		printf("Enter employee ID:");
		rewind(stdin);
		scanf("%[^\n]", &info[i].employeeID);

		printf("Enter employee name:");
		rewind(stdin);
		scanf("%[^\n]", &info[i].employeeName);

		printf("Enter employee gender:");
		rewind(stdin);
		scanf("%c", &info[i].gender);

		printf("Enter employee age:");
		rewind(stdin);
		scanf("%d", &info[i].age);

		printf("Enter your password etc(john123):");
		rewind(stdin);
		scanf("%[^\n]", &info[i].password);

		printf("Enter your position:");
		rewind(stdin);
		scanf("%[^\n]", &info[i].position);

		fprintf(fptr, "%s %s %c %d %s %s\n", info[i].employeeID, info[i].employeeName, info[i].gender, info[i].age, info[i].password, info[i].position);
		printf("\n");	
		printf("Employee added sucessfully!\n");
		printf("\n");
		printf("Next employee?( Y for yes N for no ): ");
		rewind(stdin);
		scanf("%c", &nextEmployee);

		nextEmployee = toupper(nextEmployee);

	} while (nextEmployee == 'Y');

	fclose(fptr);
}
