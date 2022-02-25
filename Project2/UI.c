#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include "Material.h"
#include "DynamicArray.h"
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <crtdbg.h>

void ui_undo_func(DynamicArray* da, DynamicArray** undo, int* undo_length, int* undo_max)
{
	int OK = 1;
	if (*undo_length == 10)
	{
		printf("NO MORE UNDOS\n");
		OK = 0;
	}
	if (*undo_length == *undo_max && OK == 1)
	{
		undo[*undo_length] = createDynamicArray(da->capacity);
		for (int i = 0; i < da->length; i++)
		{
			add(undo[*undo_length], da->elems[i]);
		}
		*undo_max = *undo_max + 1;
		for (int i = 0; i < undo[*undo_length - 1]->length; i++)
		{
			da->elems[i] = undo[*undo_length - 1]->elems[i];
		}
		da->length = undo[*undo_length - 1]->length;
		*undo_length = *undo_length - 1;
		printf("UNDO COMPLETED\n");
	}
	else if (*undo_length < *undo_max && OK == 1)
	{
		for (int i = 0; i < undo[*undo_length - 1]->length; i++)
		{
			da->elems[i] = undo[*undo_length - 1]->elems[i];
		}
		da->length = undo[*undo_length - 1]->length;
		*undo_length = *undo_length - 1;
		printf("UNDO COMPLETED\n");
	}

}

void ui_redo_func(DynamicArray* da, DynamicArray** undo, int* undo_length, int* undo_max)
{
	if (*undo_length + 1 < *undo_max)
	{
		for (int i = 0; i < undo[*undo_length + 1]->length; i++)
		{
			da->elems[i] = undo[*undo_length + 1]->elems[i];
		}
		da->length = undo[*undo_length + 1]->length;
		*undo_length = *undo_length + 1;
		printf("REDO COMPLETED\n");
	}
	else
		printf("NO MORE REDOS\n");

}

