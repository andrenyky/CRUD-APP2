#include "DynamicArray.h"
#include "Material.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Services.h"
DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	
	if (da == NULL)
		return NULL;

	da->capacity = capacity;
	da->length = 0;

	da->elems = (TElement*)malloc(capacity * sizeof(TElement));
	
	if (da->elems == NULL)
		return NULL;

	return da;
}

void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	free(arr->elems);
		arr->elems = NULL;
	free(arr);

}

void resize(DynamicArray* arr)
{
	arr->capacity = arr->capacity * 2;
	arr->elems = (TElement*)realloc(arr->elems, arr->capacity * sizeof(TElement));
}

void add(DynamicArray* arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;
	if (arr->length == arr->capacity)
		resize(arr);
	if (arr->length == 0)
	{
		arr->elems[arr->length] = t;
		arr->length++;
	}
	else {
		int unique = 1;
		for (int i = 0; i <= arr->length && unique==1; i++)
		{
			if (strcmp(t.name, arr->elems[i].name) == 0)
			{
				if (strcmp(t.supplier, arr->elems[i].supplier) == 0)
				{
					if (strcmp(t.exp_date, arr->elems[i].exp_date) == 0)
					{
						arr->elems[i].quantity+= t.quantity;
						unique = 0;
					}
				}
			}
		} 
		if (unique == 1)
		{
			arr->elems[arr->length] = t;
			arr->length++;
		}
	}
}

void add_undo(DynamicArray* arr, TElement t,DynamicArray** undo, int* undo_length,int* undo_max)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;
	if (arr->length == arr->capacity)
		resize(arr);
	if (arr->length == 0)
	{
		
		arr->elems[arr->length] = t;
		arr->length++;
		undo[*undo_length] = createDynamicArray(arr->capacity);
		for (int i = 0; i < arr->length; i++)
		{
			add(undo[*undo_length],arr->elems[i]);
		}
		*undo_length = *undo_length + 1;
		if (*undo_length > *undo_max)
			*undo_max = *undo_length;
	}
	else {
		int unique = 1;
		for (int i = 0; i <= arr->length && unique == 1; i++)
		{
			if (strcmp(t.name, arr->elems[i].name) == 0)
			{
				if (strcmp(t.supplier, arr->elems[i].supplier) == 0)
				{
					if (strcmp(t.exp_date, arr->elems[i].exp_date) == 0)
					{
						arr->elems[i].quantity += t.quantity;
						unique = 0;
					}
				}
			}
		}
		if (unique == 1)
		{	undo[*undo_length] = createDynamicArray(arr->capacity);
			for (int i = 0; i < arr->length; i++)
			{
				add(undo[*undo_length], arr->elems[i]);
			}
			*undo_length = *undo_length + 1;
			if (*undo_length > *undo_max)
				*undo_max = *undo_length;
			arr->elems[arr->length] = t;
			arr->length++;
		}
	}
}

void testsDynamicArray() {
	DynamicArray** undo;
	undo = (DynamicArray**)malloc(100 * sizeof(DynamicArray*));
	int undo_length = 0;
	int undo_max = 0;
	DynamicArray* da = createDynamicArray(2);
	if (da == NULL)
		assert(0);
	assert(da->capacity == 2);
	assert(da->length == 0);
	Material m1 = createMaterial("Flour", "Dough", 50, "03/04/2005");
	add_undo(da, m1,undo,&undo_length,&undo_max);
	assert(da->length == 1);
	assert(undo_length == 1);
	Material m2 = createMaterial("Milk", "milkkk", 50, "10/11/2024");
	add_undo(da, m2, undo, &undo_length, &undo_max);

	Material m3 = createMaterial("Lemon", "melon", 50, "10/11/2024");
	add_undo(da, m3, undo, &undo_length, &undo_max);
	assert(da->capacity == 4);

	update(da, 0, "apples", "john", 120, "04/05/2040", undo, &undo_length, &undo_max);
	assert(da->elems[0].quantity == 120);

	remove_elem(da, 0, undo, &undo_length, &undo_max);
	assert(da->length == 2);

	destroy(da);
	for (int i = 0; i < undo_max; i++)
		destroy(undo[i]);
	free(undo);

}