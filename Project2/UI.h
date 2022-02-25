#pragma once
#include "DynamicArray.h"



void ui_undo_func(DynamicArray* da, DynamicArray** undo, int* undo_length, int* undo_max);
void ui_redo_func(DynamicArray* da, DynamicArray** undo, int* undo_length, int* undo_max);
void ui_add(DynamicArray* da, DynamicArray** undo, int undo_length, int undo_max);
void ui_update(DynamicArray* da, DynamicArray** undo, int undo_length, int undo_max);
void ui_remove(DynamicArray* da, DynamicArray** undo, int undo_length, int undo_max);
void ui_filter(DynamicArray* da);
void ui_filter_supplier(DynamicArray* da);
void ui_short_supply(DynamicArray* da);
void ui_list(DynamicArray* da);
void print_menu();
void console();