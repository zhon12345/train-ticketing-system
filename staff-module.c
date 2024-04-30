#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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
		printf("Login successful. Welcome, %s!\n", staff[i].employeeName);
	}
	else {
		printf("Invalid Employee ID or password.\n");
	}
	return isAuthenticated;
}

void staffAdd() 
{
	Staff info;
	FILE* fptr = fopen("staff.bin", "ab"); // Open in binary append mode

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

void staffModify()
{
	Staff staff[size];
	int count = 0, i, found = 0;
	char enteredID[10];

	FILE* fptr = fopen("staff.bin", "rb+"); 

	if (fptr == NULL) {
		printf("Error opening file.\n");
		return;
	}

	while (fread(&staff[count], sizeof(Staff), 1, fptr) == 1) {
		count++;
	}

	printf("Enter the Employee ID to modify: ");
	rewind(stdin);
	scanf("%s", enteredID);

	for (i = 0; i < count; i++) {
		if (strcmp(staff[i].employeeID, enteredID) == 0) {
			found = 1;
			break;
		}
	}

	if (found) {
		printf("Enter new details to modify (leave unchanged for no modification):\n");
		printf("Enter employee name (current: %s): ", staff[i].employeeName);
		rewind(stdin);
		scanf("%[^\n]", &staff[i].employeeName);

		printf("Enter employee gender (current: %c): ", staff[i].gender);
		rewind(stdin);
		scanf(" %c", &staff[i].gender);

		printf("Enter employee age (current: %d): ", staff[i].age);
		scanf("%d", &staff[i].age);

		printf("Enter your new password (leave blank for no change): ");
		rewind(stdin);
		scanf("%[^\n]", &staff[i].password);

		printf("Enter your new position (leave blank for no change): ");
		rewind(stdin);
		scanf("%[^\n]", &staff[i].position);

		fseek(fptr, i * sizeof(Staff), SEEK_SET);

		fwrite(&staff[i], sizeof(Staff), 1, fptr);

		printf("Employee details modified successfully.\n");
	}
	else	{
		printf("Employee not found.\n");
	}
	fclose(fptr);
	}
 
void staffDelete()
{
	Staff staff[size];
	int count = 0, i, found = 0;
	char enteredID[10];

	FILE* fptr = fopen("staff.bin", "rb");

	if (fptr == NULL) {
		printf("Error opening file for reading.\n");
		return;
	}

	while (fread(&staff[count], sizeof(Staff), 1, fptr) == 1) {
		count++;
	}
	fclose(fptr);

	printf("Enter the Employee ID to delete: ");
	rewind(stdin);
	scanf("%s", enteredID);

	for (i = 0; i < count; i++) {
		if (strcmp(staff[i].employeeID, enteredID) == 0) {
			found = 1;
			break;
		}
	}

	if (found) {
		for (i = found; i < count - 1; i++) {
			staff[i] = staff[i + 1];
		}
		count--;

		fptr = fopen("staff.bin", "wb");
		if (fptr == NULL) {
			printf("Error opening file for writing.\n");
			return;
		}

		fwrite(staff, sizeof(Staff), count, fptr);
		fclose(fptr);

		printf("Employee deleted successfully.\n");
	}
	else {
		printf("Employee not found.\n");
	}
}