void ui_add(DynamicArray* da, DynamicArray** undo, int undo_length, int undo_max) {
	char name[50];
	char supplier[50];
	char exp_date[50];
	char alphabet[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	char days[3];
	char month[3];
	char year[5];
	int OK = 1;
	int quantity;
	printf("NAME:");
	scanf_s("%s", name, 50);
	printf("SUPPLIER:");
	scanf_s("%s", supplier, 50);
	printf("QUANTITY:");
	scanf_s("%d", &quantity);
	printf("EXPIRATION DATE(DD/MM/YYYY):");
	scanf_s("%s", exp_date, 50);
	strncpy_s(days, 3, exp_date, 2);
	strncpy_s(month, 3, exp_date + 3, 2);
	strncpy_s(year, 5, exp_date + 6, 4);
	for (int i = 0; i < strlen(days); i++)
		if (strchr(alphabet, days[i]) && OK == 1)
		{
			printf("INPUT A VALID DATE\n");
			OK = 0;
		}
	for (int i = 0; i < strlen(month); i++)
		if (strchr(alphabet, month[i]) && OK==1)
		{
			printf("INPUT A VALID DATE\n");
			OK = 0;
		}
	for (int i = 0; i < strlen(year); i++)
		if (strchr(alphabet, year[i]) && OK == 1)
		{
			printf("INPUT A VALID DATE\n");
			OK = 0;
		}
	int days_int = atoi(days);
	int month_int = atoi(month);
	int year_int = atoi(year);
	if ((month_int <= 0 || month_int > 12) && OK == 1)
	{
		printf("INPUT A VALID MONTH\n");

		OK = 0;
	}
	if ((days_int <= 0 || days_int > 31) && OK == 1)
	{
		printf("INPUT A VALID DAY\n");
		OK = 0;
	}
	if (OK == 1)
	{
		Material material = createMaterial(name, supplier, quantity, exp_date);
		add_undo(da, material, undo, undo_length, undo_max);
	}

};

void ui_update(DynamicArray* da, DynamicArray** undo, int undo_length, int undo_max)
{
	char buffer[150];
	char name[50];
	char supplier[50];
	char exp_date[50];
	int quantity;
	int pos = -1;
	for (int i = 0; i < da->length; i++)
	{
		toString(da->elems[i], buffer);
		printf("\tMATERIAL NR %d:%s\n", i, buffer);
	}
	printf("Update the material at position: ");
	scanf_s("%d", &pos);
	printf("NEW NAME( / to omit):");
	scanf_s("%s", name, 50);
	printf("NEW SUPPLIER( / to omit):");
	scanf_s("%s", supplier, 50);
	printf("NEW QUANTITY(negative value to omit):");
	scanf_s("%d", &quantity);
	printf("NEW EXPIRATION DATE(DD/MM/YYYY)( /to omit):");
	scanf_s("%s", exp_date, 50);

	update(da, pos, name, supplier, quantity, exp_date, undo, undo_length, undo_max);

}

void ui_remove(DynamicArray* da, DynamicArray** undo, int undo_length, int undo_max) {
	char buffer[150];
	int pos = -1;
	for (int i = 0; i < da->length; i++)
	{
		toString(da->elems[i], buffer);
		printf("\tMATERIAL NR %d:%s\n", i, buffer);
	}
	printf("Remove the material at position: ");
	scanf_s("%d", &pos);

	remove_elem(da, pos, undo, undo_length, undo_max);

};

void ui_filter(DynamicArray* da) {
	char stringFilter[50];
	char days[3];
	char month[3];
	char year[5];
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int current_day = newtime.tm_mday;
	int current_year = newtime.tm_year + 1900;
	int current_month = newtime.tm_mon + 1;

	printf("string to be contained:");
	gets(stringFilter);
	gets(stringFilter);

	for (int i = 0; i < da->length; i++)
	{
		int expired = 0;
		strncpy_s(days, 3, da->elems[i].exp_date, 2);
		strncpy_s(month, 3, da->elems[i].exp_date + 3, 2);
		strncpy_s(year, 5, da->elems[i].exp_date + 6, 4);
		int days_int = atoi(days);
		int month_int = atoi(month);
		int year_int = atoi(year);

		if (year_int < current_year)
			expired = 1;
		else if (year_int == current_year)
		{
			if (month_int < current_month)
				expired = 1;
			else if (month_int == current_month)
			{
				if (days_int < current_day)
					expired = 1;

			}
		}
		if (expired == 1)
		{
			if (strstr(da->elems[i].name, stringFilter))
			{
				printf("MATERIAL:%s,SUPPLIER:%s,QUANTITY:%d,EXP-DATE:%s\n", da->elems[i].name, da->elems[i].supplier, da->elems[i].quantity, da->elems[i].exp_date);
			}
		}
	}
}

void ui_filter_supplier(DynamicArray* da)
{
	char str1[50];
	char str2[50];
	char stringFilter[50];
	printf("string to be contained:");
	scanf_s("%s", stringFilter, 50);

	DynamicArray* new_array = createDynamicArray(da->capacity);

	for (int i = 0; i < da->length; i++)
	{
		if (strstr(da->elems[i].name, stringFilter))
			add(new_array, da->elems[i]);
	}

	for (int i = 0; i < new_array->length - 1; i++)
		for (int j = 0; j < new_array->length - i - 1; j++)
		{
			strcpy_s(str1, strlen(new_array->elems[j].supplier) + 1, new_array->elems[j].supplier);
			strcpy_s(str2, strlen(new_array->elems[j + 1].supplier) + 1, new_array->elems[j + 1].supplier);
			for (int k = 0; k < strlen(str1); k++)
				str1[k] = tolower(str1[k]);
			for (int k = 0; k < strlen(str2); k++)
				str2[k] = tolower(str2[k]);
			if (strcmp(str1, str2) < 0)
				swap(&new_array->elems[j], &new_array->elems[j + 1]);
		}
	for (int i = 0; i < new_array->length; i++)
		printf("MATERIAL:%s,SUPPLIER:%s,QUANTITY:%d,EXP-DATE:%s\n", new_array->elems[i].name, new_array->elems[i].supplier, new_array->elems[i].quantity, new_array->elems[i].exp_date);

	destroy(new_array);
}

void ui_short_supply(DynamicArray* da) {
	char str[50];
	int quant = 0;
	printf("Type the name of the supplier:");
	scanf_s("%s", str, 50);
	printf("Quantity:");
	scanf_s("%d", &quant);
	DynamicArray* new_array = createDynamicArray(da->capacity);

	for (int i = 0; i < da->length; i++)
	{
		if (strcmp(da->elems[i].supplier, str) == 0)
		{
			if (da->elems[i].quantity < quant)
				add(new_array, da->elems[i]);
		}
	}

	for (int i = 0; i < new_array->length - 1; i++)
		for (int j = 0; j < new_array->length - i - 1; j++)
		{
			if (new_array->elems[j].quantity > new_array->elems[j + 1].quantity)
				swap(&new_array->elems[j], &new_array->elems[j + 1]);

		}

	for (int i = 0; i < new_array->length; i++)
		printf("MATERIAL:%s,SUPPLIER:%s,QUANTITY:%d,EXP-DATE:%s\n", new_array->elems[i].name, new_array->elems[i].supplier, new_array->elems[i].quantity, new_array->elems[i].exp_date);

	destroy(new_array);
}

void ui_list(DynamicArray* da) {
	char buffer[150];
	for (int i = 0; i < da->length; i++)
	{
		toString(da->elems[i], buffer);
		printf("\t%s\n", buffer);

	}
}
void print_menu() {

	printf("<********************>\n");
	printf("1.ADD MATERIAL\n");
	printf("2.UPDATE MATERIAL\n");
	printf("3.REMOVE MATERIAL\n");
	printf("4.LIST ALL MATERIALS\n");
	printf("5.SEE ALL EXPIRED MATERIAL CONTAINING A STRING\n");
	printf("6.SEE MATERIALS CONTAINING A STRING (DESCENDING ORDER BY SUPPLIER)\n");
	printf("7.DISPLAY ALL MATERIALS FROM A GIVEN SUPPLIER, WHICH ARE IN SHORT SUPPLY\n");
	printf("8.UNDO\n");
	printf("9.REDO\n");
	printf("10.EXIT\n");
	printf("<********************>\n");
}
void console()
{
	testsDynamicArray();
	DynamicArray** undo;
	undo = (DynamicArray**)malloc(100 * sizeof(DynamicArray*));
	int undo_length = 0;
	int undo_max = 0;
	Material m1 = createMaterial("milk", "milkCompany", 20, "03/04/2021");
	Material m2 = createMaterial("eggs", "eggMan", 600, "15/04/2020");
	Material m3 = createMaterial("flour", "idk", 100, "09/03/2021");
	Material m4 = createMaterial("apples", "Stefan", 120, "23/04/2021");
	Material m5 = createMaterial("lemons", "Someone", 520, "15/04/2021");
	Material m6 = createMaterial("salt", "idk", 160, "09/03/2021");
	Material m7 = createMaterial("cocoa", "idk", 50, "09/03/2021");
	Material m8 = createMaterial("ginger", "GINNGER", 1000, "03/04/2025");
	Material m9 = createMaterial("yeast", "DoughDough", 450, "12/10/2021");
	Material m10 = createMaterial("Oil", "oilCo", 1040, "23/07/2023");
	DynamicArray* da = createDynamicArray(4);
	add_undo(da, m1, undo, &undo_length, &undo_max);
	add_undo(da, m2, undo, &undo_length, &undo_max);
	add_undo(da, m3, undo, &undo_length, &undo_max);
	add_undo(da, m4, undo, &undo_length, &undo_max);
	add_undo(da, m5, undo, &undo_length, &undo_max);
	add_undo(da, m6, undo, &undo_length, &undo_max);
	add_undo(da, m7, undo, &undo_length, &undo_max);
	add_undo(da, m8, undo, &undo_length, &undo_max);
	add_undo(da, m9, undo, &undo_length, &undo_max);
	add_undo(da, m10, undo, &undo_length, &undo_max);


	while (1)
	{
		int command = 0;
		print_menu();
		printf("Choose your option:");
		scanf_s("%d", &command);

		switch (command)
		{
		case 1:
			ui_add(da, undo, &undo_length, &undo_max);
			break;
		case 2:
			ui_update(da, undo, &undo_length, &undo_max);
			break;
		case 3:
			ui_remove(da, undo, &undo_length, &undo_max);
			break;
		case 4:
			ui_list(da);
			break;
		case 5:
			ui_filter(da);
			break;
		case 6:
			ui_filter_supplier(da);
			break;
		case 7:
			ui_short_supply(da);
			break;
		case 8:
			ui_undo_func(da, undo, &undo_length, &undo_max);
			break;
		case 9:
			ui_redo_func(da, undo, &undo_length, &undo_max);
			break;
		case 10:
			destroy(da);
			for (int i = 0; i < undo_max; i++)
			{
				destroy(undo[i]);
			}
			free(undo);
			printf("Bye!\n");
			_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
			_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
			_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
			_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
			_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
			_CrtDumpMemoryLeaks();
			return 0;
		default:
			printf("Please input a valid command\n");
		}


	}
}
