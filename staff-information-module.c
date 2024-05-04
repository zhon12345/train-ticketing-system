#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define size 100

void modeSelection();
void staffLogin();
void staffAdd();
void staffDisplay();
void staffModify();
void staffDelete();
void staffPassRecovery();

typedef struct{
	char employeeID[10], employeeName[40], password[20], passRecovery[20], position[30], gender;
	int age;
}Staff;

void main()
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
			staffLogin();
			staffModify();
			break;
		case 4:
			staffLogin();
			staffDelete();
			break;
		case 5:
			staffPassRecovery();
			break;
		case 6:
			exit(-1);
		default:
			printf("\nInvalid mode selection, please enter again.\n\n");
		}
	} while (choice != 6);
};

void staffLogin() 
{
	char username[10];
	char password[20];

	printf("\nEnter Employee ID: ");
	scanf("%s", username);

	printf("Password: ");
	scanf("%s", password);

	FILE * file;
	errno_t err = fopen_s(&file, "staff.bin", "rb");

	if (err != 0) {
		printf("Error opening file!\n");
		return -1;
	}

	Staff currentStaff;
	int found = 0;

	while (fread(&currentStaff, sizeof(Staff), 1, file) == 1) {
		if (strcmp(currentStaff.employeeID, username) == 0 && strcmp(currentStaff.password, password) == 0) {
			found = 1;
			break;
		}
	}

	fclose(file);

	if (found == 0) {
		printf("\nInvalid Employee ID or password.\n\n");
		return 0;
	}
	printf("\nLogin successful. Welcome!\n");
}

void staffAdd()
{
	Staff info;
	FILE* fptr = fopen("staff.bin", "ab");

	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	printf("\nEnter new employee ID:");
	rewind(stdin);
	scanf("%[^\n]", &info.employeeID);

	printf("Enter new employee name:");
	rewind(stdin);
	scanf("%[^\n]", &info.employeeName);

	printf("Enter new employee gender:");
	rewind(stdin);
	scanf(" %c", &info.gender);

	printf("Enter new employee age:");
	rewind(stdin);
	scanf("%d", &info.age);

	printf("Enter new password exp (john123):");
	rewind(stdin);
	scanf("%[^\n]", &info.password);

	printf("Enter your new position:");
	rewind(stdin);
	scanf("%[^\n]", &info.position);

	fwrite(&info, sizeof(Staff), 1, fptr);
	if (ferror(fptr)) {
		printf("\nError writing to file.\n");
	}
	else {
		printf("\nEmployee added sucessfully!\n");
	}
	fclose(fptr);
}

void staffDisplay()
{
		Staff info;
		FILE* fptr = fopen("staff.bin", "rb");

		if (fptr == NULL) {
			printf("Error opening file.\n");
			return;
		}

		printf("\nAll Employee Display\n");
		printf("EmployeeID |  Employee Name  |  gender  |  age  |	Password  |   Position\n");

		while (fread(&info, sizeof(Staff), 1, fptr) == 1) {
			printf(" %s\t\t%s\t\t%c\t%d\t%s\t%s\n\n", info.employeeID, info.employeeName, info.gender, info.age, info.password, info.position);
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

	printf("\nEnter the Employee ID to modify: ");
	rewind(stdin);
	scanf("%s", enteredID);

	for (i = 0; i < count; i++) {
		if (strcmp(staff[i].employeeID, enteredID) == 0) {
			found = 1;
			break;
		}
	}

	if (found == 1) {
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

		printf("\nEmployee details modified successfully.\n\n");
	}
	else{
		printf("\nEmployee not found.\n\n");
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

	printf("\nEnter the Employee ID to delete: ");
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
			printf("Error opening file for writing.\n\n");
			return;
		}

		fwrite(staff, sizeof(Staff), count, fptr);
		fclose(fptr);

		printf("\nEmployee deleted successfully.\n\n");
	}
	else {
		printf("\nEmployee not found.\n\n");
	}
}
void staffPassRecovery()
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

	printf("\nEnter the Employee ID to recover: ");
	rewind(stdin);
	scanf("%s", enteredID);

	for (i = 0; i < count; i++) {
		if (strcmp(staff[i].employeeID, enteredID) == 0) {
			found = 1;
			break;
		}
	}

	if (found == 1) {
		printf("Enter your new password: ");
		rewind(stdin);
		scanf("%[^\n]", &staff[i].password);

		fseek(fptr, i * sizeof(Staff), SEEK_SET);

		fwrite(&staff[i], sizeof(Staff), 1, fptr);

		printf("\nEmployee password changed successfully.\n\n");
	}
	else{
		printf("\nEmployee not found.\n\n");
	}
	fclose(fptr);
}
