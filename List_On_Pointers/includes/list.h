#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list_config.h"

//---------------------------------------------------------------------------------------------//

struct list_node {
    elem_t data;
    struct list_node * next;
    struct list_node * prev;
};

struct list_s {
    size_t size;
    struct list_node * head;
    struct list_node * tail;
};

//---------------------------------------------------------------------------------------------//

enum {
    No_Error,
    Alloc_Err,
    File_Error,
};

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param value 
/// @return 
list_node * List_Ctor(list_s * const header, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param my_list 
/// @param value 
/// @return 
list_node * List_Insert_Back(list_s * const header, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @param value 
/// @return 
list_node * List_Insert_Front(list_s * const header, elem_t value);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @param value 
/// @param index 
/// @return 
list_node * List_Insert_After(list_s * const header, elem_t value, list_node * node_index);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @param value 
/// @param index 
/// @return 
list_node * List_Insert_Before(list_s * const header, elem_t value, list_node * node_index);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @param index 
/// @return 
list_node * List_Remove_Node(list_s * const header, list_node * node_index);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @return 
list_node * List_Remove_Head(list_s * const header);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @return 
list_node * List_Remove_Tail(list_s * const header);

//---------------------------------------------------------------------------------------------//

/// @brief 
/// @param header 
/// @return 
list_node * List_Dtor(list_s * const header);

//---------------------------------------------------------------------------------------------//

#endif
