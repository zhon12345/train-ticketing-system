#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void modeSelection();
void staffLogin();
void staffInformation();
void staffAdd();
void staffDisplay();
void staffModify();
void staffDelete();
void staffPay();

typedef struct {
	char employeeID[15], employeeName[40], password[20], passRecovery[20], position[30], gender;
	int age;
}staff;

void modeSelection() 
{
	int choice;
	do {
		printf("Select Mode (1-8): \n");
		printf("Mode 1: Add new Staff.\n");
		printf("Mode 2: Display Staff.\n");
		printf("Mode 3: Modify Staff Details.\n");
		printf("Mode 4: Delete Staff.\n");
		printf("Mode 5: Calculate Staff Pay\n");
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
			staffPay();
			break;
		case 6:
			exit(-1);
		default:
			printf("Invalid mode selection, please enter again.\n\n");
		}
	} while (choice >=1 || choice <=6);
};
