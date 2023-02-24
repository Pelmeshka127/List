#include "../list_includes/list.h"
#include "../list_includes/dump.h"
#include "../list_includes/debug.h"

//---------------------------------------------------------------------------------------------//

list_s * List_Ctor()
{
    list_s * header = (list_s *)calloc (1, sizeof(list_s));

    if (header == nullptr)
        return nullptr;
    
    header->capacity = Def_Capacity;
    header->size = 0;
    header->head = 0;
    header->tail = 0;
    header->free = 1;

    header->node = (list_node *)calloc (Def_Capacity + 1, sizeof(list_node));

    if (header->node == nullptr)
        return nullptr;

    for (size_t node_idx = 1; node_idx <= header->capacity; node_idx++)
    {
        header->node[node_idx].next = int (node_idx + 1);
        header->node[node_idx].prev = Poison;
        header->node[node_idx].data = 0;
    }

    header->node[header->capacity].next = 0;

    LIST_VERIFICATE(header);

#ifdef LIST_CONSOLE_DUMP
    List_Console_Dump(header);
#endif

    return header;
}

//---------------------------------------------------------------------------------------------//

int List_Insert_Front(list_s * const header, elem_t value)
{
    assert(header);

    size_t cur_idx = header->free;
    header->free   = (size_t) header->node[cur_idx].next;

    header->node[cur_idx].data = value;
    header->node[cur_idx].next = 0;
    header->node[cur_idx].prev = (int) header->tail;

    if (header->head == 0)
        header->head = cur_idx;

    if (header->tail != 0)
        header->node[header->tail].next = (int) cur_idx;
    
    header->tail = cur_idx;

    header->size++;

    LIST_VERIFICATE(header);

#ifdef LIST_CONSOLE_DUMP
    List_Console_Dump(header);
#endif

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Insert_Back(list_s * const header, elem_t value)
{
    assert(header);

    size_t cur_idx = header->free;
    header->free   = (size_t) header->node[cur_idx].next;

    header->node[cur_idx].data = value;
    header->node[cur_idx].next = (int) header->head;
    header->node[cur_idx].prev = 0;

    if (header->head != 0)
        header->node[header->head].prev = (int) cur_idx;
    
    header->head = cur_idx;

    if (header->tail == 0)
        header->tail = cur_idx;
    
    header->size++;

    LIST_VERIFICATE(header);

#ifdef LIST_CONSOLE_DUMP
    List_Console_Dump(header);
#endif

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Insert_After(list_s * const header, size_t index, int value)
{
    assert(header);
    assert(index);
    assert(value);

    if (index > header->capacity)
    {
        fprintf(stderr, "Incorrect index %zu. It's bigger than capacity of list %zu.\n", index, header->capacity);
        return Incorrect_Index;
    }

    if (header->size == header->capacity)
    {
        fprintf(stderr, "You cannot insert any more. Size %zu = Capacity %zu\n", header->size, header->capacity);
        return Overflow;
    }

    if (header->size == 0)
    {
        fprintf(stderr, "You cannot insert after index %zu because the list is empty\n", index);
        return Empty;
    }

    if (header->size != 0 && index == header->tail)
        List_Insert_Front(header, value);

    else if (header->node[index].data == 0)
        List_Insert_Front(header, value);

    else
    {
        size_t inserting_index = header->free;
        header->free = (size_t) header->node[header->free].next;

        header->node[inserting_index].data = value;
        header->node[inserting_index].next = header->node[index].next;
        header->node[inserting_index].prev = (int) index;

        header->node[header->node[index].next].prev = (int) inserting_index;
        header->node[index].next = (int) inserting_index;

        header->size++;
        

    #ifdef LIST_CONSOLE_DUMP
        List_Console_Dump(header);
    #endif
    }

    LIST_VERIFICATE(header);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Insert_Before(list_s * const header, size_t index, int value)
{
    assert(header);
    assert(index);
    assert(value);

    if (index > header->capacity)
    {
        fprintf(stderr, "Incorrect index %zu. The capacity is %zu\n", index, header->capacity);
        return Incorrect_Index;
    }

    if (header->size == header->capacity)
    {
        fprintf(stderr, "You cannot insert any more. Size %zu = Capacity %zu\n", header->size, header->capacity);
        return Overflow;
    }

    if (header->size == 0)
    {
        fprintf(stderr, "You cannot insert before index %zu because the list is empty\n", index);
        return Empty;   
    }

    if (header->size != 0 && index == header->head)
        List_Insert_Back(header, value);

    else if (header->size == 0)
        List_Insert_Back(header, value);

    else
    {
        size_t inserting_index = header->free;
        header->free = (size_t) header->node[header->free].next;

        header->node[inserting_index].data = value;
        header->node[inserting_index].next = (int) index;
        header->node[inserting_index].prev = header->node[index].prev;

        header->node[header->node[index].prev].next = (int) inserting_index;
        header->node[index].prev = (int) inserting_index;

        header->size++;

    #ifdef LIST_CONSOLE_DUMP
        List_Console_Dump(header);
    #endif
    }

    LIST_VERIFICATE(header);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Erase_Node(list_s * const header, size_t index)
{
    assert(header);
    assert(index);

    if (header->size == 0)
    {
        fprintf(stderr, "You cannot erase any elements, because list is empty\n");
        return Underflow;
    }

    if (index > header->capacity)
    {
        fprintf(stderr, "Incorrect index %zu. Capacity is %zu\n", index, header->capacity);
        return Incorrect_Index;
    }

    if (index == header->head)
    {
        header->head = (size_t) header->node[index].next;
        header->node[header->node[index].next].prev = 0;

        header->node[index].data = 0;
        header->node[index].next = (int) header->free;
        header->node[index].prev = Poison;

        header->free = index;

        header->size--;

    #ifdef LIST_CONSOLE_DUMP
        List_Console_Dump(header);
    #endif
    }

    else if (index == header->tail)
    {
        header->tail = (size_t) header->node[index].prev;
        header->node[header->node[index].prev].next = 0;

        header->node[index].data = 0;
        header->node[index].next = (int) header->free;
        header->node[index].prev = Poison;

        header->free = index;

        header->size--;

    #ifdef LIST_CONSOLE_DUMP
        List_Console_Dump(header);
    #endif
    }

    else
    {
        header->node[header->node[index].prev].next = header->node[index].next;
        header->node[header->node[index].next].prev = header->node[index].prev;

        header->node[index].data = 0;
        header->node[index].next = (int) header->free;
        header->node[index].prev = Poison;

        header->free = index;

        header->size--;

    #ifdef LIST_CONSOLE_DUMP
        List_Console_Dump(header);
    #endif
    }

    LIST_VERIFICATE(header);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

void List_Dtor(list_s * const header)
{
    assert(header);

    size_t max_size = header->size;

    for (size_t i = 1; i <= max_size; i++)
        List_Erase_Node(header, header->tail);

    header->capacity = 0;
    header->free     = 0;
    header->head     = 0;
    header->tail     = 0;
    header->free     = 0;

    free(header->node);
    free(header);
}

//---------------------------------------------------------------------------------------------//
