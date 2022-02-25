
#include "Services.h"

void update(DynamicArray* da, int pos, char name[], char supplier[], int quantity, char exp_date[], DynamicArray** undo, int* undo_length, int* undo_max)
{ /*
	da-Our main dynamic array where we store the TELements
	pos-the position of the element we want to update
	name-the updated name
	supplier-the updated supplier
	quantity-the updated quantity
	exp_date-the updated expiration date
  */
	undo[*undo_length] = createDynamicArray(da->capacity);
	for (int i = 0; i < da->length; i++)
	{
		add(undo[*undo_length], da->elems[i]);
	}
	*undo_length = *undo_length + 1;
	if (*undo_length > *undo_max)
		*undo_max = *undo_length;

	if (strcmp(name, "/") != 0)
		strcpy_s(da->elems[pos].name, strlen(name) + 1, name);
	if (strcmp(supplier, "/") != 0)
		strcpy_s(da->elems[pos].supplier, strlen(supplier) + 1, supplier);
	if (strcmp(exp_date, "/") != 0)
		strcpy_s(da->elems[pos].exp_date, strlen(exp_date) + 1, exp_date);
	if (quantity >= 0)
		da->elems[pos].quantity = quantity;
}

void remove_elem(DynamicArray* da, int pos, DynamicArray** undo, int* undo_length, int* undo_max)
{ /*
	da-our main dynamic array
	pos- the position of the element we want to delete
	undo-the 2D dynamic array in which we store instances of the da array before we perform a change
	undo_length-the current length of the undo array
	undo_max-the max length of the undo array 

  */
	undo[*undo_length] = createDynamicArray(da->capacity);
	for (int i = 0; i < da->length; i++)
	{
		add(undo[*undo_length], da->elems[i]);
	}
	*undo_length = *undo_length + 1;
	if (*undo_length > *undo_max)
		*undo_max = *undo_length;

	for (int i = pos; i < da->length - 1; i++)
		da->elems[i] = da->elems[i + 1];
	da->length--;

}


void swap(Material* m1, Material* m2)
{
	Material aux = *m1;
	*m1 = *m2;
	*m2 = aux;
}


