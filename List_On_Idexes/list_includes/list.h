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
    int capacity;
    int size;
    int head;
    int tail;
    int free;
    list_node * node;
    int error;
    bool is_sorted;
};

enum Error {
    No_Error            = 0,
    Alloc_Err           = 1,
    Overflow            = 2,
    Underflow           = 3,
    Empty               = 4,
    Incorrect_Index     = 5,
    Zero_Elem_Error     = 6,
    Tail_Error          = 7,
    Head_Error          = 8,
    Free_Error          = 9,
    File_Error          = 10,
    Incorrect_Capacity  = 11,
    Ruined_List         = 12,
};


//---------------------------------------------------------------------------------------------//

/// @brief Function initializes the list
/// @param header is ptr on the list struct
/// @param Capacity is given capacity of the list
/// @return Alloc_Err if initialsing falied, No_Error if it's ok
int List_Ctor(list_s * const header, int Capacity);

//---------------------------------------------------------------------------------------------//

/// @brief Function inserts element to the end of the list
/// @param header is ptr on the list struct
/// @param value is the given value
/// @return Overflow if list is full, No_Error if it's ok
int List_Insert_Front(list_s * const header, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief Function inserts element to the start of the list
/// @param header is ptr on the list struct
/// @param value is the given value
/// @return Overflow if list is full, No_Error if it's ok
int List_Insert_Back(list_s * const header, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief Function inserts value after given index
/// @param header is ptr on the list struct
/// @param index is the given index
/// @param value is the given value
/// @return Incorrct_Index, Empty if there's error, No_Error if it's ok
int List_Insert_After(list_s * const header, int index, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief Funtion inserts value before given index
/// @param header is ptr on the list struct
/// @param index is the given index
/// @param value is the given value
/// @return Incorrct_Index, Empty if there's error, No_Error if it's ok
int List_Insert_Before(list_s * const header, int index, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief Fuction deletes node on the given index
/// @param header is ptr on the list struct
/// @return Underflow, Incorrect_Index if there's error, No_Error if it's ok
int List_Erase_Node(list_s * const header, int index);

//---------------------------------------------------------------------------------------------//

/// @brief Function deletes the head of the list
/// @param header is ptr on the list struct
/// @return No_Error
int List_Erase_Head(list_s * const header);

//---------------------------------------------------------------------------------------------//

/// @brief Function deletes the tail of the list
/// @param header is ptr on the list struct
/// @return No_Error
int List_Erase_Tail(list_s * const header);

//---------------------------------------------------------------------------------------------//

/// @brief Function increases or decreases the list
/// @param header is ptr on the list struct
/// @param mode if mode == Up_Mode -> increasing; mode == Down_Mode -> decreasing
/// @return Alloc_Err if reallocation failed, No_Error if it's ok
int List_Realloc(list_s * const header, int mode);

//---------------------------------------------------------------------------------------------//

/// @brief Function finds out the physical index of the node by logical index
/// @param header is ptr on the list struct
/// @param index is the logical index of our node
/// @return the physical index of the node
int List_Get_Phys_By_Log(list_s * const header, int my_log_index);

//---------------------------------------------------------------------------------------------//

/// @brief Function finds out the logical index of the node by physical index
/// @param header is ptr on the list struct
/// @param my_phys_index is the physical index of the our node
/// @return the logical index of the node
int List_Get_Log_By_Phys(list_s * const header, int my_phys_index);

//---------------------------------------------------------------------------------------------//

/// @brief Function finds out the logical index of the node by value in this node
/// @param header is ptr on the list struct
/// @param my_log_index is the logical index of the our node
/// @return the value of logical index of the node
int List_Get_Log_By_Data(list_s * const header, int value);

//---------------------------------------------------------------------------------------------//

/// @brief Function sorts list so logical and physical orders are equal
/// @param header is ptr on the struct node
/// @return sorted list
int List_Linearize(list_s * const header);

//---------------------------------------------------------------------------------------------//

/// @brief Function destroys list
/// @param header is ptr on the list struct
void List_Dtor(list_s * const header);

//---------------------------------------------------------------------------------------------//

/// @brief Function opens log file of the list
/// @return File_Error is file wasn't open, No_Error if it's ok
int Open_File();

//---------------------------------------------------------------------------------------------//

/// @brief Function closes log file of the list
/// @return File_Error if file wasn't closed, No_Error if it's ok
int Close_File();

//---------------------------------------------------------------------------------------------//

#endif