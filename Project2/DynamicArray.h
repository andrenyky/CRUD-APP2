#pragma once
#include "Material.h"

typedef Material TElement;

typedef struct {
	TElement* elems;
	int length;
	int capacity;
}DynamicArray;


DynamicArray* createDynamicArray(int capacity);

void destroy(DynamicArray* arr);
void resize(DynamicArray* arr);
void add(DynamicArray* arr, TElement t);
void add_undo(DynamicArray* arr, TElement t, DynamicArray** undo, int* undo_length,int* undo_max);
void testsDynamicArray();



