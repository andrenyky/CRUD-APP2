#pragma once
#include "DynamicArray.h"
void update(DynamicArray* da, int pos, char name[], char supplier[], int quantity, char exp_date[], DynamicArray** undo, int* undo_length, int* undo_max);
void remove_elem(DynamicArray* da, int pos, DynamicArray** undo, int* undo_length, int* undo_max);
void swap(Material* m1, Material* m2);

