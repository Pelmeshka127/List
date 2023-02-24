#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listconfig.h"

const elem_t Poison = -1;

struct list_node {
    elem_t data;
    int next;
    int prev;
};

struct list_s {
    size_t capacity;
    size_t size;
    size_t head;
    size_t tail;
    size_t free;
    list_node * node;
    int error;
    bool is_sorted;
};

enum Error {
    No_Error        = 0,
    Alloc_Err       = 1,
    Overflow        = 2,
    Underflow       = 3,
    Empty           = 4,
    Incorrect_Index = 5,
    Zero_Elem_Error = 6,
};




//---------------------------------------------------------------------------------------------//

/// @brief Function creates a list
/// @param value the value in the head of list
/// @return the head of list
list_s * List_Ctor();

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @param value 
/// @return 
int List_Insert_Front(list_s * const header, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @param value 
/// @return 
int List_Insert_Back(list_s * const header, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief Function inserts value after given index
/// @param header is ptr on the list struct
/// @param index is the given index
/// @param value is the given value
/// @return 
int List_Insert_After(list_s * const header, size_t index, int value);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @param inde 
/// @param value 
/// @return 
int List_Insert_Before(list_s * const header, size_t inde, int value);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @param index 
/// @return 
int List_Erase_Node(list_s * const header, size_t index);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header
void List_Dtor(list_s * const header);

//---------------------------------------------------------------------------------------------//
#endif