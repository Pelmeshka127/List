#include "../list_includes/list.h"
#include "../list_includes/dump.h"
#include "../list_includes/debug.h"

//---------------------------------------------------------------------------------------------//

FILE * log_file = nullptr;

//---------------------------------------------------------------------------------------------//

int List_Ctor(list_s * const header, int capacity = Def_Capacity)
{
    if (capacity < 1)
    {
        fprintf(stderr, "Incorrect value of the capacity of the list %d\n", capacity);
        return Incorrect_Capacity;
    }

    header->capacity = capacity;
    header->size = 0;
    header->head = 0;
    header->tail = 0;
    header->free = 1;
    
    header->is_sorted = true;

    header->node = (list_node *)calloc ((unsigned int) header->capacity + 1, sizeof(list_node));

    if (header->node == nullptr)
    {
        fprintf(stderr, "Allocation of the list array failed\n");
        return Alloc_Err;
    }

    for (int node_idx = 1; node_idx <= header->capacity; node_idx++)
    {
        header->node[node_idx].next = node_idx + 1;
        header->node[node_idx].prev = Poison;
        header->node[node_idx].data = 0;
    }

    header->node[header->capacity].next = 0;

    LIST_VERIFICATE(header);

    List_Console_Dump(header);
    List_Dump(header, log_file);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Insert_Front(list_s * const header, elem_t value)
{
    assert(header);

    if (header->size == header->capacity)
    {
        if (List_Realloc(header, Up_Mode) == Alloc_Err)
        {
            fprintf(stderr, "In function %s reallocation failed\n", __PRETTY_FUNCTION__);
            return  Alloc_Err;
        }   
        List_Console_Dump(header);
    }

    int cur_idx   = header->free;   
    header->free  = header->node[cur_idx].next;

    header->node[cur_idx].data = value;
    header->node[cur_idx].next = 0;
    header->node[cur_idx].prev = header->tail;

    if (header->head == 0)
        header->head = cur_idx;

    if (header->tail != 0)
        header->node[header->tail].next = cur_idx;
    
    header->tail = cur_idx;

    header->size++;

    LIST_VERIFICATE(header);

    List_Console_Dump(header);
    List_Dump(header, log_file);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Insert_Back(list_s * const header, elem_t value)
{
    assert(header);

    if (header->size == header->capacity)
    {
        if (List_Realloc(header, Up_Mode) == Alloc_Err)
        {
            fprintf(stderr, "In function %s reallocation failed\n", __PRETTY_FUNCTION__);
            return  Alloc_Err;
        }   
        List_Console_Dump(header);
    }

    int cur_idx  = header->free;
    header->free = header->node[cur_idx].next;

    header->node[cur_idx].data = value;
    header->node[cur_idx].next = header->head;
    header->node[cur_idx].prev = 0;

    if (header->head != 0)
        header->node[header->head].prev = cur_idx;
    
    header->head = cur_idx;

    if (header->tail == 0)
        header->tail = cur_idx;
    
    header->size++;

    LIST_VERIFICATE(header);

    List_Console_Dump(header);
    List_Dump(header, log_file);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Insert_After(list_s * const header, int index, elem_t value)
{
    assert(header);
    assert(value);

    if (header->size == 0)
    {
        fprintf(stderr, "You cannot insert after index %d because the list is empty\n", index);
        return Empty;
    }

    if (index <= 0 || index > header->capacity)
    {
        fprintf(stderr, "Incorrect index %d. The capacity of the list is %u.\n", index, header->capacity);
        return Incorrect_Index;
    }

    if (header->size == header->capacity)
    {
        if (List_Realloc(header, Up_Mode) == Alloc_Err)
        {
            fprintf(stderr, "In function %s reallocation failed\n", __PRETTY_FUNCTION__);
            return Alloc_Err;
        }
        List_Console_Dump(header);
        List_Dump(header, log_file);
    }

    if (header->size == 0)
        List_Insert_Front(header, value);

    else if (header->size != 0 && index == header->tail)
        List_Insert_Front(header, value);

    else
    {
        int inserting_index = header->free;
        header->free        = header->node[header->free].next;

        header->node[inserting_index].data = value;
        header->node[inserting_index].next = header->node[index].next;
        header->node[inserting_index].prev = index;

        header->node[header->node[index].next].prev = inserting_index;
        header->node[index].next                    = inserting_index;

        header->size++;

        header->is_sorted = false;
        
        List_Console_Dump(header);
        List_Dump(header, log_file);
    }

    LIST_VERIFICATE(header);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Insert_Before(list_s * const header, int index, elem_t value)
{
    assert(header);
    assert(value);

    if (header->size == 0)
    {
        fprintf(stderr, "You cannot insert after index %d because the list is empty\n", index);
        return Empty;
    }

    if (index <= 0 || index > header->capacity)
    {
        fprintf(stderr, "Incorrect index %d. The capacity of the list is %u.\n", index, header->capacity);
        return Incorrect_Index;
    }

    if (header->size == header->capacity)
    {
        if (List_Realloc(header, Up_Mode) == Alloc_Err)
        {
            fprintf(stderr, "In function %s reallocation failed\n", __PRETTY_FUNCTION__);
            return Alloc_Err;
        }
        List_Console_Dump(header);
        List_Dump(header, log_file);
    }

    if (header->size == 0)
        List_Insert_Back(header, value);

    else if (header->size != 0 && index == header->head)
        List_Insert_Back(header, value);

    else
        List_Insert_After(header, header->node[index].prev, value);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Erase_Node(list_s * const header, int index)
{
    assert(header);
    assert(index);

    if (header->size == 0)
    {
        fprintf(stderr, "You cannot erase any elements, because list is empty\n");
        return Underflow;
    }

    if (index <= 0 || index > header->capacity)
    {
        fprintf(stderr, "Incorrect index %du. Capacity is %u\n", index, header->capacity);
        return Incorrect_Index;
    }

    if (header->size  <= header->capacity / 4)
    {
        if (List_Realloc(header, Down_Mode) == Alloc_Err)
        {
            fprintf(stderr, "In function %s reallocation failed\n", __PRETTY_FUNCTION__);
            return Alloc_Err;
        }
        List_Console_Dump(header);
        List_Dump(header, log_file);
    }

    if (index == header->head)
        List_Erase_Head(header);

    else if (index == header->tail)
        List_Erase_Tail(header);

    else
    {
        header->node[header->node[index].prev].next = header->node[index].next;
        header->node[header->node[index].next].prev = header->node[index].prev;

        header->node[index].data = 0;
        header->node[index].next = header->free;
        header->node[index].prev = Poison;

        header->free = index;

        header->is_sorted = false;

        header->size--;

        List_Console_Dump(header);
        List_Dump(header, log_file);
    }

    LIST_VERIFICATE(header);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Erase_Head(list_s * const header)
{
    assert(header);

    if (header->size  <= header->capacity / 4)
    {
        if (List_Realloc(header, Down_Mode) == Alloc_Err)
        {
            fprintf(stderr, "In function %s reallocation failed\n", __PRETTY_FUNCTION__);
            return Alloc_Err;
        }
        List_Console_Dump(header);
        List_Dump(header, log_file);
    }

    int old_head = header->head;

    header->head = header->node[old_head].next;

    header->node[header->node[old_head].next].prev = 0;

    header->node[old_head].data = 0;
    header->node[old_head].next = header->free;
    header->node[old_head].prev = Poison;

    header->free = old_head;

    header->size--;

    List_Console_Dump(header);
    List_Dump(header, log_file);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Erase_Tail(list_s * const header)
{
    assert(header);

    if (header->size  <= header->capacity / 4)
    {
        if (List_Realloc(header, Down_Mode) == Alloc_Err)
        {
            fprintf(stderr, "In function %s reallocation failed\n", __PRETTY_FUNCTION__);
            return Alloc_Err;
        }
        List_Console_Dump(header);
        List_Dump(header, log_file);
    }

    int old_tail = header->tail;

    if (header->size == 1)
        header->head = 0;

    header->tail = header->node[old_tail].prev;

    header->node[header->node[old_tail].prev].next = 0;

    header->node[old_tail].data = 0;
    header->node[old_tail].next = header->free;
    header->node[old_tail].prev = Poison;

    header->free = old_tail;

    header->size--;

    List_Console_Dump(header);
    List_Dump(header, log_file);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Realloc(list_s * const header, int mode)            
{
    assert(header);
    int old_capacity = (int) header->capacity;

    if (header->is_sorted == false)
        List_Linearize(header);

    if (mode == Up_Mode)
    {
        header->capacity = header->capacity * Multiplier;
        header->node = (list_node *)realloc (header->node, (unsigned int) (header->capacity + 1) * sizeof(list_node));
        if (header->node == nullptr)
        {
            fprintf(stderr, "Reallocation of the list failed\n");
            return Alloc_Err;
        }
        
        header->free = old_capacity + 1;

        for (int node_idx = old_capacity + 1; node_idx <= header->capacity; node_idx++)
        {
            header->node[node_idx].data = 0;
            header->node[node_idx].next = node_idx + 1;
            header->node[node_idx].prev = Poison;
        }

        printf("ReAllocation: new capacity is %u\n", header->capacity);
    }

    else if (mode == Down_Mode)
    {
        header->capacity = header->capacity / Multiplier;
        header->node = (list_node *)realloc (header->node, (unsigned int) (header->capacity + 1) * sizeof(list_node));
        if (header->node == nullptr)
        {
            fprintf(stderr, "Reallocation of the list failed\n");
            return Alloc_Err;
        }

        printf("ReAllocation: new capacity is %u\n", header->capacity);
    }

    else
    {
        fprintf(stderr, "Mode of the reallocation %d is undefined\n", mode);
        return Alloc_Err;
    }

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int List_Get_Phys_By_Log(list_s * const header, int my_log_index)
{
    assert(header);

    if (my_log_index <= 0 || my_log_index > (int) header->size)
    {
        fprintf(stderr, "Incorrect index %d in function %s\n", my_log_index, __PRETTY_FUNCTION__);
        return Incorrect_Index;
    }

    int cur_idx = header->head;
    int log_idx = 1;

    while (log_idx < my_log_index)
    {
        cur_idx = header->node[cur_idx].next;
        log_idx++;
    }

    return cur_idx;
}

//---------------------------------------------------------------------------------------------//

int List_Get_Log_By_Phys(list_s * const header, int my_phys_index)
{
    assert(header);

    if (my_phys_index < 0 || my_phys_index > (int) header->size)
    {
        fprintf(stderr, "Incorrect index %d in function %s\n", my_phys_index, __PRETTY_FUNCTION__);
        return Incorrect_Index;
    }

    int cur_idx = header->head;
    int log_idx = 1;

    while (cur_idx != my_phys_index)
    {
        cur_idx = header->node[cur_idx].next;
        log_idx++;
    }

    return log_idx;
}

//---------------------------------------------------------------------------------------------//

int List_Get_Log_By_Data(list_s * const header, int value)
{
    assert(header);

    if (header->is_sorted == false)
        List_Linearize(header);

    list_node cur_node = header->node[header->head];
    int log_index = 1;

    while (cur_node.data != value)
    {
        log_index++;
        cur_node = header->node[cur_node.next];
    }

    return log_index;
}

//---------------------------------------------------------------------------------------------//

int List_Linearize(list_s * const header)
{
    assert(header);

    if (header->size <= 1)
    {
        fprintf(stderr, "List is empty in function %s\n", __PRETTY_FUNCTION__);
        return Empty;
    }

    list_node * new_node = (list_node *)calloc ((unsigned int) header->capacity + 1, sizeof(list_node));
    if (new_node == nullptr)
    {
        fprintf(stderr, "Allocation of new list in %s failed\n", __PRETTY_FUNCTION__);
        return Alloc_Err;
    }

    header->node[header->tail].next = header->free;

    header->free = 0;
    header->head = 1;
    header->tail = (int) header->size;
    header->is_sorted = true;

    new_node[0].data = 0;
    new_node[0].next = 0;
    new_node[0].prev = 0;

    int old_node_idx = 1;

    for (int new_node_idx = 1; new_node_idx <= header->capacity; new_node_idx++)
    {
        if (header->node[old_node_idx].prev == Poison)
        {
            if (header->free == 0)
                header->free = new_node_idx;

            new_node[new_node_idx].prev = Poison;
            new_node[new_node_idx].next = (new_node_idx + 1) % (header->capacity + 1);
        }

        else
        {
            new_node[new_node_idx].data = header->node[old_node_idx].data;
            new_node[new_node_idx].next = (new_node_idx + 1) % (header->capacity + 1);
            new_node[new_node_idx].prev = new_node_idx - 1;
        }

        old_node_idx = header->node[old_node_idx].next;
    }

    free(header->node);

    header->node = new_node;
    header->node[header->tail].next = 0;

    List_Console_Dump(header);
    List_Dump(header, log_file);

    return No_Error;
}

//---------------------------------------------------------------------------------------------//

void List_Dtor(list_s * const header)
{
    assert(header);

    int max_size = header->size;

    for (int i = 1; i <= max_size; i++)
        List_Erase_Tail(header);

    header->capacity = 0;
    header->free     = 0;
    header->head     = 0;
    header->tail     = 0;
    header->free     = 0;

    free(header->node);
}

//---------------------------------------------------------------------------------------------//

int Open_File()
{
    log_file = fopen("graphics/graph.html", "w");
    if (log_file == nullptr)
    {
        fprintf(stderr, "Failed openning graph.html in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }
    return No_Error;
}

//---------------------------------------------------------------------------------------------//

int Close_File()
{
    if (fclose(log_file) == EOF)
    {
        fprintf(stderr, "Failed closing graph.html in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }
    return No_Error;
}

//---------------------------------------------------------------------------------------------//