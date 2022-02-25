#pragma once

typedef struct {
	char name[50];
	char supplier[50];
	int quantity;
	char exp_date[50];
} Material;

Material createMaterial(char name[], char supplier[], int quantity, char exp_date[]);

char* getName(Material* p);
char* getSupplier(Material* p);
int getQuantity(Material* p);
char* getExpDate(Material* p);

void toString(Material p,char *str);



