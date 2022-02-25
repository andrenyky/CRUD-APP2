#include "Material.h"
#include <string.h>
#include <stdio.h>

Material createMaterial(char name[], char supplier[], int quantity, char exp_date[])
{
	Material p;
	strcpy_s(p.name,strlen(name)+1,name);
	strcpy_s(p.supplier, strlen(supplier)+1, supplier);
	strcpy_s(p.exp_date,strlen(exp_date)+1, exp_date);
	p.quantity = quantity;

	return p;
}

char* getName(Material* p)
{
	return p->name;
}

char* getSupplier(Material* p)
{
	return p->supplier;
}

char* getExpDate(Material* p)
{
	return p->exp_date;
}

void toString(Material p,char *str)
{
	sprintf_s(str,100, "MATERIAL:%s,SUPPLIER:%s,QUANTITY:%d,EXP-DATE:%s", p.name, p.supplier, p.quantity, p.exp_date);
}