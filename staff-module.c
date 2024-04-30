#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)

#define size 100

void staffMain();
void modeSelection();
bool staffLogin();
void staffAdd();
void staffDisplay();
void staffModify();
void staffDelete();
void staffPassRecovery();

typedef struct{
	char employeeID[10], employeeName[40], password[20], passRecovery[20], position[30], gender;
	int age;
}Staff;

void staffMain()
{
	printf("_____Welcome to Adminstration Page._____\n");
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

bool staffLogin() {
	FILE* file = fopen("staff.bin", "rb");

	if (file == NULL) {
		printf("Error opening file\n");
		return false;
	}

	Staff staff[size];
	int count = 0;

	while (fscanf(file, "%s %s %s %s %s %c %d", staff[count].employeeID, staff[count].employeeName,
		staff[count].password, staff[count].passRecovery, staff[count].position, &staff[count].gender, &staff[count].age) == 7) {
		count++;
	}

	fclose(file);

	char enteredID[10], enteredPassword[20];
	printf("Enter your Employee ID: ");
	scanf("%s", enteredID);
	printf("Enter your password: ");
	scanf("%s", enteredPassword);

	bool isAuthenticated = false;
	for (int i = 0; i < count; i++) {
		if (strcmp(enteredID, staff[i].employeeID) == 0 && strcmp(enteredPassword, staff[i].password) == 0) {
			isAuthenticated = true;
			break;
		}
	}

	if (isAuthenticated) {
		printf("Login successful. Welcome, %s!\n", staff[i].employeeName); // Use the name of the logged-in staff
	}
	else {
		printf("Invalid Employee ID or password.\n");
	}
	return isAuthenticated;
}

void staffAdd()
{
	Staff info;
	FILE * fptr = fopen("employeeInfo.txt", "a"); // Append mode to add

	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	printf("Enter employee ID:");
	rewind(stdin);
	scanf("%[^\n]", &info.employeeID);

	printf("Enter employee name:");
	rewind(stdin);
	scanf("%[^\n]", &info.employeeName);

	printf("Enter employee gender:");
	rewind(stdin);
	scanf(" %c", &info.gender); // Space before %c to avoid newline issues

	printf("Enter employee age:");
	rewind(stdin);
	scanf("%d", &info.age);

	printf("Enter your password etc(john123):");
	rewind(stdin);
	scanf("%[^\n]", &info.password);

	printf("Enter your position:");
	rewind(stdin);
	scanf("%[^\n]", &info.position);

	if (fprintf(fptr, "%s %s %c %d %s %s\n", info.employeeID, info.employeeName, info.gender, info.age, info.password, info.position) != 6) {
		printf("Error writing to file.\n");
	}

	printf("\n");
	printf("Employee added sucessfully!\n");
	printf("\n");

	fclose(fptr);
}

void staffDisplay() {
	Staff info;
	FILE* fptr = fopen("staff.bin", "ab");

	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	printf("Enter employee ID:");
	rewind(stdin);
	scanf("%[^\n]", &info.employeeID);

	printf("Enter employee name:");
	rewind(stdin);
	scanf("%[^\n]", &info.employeeName);

	printf("Enter employee gender:");
	rewind(stdin);
	scanf(" %c", &info.gender); 

	printf("Enter employee age:");
	rewind(stdin);
	scanf("%d", &info.age);

	printf("Enter your password etc(john123):");
	rewind(stdin);
	scanf("%[^\n]", &info.password);

	printf("Enter your position:");
	rewind(stdin);
	scanf("%[^\n]", &info.position);

	fwrite(&info, sizeof(Staff), 1, fptr);
	if (ferror(fptr)) {
		printf("Error writing to file.\n");
	}
	else {
		printf("\n");
		printf("Employee added sucessfully!\n");
		printf("\n");
	}

	fclose(fptr);
}
